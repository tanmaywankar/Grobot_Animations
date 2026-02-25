/*
  Grobot_Animations: BasicEyes Example
  Demonstrates how to initialize Grobot eyes and cycle through emotions.
  Created by Tanmay Wankar, 2026.
*/

#include <TFT_eSPI.h>
#include <Grobot_Animations.h>

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite canvas = TFT_eSprite(&tft);

// Initialize GrobotEyes(eyeColor, backgroundColor)
// 0x97E0 is some kind of Green(looked good to me), 0x0000 is Black
GrobotEyes eyes(0x97E0, 0x0000); 

unsigned long lastSwitch = 0;
int moodIdx = 0; // using a consistent index name

// Switch through built-in moods using the legacy String system
String moods[] = {"NEUTRAL", "HAPPY", "ANGRY", "SAD", "EXCITED", "ANNOYED", "IDLE1", "IDLE2", "IDLE3"};

void setup() {
  tft.init();
  tft.setRotation(1); 
  tft.fillScreen(TFT_BLACK);

  // Create the drawing buffer based 320*240 display (it will scale accordingly based on display size). 
  canvas.createSprite(320, 120);

  eyes.setEmotion("NEUTRAL");
  
  Serial.begin(115200);
  Serial.println("Animations Initialized");
}

void loop() {
  // Cycle moods every 4 seconds
  if (millis() - lastSwitch > 4000) {
    lastSwitch = millis();
    eyes.setEmotion(moods[moodIdx]);
    
    Serial.print("Current Mood: ");
    Serial.println(moods[moodIdx]);

    moodIdx++;
    if (moodIdx > 8) moodIdx = 0;
  }

  // This calculates physics AND pushes the sprite to the physical screen
  eyes.renderEmotions(canvas);

  // Optional: Display HUD (FPS counter)
  eyes.HUD(canvas); 
}