#include "Grobot_Animations.h"


//initializing the constructor function
GrobotEyes::GrobotEyes(uint16_t eyeColor, uint16_t bgColor) 
  : _eyeColor(eyeColor), _bgColor(bgColor){

    lastFrameTime = millis();

    //declaring variable values 
    blinkTime = 3000;
    blinkDelay = 200;
    eyeOffset = eyeRadius + eyeGap;


// Setting up initial "Eye" states so they aren't empty
    currentL = {0, 0, 0, 30, 45, 0, 0, 0, 0, 0};
    currentR = currentL;
    targetL  = currentL;
    targetR  = currentL;
    baseL    = currentL;
    baseR    = currentL;

  }

//adding spring physics
void GrobotEyes::applySpring(float &current, float &velocity, float target, float dt, float stiffness, float damping){
  // float stiffness= 180.0;
  // float damping = 15.0;
  //hookes law f = -kx
  float force = (target-current) * stiffness;
  
  //adds damping cuz we can't bounce forever
  velocity += (force - (velocity * damping)) * dt;

  current += velocity * dt;
}

//used to maintain constant speed in case of fps fluctuation
void  GrobotEyes::updateDeltaTime(){
  //code for delta time calculation
  unsigned long currentMillis = millis();
  dT = (currentMillis - lastFrameTime) / 1000.0; 
  lastFrameTime = currentMillis;
  //fps logic
  if (dT > 0) {
    // We use a slight lerp here too so the number doesn't flicker too fast
    float instantFPS = 1.0 / dT;
    currentFPS = currentFPS + (instantFPS - currentFPS) * 0.1; 
  }
}

//to draw the actual eyes left and right
void GrobotEyes::drawEye(TFT_eSprite &canvas, int eX, int eY, int pR, int eyeRadius, int lidH, int botH, int tilt, bool isLeft){

  // int lookX = eX + offX;
  // int lookY = eY + offY;


  canvas.fillCircle(eX, eY, eyeRadius, _eyeColor);
  canvas.fillCircle(eX, eY, pR, _bgColor);
  canvas.fillRect(eX - eyeRadius, eY - eyeRadius, (eyeRadius * 2)+10, lidH, _bgColor);

  if (isLeft) {

    int pointX = (tilt < 0) ? (eX - eyeRadius) : (eX + eyeRadius);

    canvas.fillTriangle(
      eX - eyeRadius, eY - eyeRadius + lidH,         // Top Left (Flat)
      eX + eyeRadius, eY - eyeRadius + lidH,         // Top Right (Flat)
      pointX, eY - eyeRadius + lidH + abs(tilt),  // Bottom Right (The Pointy bit)
      _bgColor
    );
  } else {
    // Right Eye: The "Anger Point" is on the LEFT side (near the nose)
    int pointX = (tilt < 0) ? (eX + eyeRadius) : (eX - eyeRadius);

    canvas.fillTriangle(
      eX - eyeRadius, eY - eyeRadius + lidH,         // Top Left (Flat)
      eX + eyeRadius, eY - eyeRadius + lidH,         // Top Right (Flat)
      pointX, eY - eyeRadius + lidH + abs(tilt),  // Bottom Left (The Pointy bit)
      _bgColor
    );
  }
 canvas.fillRect(
  eX - eyeRadius - 5,
  eY + (eyeRadius + 5) - botH,
  (eyeRadius * 2) + 10,
  botH,
  _bgColor
  );
}

//rendering the actual animation including eyes, blink and also spring physics
void GrobotEyes::renderEmotions(TFT_eSprite &canvas){
  
  updateDeltaTime();
  //fill bg black eyery refresh so that thre aint no trail behind
  canvas.fillSprite(_bgColor);
  blink();
  //entire canvas 
  applySpring(canvasX, vCanvasX, targetCanvasX, dT, 140.0, 18);
  applySpring(canvasY, vCanvasY, targetCanvasY, dT, 140.0, 18);
 // LEFT EYE: Apply spring physics to everything
  applySpring(currentL.topH, currentL.vTop,  targetL.topH,  dT);
  applySpring(currentL.botH, currentL.vBot,  targetL.botH,  dT);
  applySpring(currentL.tilt, currentL.vTilt, targetL.tilt,  dT);
  applySpring(currentL.pR, currentL.vPR,   targetL.pR,    dT, 180.0, 22);
  applySpring(currentL.eyeRadius, currentL.veyeRadius, targetL.eyeRadius, dT);
  // RIGHT EYE: Apply spring physics to everything
  applySpring(currentR.topH, currentR.vTop,  targetR.topH,  dT);
  applySpring(currentR.botH, currentR.vBot,  targetR.botH,  dT); 
  applySpring(currentR.tilt, currentR.vTilt, targetR.tilt,  dT);
  applySpring(currentR.pR, currentR.vPR,   targetR.pR, dT, 180.0, 22);
  applySpring(currentR.eyeRadius, currentR.veyeRadius, targetR.eyeRadius, dT);

  // drawing actual eyes
  drawEye(canvas, 160 - eyeOffset, eyeY, (int)currentL.pR, (int)currentL.eyeRadius, (int)currentL.topH, (int)currentL.botH, (int)currentL.tilt, true);
  drawEye(canvas, 160 + eyeOffset, eyeY, (int)currentR.pR, (int)currentR.eyeRadius, (int)currentR.topH, (int)currentR.botH, (int)currentR.tilt, false);

  canvas.pushSprite((int)canvasX, (int)canvasY);

}

