#include <TFT_eSPI.h>
#include <Grobot_Animations.h>

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite canvas = TFT_eSprite(&tft);

// Initialize with a Blue Eye 
GrobotEyes eyes(TFT_BLUE, TFT_BLACK); 

void setup() {
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  canvas.createSprite(320, 120);
  
  // Start Neutral
  eyes.setEmotion(MOOD_NEUTRAL);
}

void loop() {
  static unsigned long lastChange = 0;
  static int stage = 0;

  if (millis() - lastChange > 2500) {
    lastChange = millis();
    stage++;
    if (stage > 3) stage = 0;

    switch(stage) {
      case 0: 
        // 1. Standard Symmetric Mood
        eyes.setEmotion(MOOD_NEUTRAL; 
        break;

      case 1: 
        // 2. Asymmetric Mood: The "Wink"
        // Left eye stays Neutral, Right eye uses our new Closed struct
        eyes.setEmotion(MOOD_NEUTRAL, MOOD_WINK); 
        break;

      case 2: 
        // 3. Mixing Preset Moods
        // Make the robot look "Confused" (Happy Left, Sad Right)
        eyes.setEmotion(MOOD_HAPPY, MOOD_SAD); 
        break;

      case 3:
        eyes.setEmotion(MOOD_NEUTRAL);
        break;
    }
  }

  eyes.renderEmotions(canvas);
}