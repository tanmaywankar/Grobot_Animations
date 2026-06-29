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

uint32_t lastMoodSwitch = 0;
uint32_t moodSwitchInterval = 5000;
int moodIndex = 0; // using a consistent index name

void setup() {
  tft.init();
  tft.setRotation(1); 
  tft.fillScreen(TFT_BLACK);

  // Create the drawing buffer based 320*240 display. do not change it unless you know how it works.(it will scale accordingly based on display size). 
  canvas.createSprite(320, 120);
  //sets initial emotion to be neutral
  eyes.setEmotion(MOOD_NEUTRAL);
  
  Serial.begin(115200);
  Serial.println("Animations Initialized");
}

void loop() {
  // Cycle moods
 moodSwitch(true);
  // This calculates physics AND pushes the sprite to the physical screen
  eyes.renderEmotions(canvas);

  // Optional: Display HUD (FPS counter)
  eyes.HUD(tft); 
}

void moodSwitch(bool toSwitch){
  //employ failsafe mechanisms
  if(!toSwitch) return;
  if(millis() - lastMoodSwitch <= moodSwitchInterval) return;

// Switch through built-in moods
static const MoodData moods[] = {MOOD_NEUTRAL, MOOD_HAPPY, MOOD_ANGRY, MOOD_SAD, MOOD_WINK};
const int numMoods = sizeof(moods)/sizeof(moods[0]);

moodIndex = (moodIndex + 1) % numMoods;

eyes.setEmotion(moods[moodIndex]);
eyes.lookAt(random(-30, 31), random(-20, 21));

lastMoodSwitch = millis();
moodSwitchInterval = random(5000, 8000);

}