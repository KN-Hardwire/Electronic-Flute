#include "functions.h"

void generate_square_wave(const project_type freq, uint16_t volume) {
	/* Division by 0 check */
	if (freq < 1) volume = 0;

    const uint8_t slice_num = pwm_gpio_to_slice_num(OUT_PIN);
    float clk_div;
    
    #if PROJECT_TYPE == PROJECT_INT
        // Calculate with floating point for accuracy, then round to nearest
        float target_div = (float)(PWM_CLOCK_FREQ / (DUTY + 1)) / (float)freq;
        clk_div = target_div;
        
        // Round to nearest supported divider value
        // RP2040 supports 1-255 with 1/16 fractional steps
        uint32_t div_int = (uint32_t)target_div;
        uint32_t div_frac = (uint32_t)((target_div - div_int) * 16.0f + 0.5f);
        
        if (div_frac >= 16) {
            div_int++;
            div_frac = 0;
        }
        
        clk_div = div_int + (div_frac / 16.0f);
    #else
        // For floating point, still need to account for hardware limitations
        float target_div = ((float)PWM_CLOCK_FREQ / (float)(DUTY + 1)) / freq;
        
        // Quantize to nearest 1/16 step
        uint32_t div_int = (uint32_t)target_div;
        uint32_t div_frac = (uint32_t)((target_div - div_int) * 16.0f + 0.5f);
        
        if (div_frac >= 16) {
            div_int++;
            div_frac = 0;
        }
        
        clk_div = div_int + (div_frac / 16.0f);
    #endif

    // Lower bound check
    if (clk_div < 1.0f) clk_div = 1.0f;
    
    #if DEBUG_MODE == 1
        printf("freq: %f, target_div: %f, actual_div: %f\n", 
               (float)freq, target_div, clk_div);
    #endif

    project_type out_duty = volume_to_duty(volume) * (DUTY / 2);
    
    pwm_set_clkdiv(slice_num, clk_div);
    pwm_set_wrap(slice_num, DUTY);
    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(OUT_PIN), out_duty);
    pwm_set_enabled(slice_num, true);
}

project_type volume_to_duty(uint16_t volume) {
	if (!volume) return 0;
	project_type x = ((project_type) volume) / ((project_type) MAX_VOLUME);
    return (project_type) pow((double) x, (double) CALC_DUTY_POW);
}

uint16_t get_volume(void) {
	static uint16_t diff_buffer[DIFF_BUFFER_SIZE] = {0};
	static uint16_t buffer_index = 0;

	// How many pass threshold
	static uint16_t diff_count = 0;

	static uint16_t last_adc_measure = 0;
	static uint64_t last_time_measure = 0;

	uint16_t new_adc_measure = adc_read() * ADC_PREAMP;
	uint64_t new_time_measure = time_us_64();

	uint16_t new_diff = abs(new_adc_measure - last_adc_measure) / (new_time_measure - last_time_measure);
	diff_buffer[buffer_index] = new_diff;
	buffer_index = (buffer_index + 1) % DIFF_BUFFER_SIZE;

	#if DEBUG_MODE == 1
		(void) printf("diff: %d\n", new_diff);
	#endif

	if (new_diff > DIFF_THRESHOLD) {
		diff_count++;
	}
	if (diff_buffer[buffer_index] > DIFF_THRESHOLD) {
		diff_count--;
	}

	#if DEBUG_MODE == 1
		(void) printf("diff count: %d\n", diff_count);
	#endif

	last_adc_measure = new_adc_measure;
	last_time_measure = new_time_measure;

	/* Volume from diff count:
	 * 0 <= diff_count <= DIFF_COUNT_LOW_THRESHOLD							--> Background noise (ignore)
	 * DIFF_COUNT_LOW_THRESHOLD < diff_count <= DIFF_COUNT_HIGH_THRESHOLD	--> Volume control full spectrum
	 * DIFF_COUNT_HIGH_THRESHOLD < diff_count <= DIFF_BUFFER_SIZE			--> Clip at max volume
	*/

	if (diff_count <= DIFF_COUNT_LOW_THRESHOLD) {
		return 0;
	}
	if (diff_count <= DIFF_COUNT_HIGH_THRESHOLD) {
		return (diff_count - DIFF_COUNT_LOW_THRESHOLD);
	}
	return MAX_VOLUME;
}

uint16_t lowpass_iir(uint16_t new_sample) {
    static float filtered = 0;
    static bool first_run = true;
    
    if (first_run) {
        filtered = new_sample;
        first_run = false;
        return new_sample;
    }
    
    filtered = (ALPHA * new_sample) + ((1.0f - ALPHA) * filtered);
    
    return (uint16_t)filtered;
}

project_type get_frequency(uint8_t button_mask) {
	/* Check for pressed buttons - button 7 modifies the frequency */
	uint8_t base_note = 8;
	bool octave_shift = false;

	for (uint8_t button = 0; button < BUTTON_COUNT - 1; ++button) {
		if ((button_mask >> button) & 1) {
			base_note = button;   // First 0-6 button pressed determines note
			break;
		}
	}
	if (base_note == 8) {
		base_note = 7;
	}
	if ((button_mask >> (BUTTON_COUNT-1)) & 1) {
		octave_shift = true;  // Button 7 pressed - enable 2x frequency
	}

	// Apply octave shift if button 7 is pressed
	if (octave_shift) {
		return ((project_type)(note_frequencies[base_note] * 2));
	} else {
		return note_frequencies[base_note];
	}
}
