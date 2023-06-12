/*
 * Project lightTests
 * Description: Light tests for the NM Park Bench Project
 * Author: KD Neeley
 * Date: 06/11/2023
 */
#include <LPD8806.h> 


const int NLEDS = 160; // Number of LEDs
const int CLKPIN = 14; //Clock In Pin
const int DPIN = 15; //Data In Pin

LPD8806 lights = LPD8806(NLEDS, CLKPIN, DPIN);

void setup() {
    lights.begin();
    lights.show();
}

void loop() {
    for(int i=0; i<NLEDS; i++) {
        lights.setPixelColor(i, 255, 255, 255);
        lights.show();
    }
}







