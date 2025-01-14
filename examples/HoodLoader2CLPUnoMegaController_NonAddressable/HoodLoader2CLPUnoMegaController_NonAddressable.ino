/*
   Copyright 2019 Leon Kiefer
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
     http://www.apache.org/licenses/LICENSE-2.0
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

   
   Non-addressable version made Arduino-compatible by Space Yeti Studios.
*/
#include <CorsairLightingProtocol.h>
#include <FastLED.h>

#define RED_PIN1 3
#define GREEN_PIN1 5
#define BLUE_PIN1 6
#define RED_PIN2 9
#define GREEN_PIN2 10
#define BLUE_PIN2 11

CorsairLightingFirmwareStorageEEPROM firmwareStorage;
CorsairLightingFirmware firmware(CORSAIR_LIGHTING_NODE_PRO, &firmwareStorage);
FastLEDControllerStorageEEPROM storage;
FastLEDController ledController(&storage);
CorsairLightingProtocolController cLP(&ledController, &firmware);
CorsairLightingProtocolSerial cHID(&cLP);

CRGB ledsChannel1[10];
CRGB ledsChannel2[10];

// Declare the set4PinLEDs function for Channel 1
void set4PinLEDs(const CRGB& color) {
  analogWrite(RED_PIN1, 255 - color.r);
  analogWrite(GREEN_PIN1, 255 - color.g);
  analogWrite(BLUE_PIN1, 255 - color.b);
}

// Declare the set4PinLEDs function for Channel 2
void set4PinLEDs2(const CRGB& color) {
  analogWrite(RED_PIN2, 255 - color.r);
  analogWrite(GREEN_PIN2, 255 - color.g);
  analogWrite(BLUE_PIN2, 255 - color.b);
}

void setup() {
  cHID.setup();
  pinMode(RED_PIN1, OUTPUT);
  pinMode(GREEN_PIN1, OUTPUT);
  pinMode(BLUE_PIN1, OUTPUT);
  pinMode(RED_PIN2, OUTPUT);
  pinMode(GREEN_PIN2, OUTPUT);
  pinMode(BLUE_PIN2, OUTPUT);

  ledController.addLEDs(0, ledsChannel1, 10);
  ledController.addLEDs(1, ledsChannel1, 10);
  ledController.onUpdateHook(0, []() {
    // use color of first LED of the first channel
    set4PinLEDs(ledsChannel1[0]);
    set4PinLEDs2(ledsChannel1[1]);
  });
}

void loop() {
  cHID.update();
  ledController.updateLEDs();
}

