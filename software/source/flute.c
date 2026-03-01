#include "functions.h"

#define ALPHA 0.9f  // Smoothing factor (0.0 - 1.0)

uint16_t lowpass_iir(uint16_t new_sample) {
    static float filtered = 0;
    static bool first_run = true;
    
    if (first_run) {
        filtered = new_sample;
        first_run = false;
        return new_sample;
    }
    
    // IIR filter: y[n] = α * x[n] + (1-α) * y[n-1]
    filtered = (ALPHA * new_sample) + ((1.0f - ALPHA) * filtered);
    
    return (uint16_t)filtered;
}

int main(void) {
	// stdio_init_all();

    const uint16_t buttons[BUTTON_COUNT] = {BUTTON1, BUTTON2, BUTTON3, BUTTON4, BUTTON5, BUTTON6, BUTTON7, BUTTON8};

    for (register uint8_t i = 0; i < BUTTON_COUNT; ++i) {
		gpio_init(buttons[i]);
		gpio_set_dir(buttons[i], GPIO_IN);
		gpio_pull_up(buttons[i]);
    }

    adc_init();
    adc_gpio_init(ADC26);
    adc_select_input(0);

	gpio_init(OUT_PIN);
    gpio_set_function(OUT_PIN, GPIO_FUNC_PWM);

    uint8_t button_mask;

    while (true) {
		button_mask = 0;
		for (register uint8_t i = 0; i < BUTTON_COUNT; ++i) {
			if (gpio_get(buttons[i])) {
				button_mask |= (1 << i);
			}
		}
		generate_square_wave(get_frequency(button_mask)/4, lowpass_iir(get_volume()));
		// generate_square_wave(get_frequency(button _mask), 50);

		// sleep_us(1);	// slow down work to reduce power consumed
	}

    return EXIT_SUCCESS;
}

