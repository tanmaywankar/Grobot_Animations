#ifndef GROBOT_ANIMATIONS_H
#define GROBOT_ANIMATIONS_H
#include "Moods.h"
#include "Animation_config.h"
#include <Arduino.h>
#include <TFT_eSPI.h>

//eye state definitions for easy emotion switching

struct EyeState {
  float topH;
  float botH; 
  float tilt;  
  float pR;
  float eyeRadius;

  //velocities for spring motion

  float vTop;
  float vBot;
  float vTilt;
  float vPR;
  float veyeRadius;
};

class GrobotEyes{
    public:
        GrobotEyes(uint16_t eyeColor, uint16_t bgColor);
        void setEmotion(MoodData mood);
        void setEmotion(MoodData left, MoodData right);
        void setEmotion(String moodName);
        void renderEmotions(TFT_eSprite &canvas);
        void HUD(TFT_eSPI &canvas);
        void updateDeltaTime();
        void blink();
        void lookAt(int x, int y);
        void moodSwitch(bool toSwitch);
    
    private:

        // //the state that we are currently in
        EyeState currentR, currentL;
        //the state that we are want to transition to
        EyeState targetL, targetR;
        //the base state of an emotion, so that blinking wont affect the angry eyes
        EyeState baseL, baseR;


        //eye definitons
        //light green color for grobot's inner eye 
        //it looks way different on my tft and pc so you might need to change it as per your needs
        uint16_t _eyeColor, _bgColor;
        float eyeRadius;
        int eyeGap;
        int eyeOffset;

        //eyelid definition
        unsigned long lastBlinkTime = 0;
        int blinkTime;
        int blinkDelay;

        //adding Delta Time so as to maintain fluidity no matter the fps
        unsigned long lastFrameTime = 0;
        float dT = 0;
        float currentFPS = 0;

        //canvas movement, for eyes
        float canvasX = 0, canvasY = 0;
        float targetCanvasX = 0, targetCanvasY = 0;
        float vCanvasX = 0, vCanvasY = 0;

        //emotion logics
        unsigned long lastMoodSwitch = 0;
        int moodIndex = 0;
        unsigned long switchInterval;

        void setBase(EyeState &eye, float top, float bot, float tilt, float pR, float radius);
        void drawEye(TFT_eSprite &canvas, int eX, int eY, int pR, int eyeRadius, int lidH, int botH, int tilt, bool isLeft);
        void applySpring(float &current, float &velocity, float target, float dt, float stiffness= DEFAULT_STIFFNESS, float damping = DEFAULT_DAMPING);

};

#endif