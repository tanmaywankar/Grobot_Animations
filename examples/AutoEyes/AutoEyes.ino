/*
  Grobot_Animations: AutoEyes Example
  Demonstrates how to use the simplest moodSwitch function.
  Created by Tanmay Wankar, 2026.
*/

#include <TFT_eSPI.h>
#include <Grobot_Animations.h>

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite canvas = TFT_eSprite(&tft);

// Initialize GrobotEyes(eyeColor, backgroundColor)
// 0x97E0 is some lighter shade of green , 0x0000 is Black
GrobotEyes eyes(0x97E0, 0x0000); 

void setup() {
  tft.init();
  tft.setRotation(1); 
  tft.fillScreen(TFT_BLACK);

  // Create the drawing buffer based 320*240 display. do not change it unless you know how it works.(it will scale accordingly based on display size). 
  canvas.createSprite(320, 120);
  //sets initial emotion to be neutral
  eyes.setEmotion("NEUTRAL");
  
  Serial.begin(115200);
  Serial.println("Tnitializing Auto mood switch");
}

void loop() {
  //Use the built-in moodSwitch function to swithc between available moods  
  eyes.moodSwitch();  
  // This calculates physics AND pushes the sprite to the physical screen
  eyes.renderEmotions(canvas);
  // Optional: Display HUD (FPS counter)
  eyes.HUD(tft); 
}