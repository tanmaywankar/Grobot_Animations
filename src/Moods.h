#ifndef MOODS_H
#define MOODS_H

struct MoodData {
    float topH;
    float botH;
    float tilt;
    float pR;
    float radius;
};

// Preset Moods - You can add more here 
const MoodData MOOD_NEUTRAL     = {0, 0, 0, 30, 45};
const MoodData MOOD_HAPPY       = {0, 50, 0, 30, 45};
const MoodData MOOD_ANGRY       = {0, 0, 60, 30, 45};
const MoodData MOOD_SAD         = {0, 0, -60, 27, 45};
const MoodData MOOD_EXCITED     = {0, 0, 0, 23, 45};
const MoodData MOOD_ANNOYED     = {0, 35, 25, 0, 45};
const MoodData MOOD_QUESTIONING_L = {0, 0, 0, 30, 45};
const MoodData MOOD_QUESTIONING_R = {50, 0, 0, 30, 45};

#endif