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

void generate_square_wave(const project_type freq, const uint16_t volume);
project_type volume_to_duty(uint16_t volume);
project_type get_frequency(const uint8_t mask);
uint16_t get_volume(void);
project_type index_to_note(uint8_t button_index);

// static inline bool button_pressed(uint8_t bitmask, uint8_t button_index) {
//     return (bitmask >> button_index) & 1;
// }

#endif

