
#ifndef ANIMATION_CONFIG_H
#define ANIMATION_CONFIG_H

/*
All the values here have been put based on a standard 2.4" ili9341 display
if using display with other dimensions then please change the values as required
*/


//change these values as per your device size and requirements
#define DEFAULT_EYE_RADIUS 45
#define DEFAULT_PUPIL_RADIUS 30
#define DEFAULT_EYE_GAP 20
//the height of the base canvas (use it to change the scaling up or down)
//default is 120.0
#define BASE_DESIGN_HEIGHT 120.0

//your screen dimensions
#define PHYSICAL_SCREEN_HEIGHT 240.0
#define PHYSICAL_SCREEN_WIDTH 320.0

//animation Defaults
#define DEFAULT_STIFFNESS 180.0
#define DEFAULT_DAMPING 15.0
#define DEFAULT_BLINK_TIME 3000
#define DEFAULT_BLINK_DELAY 200

//for animating the actual canvas 
#define CANVAS_STIFFNESS 140.0
#define CANVAS_DAMPING  18.0

//interval between the moods change
#define DEFAULT_MOOD_INTERVAL 5000


#endif