#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"

#include "notes.h"
#include "pins.h"
#include "constants.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

void generate_square_wave(const float freq, const uint16_t volume);
uint16_t volume_to_duty(uint16_t volume);
float get_frequency(uint8_t button_mask);
uint16_t get_volume(void);
uint16_t lowpass_iir(uint16_t new_sample);

#endif // FUNCTIONS_H
