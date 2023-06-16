/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/kdneeley/Documents/IoT/NMParkBenchTests/MSGEQ7testing/src/MSGEQ7testing.ino"
/*
 * Project MSGEQ7testing
 * Description: Simple program to test the MSGEQ7 
 * Author: KD Neeley
 * Date: 06/13/2023
 * 
 Arduino Connections:
 - GND to GND on MSGEQ7
 - 5V to VDD on MSGEQ7
 - A3 to OUT on MSGEQ7 
 - D7 to STROBE on MSGEQ7
 - D8 to RESET on MSGEQ7
  */

void setup();
void loop();
#line 15 "/Users/kdneeley/Documents/IoT/NMParkBenchTests/MSGEQ7testing/src/MSGEQ7testing.ino"
const int MSGEQ7_STROBE_PIN =    7;
const int MSGEQ7_RESET_PIN =     8;
const int MSGEQ7_ANALOG_PIN =   16;
const int NUM_FREQUENCY_BANDS =  7;

int volumeInBand[NUM_FREQUENCY_BANDS];
int minimumVolume, maximumVolume;
int band1, band2, band3, band4, band5, band6, band7;

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

}

void loop() {
// Toggle the RESET pin of the MSGEQ7 to start reading from the lowest frequency band
  digitalWrite(MSGEQ7_RESET_PIN, HIGH);
  digitalWrite(MSGEQ7_RESET_PIN, LOW);
  
  // Read the volume in every frequency band from the MSGEQ7
  for (int i=0; i<NUM_FREQUENCY_BANDS; i++) {
    digitalWrite(MSGEQ7_STROBE_PIN, LOW);
    delayMicroseconds(30); // Allow the output to settle
    volumeInBand[i] = analogRead(MSGEQ7_ANALOG_PIN);
    digitalWrite(MSGEQ7_STROBE_PIN, HIGH);
  }

  //Band1
  band1 = volumeInBand[0];
  Serial.printf("Band1 = %i\n", band1);
  //Band2
  band2 = volumeInBand[1];
  Serial.printf("Band2 = %i\n", band2);
  //Band3
  band3 = volumeInBand[2];
  Serial.printf("Band3 = %i\n", band3);
  //Band4
  band4 = volumeInBand[3];
  Serial.printf("Band4 = %i\n", band4);
  //Band5
  band5 = volumeInBand[4];
  Serial.printf("Band5 = %i\n", band5);
  //Band6
  band6 = volumeInBand[5];
  Serial.printf("Band6 = %i\n", band6);
  //Band7
  band7 = volumeInBand[6];
  Serial.printf("Band7 = %i\n", band7);


}