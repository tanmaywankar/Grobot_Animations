# Grobot_Animations

A Lightweight, physics-based animation library for robot eyes. Originally designed for the **Grobot** project, this library utilizes **State Machine** logic to create organic, smooth, and expressive eye movements on TFT displays.

Optimized for **ESP32** using the `TFT_eSPI` driver (should work on any other supported device).

---

##  Installation

This library is designed to work within the Arduino IDE ecosystem. Follow these steps to get started:

### Prerequisites
Before installing this library, ensure you have the [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI) library installed and properly configured for your specific display and pinout in your `User_Setup.h`.

### Step-by-Step Setup
1. **Download:** Click the green **Code** button at the top of this repository and select **Download ZIP** you can also download stable release from **Releases** Tab.
2. **Import:** In your Arduino IDE, go to **Sketch** > **Include Library** > **Add .ZIP Library...**
3. **Select:** Choose the `.zip` file you just downloaded.
4. **Restart:** Restart the Arduino IDE to ensure the **Examples** are properly indexed.

---

##  Hardware Requirements

| Component | Specification |
| :--- | :--- |
| **Microcontroller** | ESP32 (all variants) or Pi Pico (all variants) |
| **Display Driver** | ILI9341, ST7789, or any driver supported by TFT_eSPI |
| **Communication** | SPI |



---

##  Supported Moods
You can trigger different expressions by passing these strings to the `setEmotion()` function:

* **Standard:** `NEUTRAL`, `HAPPY`, `ANGRY`, `SAD`, `EXCITED`, `ANNOYED`, `QUESTIONING`
* **Dynamic Idles:** `IDLE1`, `IDLE2`, `IDLE3` (Asymmetrical movements)

---

##  Tested on esp 32 wroom32
Should work on any device that supports `TfT_eSPI` library.

---

##  Repository Structure
* **`src/`**: Core library files (`Grobot_Animations.h`, `Grobot_Animations.cpp`).
* **`examples/`**: Contains `BasicEye.ino` which demonstrates the full cycle of moods along with other Examples.
* **`src/Moods.h`**: Can be used to define custom moods.

---

##  Integration Details
To use this library in your own project, simply initialize the `GrobotEyes` class and call the render function in your main loop.

> **Note:** For flicker-free animations, this library utilizes **TFT_eSprite** buffers. Ensure your microcontroller has enough RAM to support the sprite size defined in your sketch.

---

##  License
This project is licensed under the **MIT License**. You are free to use, modify, and distribute this code for personal or commercial projects. See the [LICENSE](LICENSE) file for details.

---

**Author:** [Tanmay Wankar](https://github.com/tanmaywankar)  