//contains the final state of given emotion.
void GrobotEyes::setEmotion(String mood) {
  if (mood == "NEUTRAL") {
    setBase(baseL, 0, 0, 0, 30, 45); 
    setBase(baseR, 0, 0, 0, 30, 45);
  } 
  else if (mood == "HAPPY") {
    setBase(baseL, 0, 50, 0, 30, 45); 
    setBase(baseR, 0, 50, 0, 30, 45);
  } 
  else if (mood == "ANGRY") {
    setBase(baseL, 0, 0, 60, 30, 45); 
    setBase(baseR, 0, 0, 60, 30, 45);
  }
  else if (mood == "SAD"){
  setBase(baseL, 0, 0, -60, 27, 45); 
  setBase(baseR, 0, 0, -60, 27, 45);
  }
  else if (mood == "EXCITED"){
    setBase(baseL, 0, 0, 0, 23, 45); 
    setBase(baseR, 0, 0, 0, 23, 45);
  }
  else if (mood == "IDLE3") {
    setBase(baseL, 35, 35, 0, 0, 45); 
    setBase(baseR, 35, 35, 0, 0, 45);
  }
  else if (mood == "ANNOYED") {
    setBase(baseL, 0, 35, 25, 0, 45); 
    setBase(baseR, 0, 35, 25, 0, 45);
  }
  else if (mood == "QUESTIONING") {
    setBase(baseL, 0, 0, 0, 30, 45); 
    setBase(baseR, 50, 0, 0, 30, 45);
  } 
  else if (mood == "IDLE1") {
    setBase(baseL, 0, 0, 0, 30, 45); 
    setBase(baseR, 0, 0, 0, 15, 30);
  }
  else if (mood == "IDLE2") {
    setBase(baseL, 0, 0, 0, 15, 30);
    setBase(baseR, 0, 0, 0, 30, 45); 
  }

  // Sync targets with the new base mood
  targetL = baseL;
  targetR = baseR;
}

//to set base values of variables that are not declared directly while setting the mood
void GrobotEyes::setBase(EyeState &eye, float top, float bot, float tilt, float pR, float radius) {
    eye.topH = top;
    eye.botH = bot;
    eye.tilt = tilt;
    eye.pR = pR;
    eye.eyeRadius = radius;
    // We explicitly reset velocities so a mood switch 
    // doesn't carry over old momentum
    eye.vTop = eye.vBot = eye.vTilt = eye.vPR = eye.veyeRadius = 0;
}


void GrobotEyes::blink(){
  unsigned long now = millis();

  if(now - lastBlinkTime > blinkTime){
    targetL.topH = 100;
    targetR.topH = 100;
  }
  if(now - lastBlinkTime > blinkTime + blinkDelay){
    targetL.topH = baseL.topH; 
    targetR.topH = baseR.topH;
    lastBlinkTime = now;
    //make blinking
      blinkDelay = random(200, 400);
      blinkTime = random(4000, 15000); 

  }
  
}

//just a basic loop for demo purpose, needs to be optimized (will do later)
void GrobotEyes::moodSwitch(bool toSwitch){
  if(toSwitch){
     if (millis() - lastMoodSwitch > switchInterval) {
    moodIndex++;
    if (moodIndex > 9) moodIndex = 0; // Reset mood

    if (moodIndex == 0) setEmotion("NEUTRAL");
    else if (moodIndex == 1) setEmotion("HAPPY");
    else if (moodIndex == 2) setEmotion("ANGRY");
    else if (moodIndex == 3) setEmotion("SAD");
    else if (moodIndex == 4) setEmotion("EXCITED");
    else if (moodIndex == 5) setEmotion("ANNOYED");
    else if (moodIndex == 6) setEmotion("QUESTIONING");
    else if (moodIndex == 7) setEmotion("IDLE1");
    else if (moodIndex == 8) setEmotion("IDLE2");
    else if (moodIndex == 9) setEmotion("IDLE3");
    lookAt(random(-30, 31), random(-20, 21));
    lastMoodSwitch = millis();
    
    // Randomize the NEXT interval for variety (10s to 15s)
    switchInterval = random(5000, 8000);
  }
 
  }

}

void GrobotEyes::lookAt(int x, int y) {
  targetCanvasX = x; 
  targetCanvasY = 60 + y; 
}


void GrobotEyes::HUD(TFT_eSPI &tft){
  tft.setCursor(5, 5); // This is now 5 pixels from the physical top
  tft.setTextColor(TFT_WHITE, TFT_BLACK); 
  tft.setTextSize(1);
  tft.print("FPS: ");
  tft.print((int)currentFPS);
}
