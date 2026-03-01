#ifndef NOTES_H
#define NOTES_H

#include "types.h"

// Note Frequencies [Hz]
#if PROJECT_TYPE == PROJECT_INT
    #define NOTE_C4     ((project_type) 262)
    #define NOTE_CS4    ((project_type) 277)
    #define NOTE_D4     ((project_type) 294)
    #define NOTE_DS4    ((project_type) 311)
    #define NOTE_E4     ((project_type) 330)
    #define NOTE_F4     ((project_type) 349)
    #define NOTE_FS4    ((project_type) 370)
    #define NOTE_G4     ((project_type) 392)
    #define NOTE_GS4    ((project_type) 415)
    #define NOTE_A4     ((project_type) 440)
    #define NOTE_AS4    ((project_type) 466)
    #define NOTE_B4     ((project_type) 494)
    #define NOTE_C5     ((project_type) 523)
    #define NOTE_D5     ((project_type) 587)
#elif PROJECT_TYPE == PROJECT_FLOAT
    #define NOTE_C4     ((project_type) 261.63)
    #define NOTE_CS4    ((project_type) 277.18)
    #define NOTE_D4     ((project_type) 293.66)
    #define NOTE_DS4    ((project_type) 311.13)
    #define NOTE_E4     ((project_type) 329.63)
    #define NOTE_F4     ((project_type) 349.23)
    #define NOTE_FS4    ((project_type) 369.99)
    #define NOTE_G4     ((project_type) 392.00)
    #define NOTE_GS4    ((project_type) 415.30)
    #define NOTE_A4     ((project_type) 440.00)
    #define NOTE_AS4    ((project_type) 466.16)
    #define NOTE_B4     ((project_type) 493.88)
    #define NOTE_C5     ((project_type) 523.25)
    #define NOTE_D5     ((project_type) 587.33)
#endif

// Lookup table for button index to note conversion
#if PROJECT_TYPE == PROJECT_INT
    static const project_type note_frequencies[] = {
        NOTE_C4,  // 0: C4 (262 Hz)
        NOTE_D4,  // 1: D4 (294 Hz)
        NOTE_E4,  // 2: E4 (330 Hz)
        NOTE_F4,  // 3: F4 (349 Hz)
        NOTE_G4,  // 4: G4 (392 Hz)
        NOTE_A4,  // 5: A4 (440 Hz)
        NOTE_B4,  // 6: B4 (494 Hz)
        NOTE_C5   // 7: C5 (523 Hz)
    };
#elif PROJECT_TYPE == PROJECT_FLOAT
    static const project_type note_frequencies[] = {
        NOTE_C4,  // 0: C4 (261.63 Hz)
        NOTE_D4,  // 1: D4 (293.66 Hz)
        NOTE_E4,  // 2: E4 (329.63 Hz)
        NOTE_F4,  // 3: F4 (349.23 Hz)
        NOTE_G4,  // 4: G4 (392.00 Hz)
        NOTE_A4,  // 5: A4 (440.00 Hz)
        NOTE_B4,  // 6: B4 (493.88 Hz)
        NOTE_C5   // 7: C5 (523.25 Hz)
    };
#endif

#endif // NOTES_H
