#ifndef NOTES_H
#define NOTES_H

// Note Frequencies [Hz]
#define NOTE_C4   261.63f
#define NOTE_CS4  277.18f
#define NOTE_D4   293.66f
#define NOTE_DS4  311.13f
#define NOTE_E4   329.63f
#define NOTE_F4   349.23f
#define NOTE_FS4  369.99f
#define NOTE_G4   392.00f
#define NOTE_GS4  415.30f
#define NOTE_A4   440.00f
#define NOTE_AS4  466.16f
#define NOTE_B4   493.88f
#define NOTE_C5   523.25f
#define NOTE_CS5  554.37f

// Lookup table for button index to note conversion
static const float note_frequencies[8] = {
    NOTE_C4,
    NOTE_D4,
    NOTE_E4,
    NOTE_F4,
    NOTE_G4, 
    NOTE_A4,
    NOTE_B4,
    NOTE_C5
};

#endif // NOTES_H
