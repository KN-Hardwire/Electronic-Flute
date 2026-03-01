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
	#define RETURN_VALUE_JUMP 1
	static uint16_t return_value = 0;
	static bool first_return = true;

	// How many pass threshold
	static uint16_t diff_count = 0;

	static uint16_t last_adc_measure = 0;
	static uint64_t last_time_measure = 0;

	static uint16_t filter_buffer[FILTER_BUFFER_SIZE];
	static uint16_t filter_buffer_idx = 0;

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
	 * 0 <= diff_count <= DIFF_COUNT_THRESHOLD				--> Background noise
	 * DIFF_COUNT_THRESHOLD < diff_count <= DIFF_COUNT_MAX	--> Volume control full spectrum
	 * DIFF_COUNT_MAX < diff_count <= DIFF_BUFFER_SIZE		--> Round to max volume
	 */

	if (first_return) {
		first_return = false;
		return 0;
	}

	// VERSION OG
	if (diff_count <= DIFF_COUNT_THRESHOLD) {
		return 0;
	}

	if (diff_count <= DIFF_COUNT_MAX) {
		return (diff_count - DIFF_COUNT_THRESHOLD);
	}

	// return MAX_VOLUME;

	// PROTOTYPE VERSION 1
	// uint16_t tmp = diff_count;
	// if (tmp <= DIFF_COUNT_THRESHOLD) {
	// 	tmp = 0;
	// } else if (tmp <= DIFF_COUNT_MAX) {
	// 	tmp = (tmp - DIFF_COUNT_THRESHOLD);
	// } else {
	// 	tmp = MAX_VOLUME;
	// }
	//
	// if (tmp > return_value) {
	// 	return_value += RETURN_VALUE_JUMP;
	// } else if (tmp < return_value) {
	// 	if (tmp <= RETURN_VALUE_JUMP) {
	// 		return_value = 0;
	// 	} else {
	// 		return_value -= RETURN_VALUE_JUMP;
	// 	}
	// }
	// if (return_value > MAX_VOLUME) {
	// 	return_value = MAX_VOLUME;
	// }

	// return return_value;

	// PROTOTYPE VERSION 2
	// uint16_t tmp = diff_count;
	// if (tmp <= DIFF_COUNT_THRESHOLD) {
	// 	// tmp < low_thresh
	// 	tmp = 0;
	// // } else if (tmp <= DIFF_COUNT_MAX) {
	// // 	// low_thresh < tmp < max_thresh
	// // 	tmp = MID_VOLUME;
	// } else { // max_thresh < tmp
	// 	tmp = MAX_VOLUME;
	// }

	// return tmp
	
	// filter_buffer[filter_buffer_idx] = tmp;
	// filter_buffer_idx = (filter_buffer_idx + 1)%FILTER_BUFFER_SIZE;

	// uint16_t zero_count = 0;
	// uint16_t mid_count = 0;
	// uint16_t max_count = 0;
	// for(uint16_t i = 0; i<FILTER_BUFFER_SIZE; i++){
	// 	switch(filter_buffer[i]){
	// 		case 0:
	// 			zero_count++;
	// 			break;
	// 		case MID_VOLUME:
	// 			mid_count++;
	// 			break;
	// 		case MAX_VOLUME:
	// 			max_count++;
	// 			break;
		
	// 	}
	// }

	// if (zero_count>max_count&&zero_count>mid_count){
	// 	return 0;
	// } else if (mid_count>max_count&&mid_count>max_count){
	//  	return MID_VOLUME;
	// } else if (max_count>zero_count&&max_count>mid_count){
	// 	return MAX_VOLUME;
	// } else {
	// 	return 0;
	// }
	


	// if (tmp > return_value) {
	// 	return_value += RETURN_VALUE_JUMP;
	// } else if (tmp < return_value) {
	// 	if (tmp <= RETURN_VALUE_JUMP) {
	// 		return_value = 0;
	// 	} else {
	// 		return_value -= RETURN_VALUE_JUMP;
	// 	}
	// }
	// if (return_value > MAX_VOLUME) {
	// 	return_value = MAX_VOLUME;
	// }
	
}

