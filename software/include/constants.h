#ifndef CONSTANTS_H
#define CONSTANTS_H

#ifndef DEBUG_MODE
    #define DEBUG_MODE 0
#endif

#define BUTTON_COUNT		    ((uint8_t) 8)
#define DUTY				    ((uint32_t) 65535)

#define PWM_CLOCK_FREQ		    ((double) 125000000.0)
             
/* Volume calculation */
#define CALC_DUTY_POW		    ((double) 2.2) 

// Smoothing factor for volume (0.0 - 1.0)
#define ALPHA                   ((float) 0.002f)              // <-- tuning

#define ADC_PREAMP			    ((uint16_t) 100)	        // <-- tuning
#define DIFF_THRESHOLD		    ((uint16_t) 100)	        // <-- tuning

#define DIFF_BUFFER_SIZE	        ((uint16_t)	100)	    // <-- tuning
#define DIFF_COUNT_LOW_THRESHOLD	((uint16_t) 20)         // <-- tuning
#define DIFF_COUNT_HIGH_THRESHOLD	((uint16_t) 80)         // <-- tuning

#define MAX_VOLUME			    (DIFF_COUNT_HIGH_THRESHOLD - DIFF_COUNT_LOW_THRESHOLD)

#endif // CONSTANTS_H
