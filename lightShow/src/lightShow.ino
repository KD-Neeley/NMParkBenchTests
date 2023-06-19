/*
 * Project lightShow
 * Description: experimenting with light effects to go with the MSGEQ7
 * Author: KD Neeley
 * Date: 06/14/2023

 Arduino Connections on the MSGEQ7:
 - GND to GND on MSGEQ7
 - 5V to VDD on MSGEQ7
 - A3 to OUT on MSGEQ7 
 - D7 to STROBE on MSGEQ7
 - D8 to RESET on MSGEQ7
  */

#include <LPD8806.h> 
#include <SPI.h>
#include "kdsRainbows.h"

//Pins for the MSGEQ7
const int MSGEQ7_STROBE_PIN =    7;
const int MSGEQ7_RESET_PIN =     8;
const int MSGEQ7_ANALOG_PIN =   16;
const int NUM_FREQUENCY_BANDS =  7;

//Globals for the MSGEQ7
int volumeInBand[NUM_FREQUENCY_BANDS];
int minimumVolume, maximumVolume;
int band1, band2, band3, band4, band5, band6, band7;


//PINS and Constants for the Lights
const int NLEDS = 324; // Number of LEDs
const int CLKPIN = 14; //Clock In Pin
const int DPIN = 15; //Data In Pin
const int MULTIPLE = 4;
const int OFFSETDELTA = 2;

//Globals for the lights
int numArray[NLEDS];
int offset = 0;
int displayLight;

//declare object for the lights
LPD8806 lights = LPD8806(NLEDS, CLKPIN, DPIN);

//functions
int pixelFill (int startPixel, int endPixel, int hexColor); 
void cycle(unsigned int offset, unsigned int s, unsigned int v);
uint32_t hsvToColour(unsigned int h, unsigned int s, unsigned int v);
int maxRead(int band);

void setup() {
  Serial.begin(9600);
  waitFor(Serial.isConnected, 15000);

  // Set up the MSGEQ7 IC
  pinMode(MSGEQ7_ANALOG_PIN, INPUT);
  pinMode(MSGEQ7_STROBE_PIN, OUTPUT);
  pinMode(MSGEQ7_RESET_PIN, OUTPUT);
  digitalWrite(MSGEQ7_RESET_PIN, LOW);
  digitalWrite(MSGEQ7_STROBE_PIN, HIGH);

  // Initialize the minimum and maximum volume levels
  minimumVolume = 1023;
  maximumVolume = 0;

  //setup the lights
  lights.begin();
  lights.show();
}

void loop() {

// Toggle the RESET pin of the MSGEQ7 to start reading from the lowest frequency band
  digitalWrite(MSGEQ7_RESET_PIN, HIGH);
  digitalWrite(MSGEQ7_RESET_PIN, LOW);

    // Read the volume in every frequency band from the MSGEQ7
    //save the reading to each respective band
      for (int i=0; i<NUM_FREQUENCY_BANDS; i++) {
        digitalWrite(MSGEQ7_STROBE_PIN, LOW);
        delayMicroseconds(30); // Allow the output to settle
        volumeInBand[i] = analogRead(MSGEQ7_ANALOG_PIN);
        digitalWrite(MSGEQ7_STROBE_PIN, HIGH);
        band1 = volumeInBand[0];
        band2 = volumeInBand[1];
        band3 = volumeInBand[2];
        band4 = volumeInBand[3];
        band5 = volumeInBand[4];
        band6 = volumeInBand[5];
        band7 = volumeInBand[6];
        displayLight = maxRead(band1);
      }
  //end thread here

  Serial.printf("Band1 = %i\n", band1);
  Serial.printf("Band2 = %i\n", band2);
  Serial.printf("Band3 = %i\n", band3);
  Serial.printf("Band4 = %i\n", band4);
  Serial.printf("Band5 = %i\n", band5);
  Serial.printf("Band6 = %i\n", band6);
  Serial.printf("Band7 = %i\n", band7);

  if(displayLight == band1) {
  //purple
  pixelFill(0, NLEDS-1, purple);
  }
  if(displayLight == band2) {
  //blue
   pixelFill(0, NLEDS-1, fullblue);
  }
  if(displayLight == band3) {
  //red
   pixelFill(0, NLEDS-1, fullred);
  }
  if(displayLight == band4) {
  //magenta
   pixelFill(0, NLEDS-1, fullmagenta);
  }
  if(displayLight == band5) {
  //orange 
   pixelFill(0, NLEDS-1, orange);
  }
  if(displayLight == band6) {
  //yellow
   pixelFill(0, NLEDS-1, fullyellow);
  }
  if(displayLight == band7) {
  //white
   pixelFill(0, NLEDS-1, full);
  }
}

int pixelFill (int startPixel, int endPixel, int hexColor) {

for(int i=startPixel; i<endPixel-1; i++) {
  lights.setPixelColor(i, hexColor);
}
 lights.show();
//  delay(500);
 return(endPixel);
}

int maxRead(int band) {
  int maxReading = band1;
    if(maxReading<band2); {
      maxReading = band2;
    }
    if(maxReading<band3) {
      maxReading =band3;
    }
    if(maxReading<band4) {
      maxReading = band4;
    }
    if(maxReading<band5) {
      maxReading = band5;
    }
    if(maxReading<band6) {
      maxReading = band6;
    }
    if(maxReading<band7) {
      maxReading = band7;
    }
    return maxReading;
}