// uint16_t get_volume(void) {
//     static uint16_t diff_buffer[DIFF_BUFFER_SIZE] = {0};
//     static uint16_t buffer_index = 0;
//     static uint16_t diff_count = 0;
//     static uint16_t last_adc_measure = 0;
//     static uint64_t last_time_measure = 0;
    
//     // SMOOTHING 1: Filter the raw ADC input
//     static uint16_t filtered_adc = 0;
//     static bool first_run = true;
    
//     uint16_t new_adc_measure = adc_read() * ADC_PREAMP;
    
//     // Exponential moving average on ADC
//     if (first_run) {
//         filtered_adc = new_adc_measure;
//         first_run = false;
//     } else {
//         // 90% old, 10% new - heavy smoothing
//         filtered_adc = (filtered_adc * 9 + new_adc_measure) / 10;
//     }
    
//     uint64_t new_time_measure = time_us_64();
    
//     // Skip first reading
//     if (last_time_measure == 0) {
//         last_adc_measure = filtered_adc;
//         last_time_measure = new_time_measure;
//         return 0;
//     }
    
//     // Calculate time difference with minimum protection
//     uint64_t time_diff = new_time_measure - last_time_measure;
//     if (time_diff < 100) time_diff = 100;  // Prevent division by tiny numbers
    
//     // SMOOTHING 2: Use filtered ADC for difference
//     uint16_t new_diff = abs(filtered_adc - last_adc_measure) / time_diff;
    
//     // SMOOTHING 3: Limit maximum change per sample
//     #define MAX_DIFF_CHANGE 10
//     static uint16_t last_diff = 0;
//     if (abs(new_diff - last_diff) > MAX_DIFF_CHANGE) {
//         if (new_diff > last_diff) {
//             new_diff = last_diff + MAX_DIFF_CHANGE;
//         } else {
//             new_diff = last_diff - MAX_DIFF_CHANGE;
//         }
//     }
//     last_diff = new_diff;
    
//     // Update circular buffer
//     diff_buffer[buffer_index] = new_diff;
//     buffer_index = (buffer_index + 1) % DIFF_BUFFER_SIZE;
    
//     // Update diff_count
//     if (new_diff > DIFF_THRESHOLD) {
//         if (diff_count < DIFF_BUFFER_SIZE) diff_count++;
//     }
//     if (diff_buffer[buffer_index] > DIFF_THRESHOLD) {
//         if (diff_count > 0) diff_count--;
//     }
    
//     last_adc_measure = filtered_adc;
//     last_time_measure = new_time_measure;
    
//     // SMOOTHING 4: Apply IIR filter to the final volume
//     static uint16_t smoothed_volume = 0;
//     uint16_t raw_volume;
    
//     // Calculate raw volume
//     if (diff_count <= DIFF_COUNT_THRESHOLD) {
//         raw_volume = 0;
//     } else if (diff_count <= DIFF_COUNT_MAX) {
//         raw_volume = (diff_count - DIFF_COUNT_THRESHOLD);
//     } else {
//         raw_volume = MAX_VOLUME;
//     }
    
//     // SMOOTHING 5: Exponential moving average on volume
//     // 80% old, 20% new - adjustable for response speed
//     #define VOLUME_SMOOTHING 4  // 1 = fastest, higher = smoother
    
//     if (smoothed_volume == 0) {
//         smoothed_volume = raw_volume;
//     } else {
//         smoothed_volume = (smoothed_volume * (VOLUME_SMOOTHING * 2) + 
//                           raw_volume * 2) / ((VOLUME_SMOOTHING * 2) + 2);
//     }
    
//     // SMOOTHING 6: Add hysteresis to prevent jitter near thresholds
//     #define HYSTERESIS 1
//     static uint16_t last_returned = 0;
//     if (abs(smoothed_volume - last_returned) > HYSTERESIS) {
//         last_returned = smoothed_volume;
//     }
    
//     return last_returned;
// }

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
