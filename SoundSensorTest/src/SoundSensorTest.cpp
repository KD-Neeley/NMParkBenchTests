/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/kdneeley/Documents/IoT/NMParkBenchTests/SoundSensorTest/src/SoundSensorTest.ino"
/*
 * Project SoundSensorTest
 * Description:
 * Author: KD Neeley
 * Date: 06/12/2023
 * SRC: https://github.com/engineertype/MSGEQ7_MOSFET/blob/master/MSGEQ7_MOSFET.ino

 Arduino Connections:
 - GND to GND on MSGEQ7
 - 5V to VDD on MSGEQ7
 - A3 to OUT on MSGEQ7 
 - D7 to STROBE on MSGEQ7
 - D8 to RESET on MSGEQ7
  */

void setup();
void loop();
void autoAdjustMinMax(int volume);
#line 16 "/Users/kdneeley/Documents/IoT/NMParkBenchTests/SoundSensorTest/src/SoundSensorTest.ino"
const int MSGEQ7_STROBE_PIN =    7;
const int MSGEQ7_RESET_PIN =     8;
const int MSGEQ7_ANALOG_PIN =   19;
const int NUM_FREQUENCY_BANDS =  7;

int volumeInBand[NUM_FREQUENCY_BANDS];
int minimumVolume, maximumVolume;
int cutoffVolume;

int band1(int red, int green, int blue, int fullMin, int fullMax );


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

  static unsigned long nextLoopTime = 50; 
  int cutoffVolume;
  
  // Toggle the RESET pin of the MSGEQ7 to start reading from the lowest frequency band
  digitalWrite(MSGEQ7_RESET_PIN, HIGH);
  digitalWrite(MSGEQ7_RESET_PIN, LOW);
  
  // Read the volume in every frequency band from the MSGEQ7
  for (int i=0; i<NUM_FREQUENCY_BANDS; i++) {
    digitalWrite(MSGEQ7_STROBE_PIN, LOW);
    delayMicroseconds(30); // Allow the output to settle
    volumeInBand[i] = analogRead(MSGEQ7_ANALOG_PIN);
    autoAdjustMinMax(volumeInBand[i]);
    digitalWrite(MSGEQ7_STROBE_PIN, HIGH);
  }

   // A volume greater than 35% should turn the LED on
  cutoffVolume = map(35, 0, 100, minimumVolume, maximumVolume);
  
  // Turn the RED LED on if the volume in the lower frequency bands is high enough
  if (volumeInBand[0] > cutoffVolume || volumeInBand[1] > cutoffVolume) {
     // analogWrite(RED_LED, map(max(volumeInBand[0], volumeInBand[1]), cutoffVolume, maximumVolume, 0, 255));
    // Serial.printf("Band 0 =" )
    Serial.printf("Band 0: %i \n Band 1 %i \n", volumeInBand[0], volumeInBand[1]);
  }
   
  else {
    // analogWrite(band1(), 0);
  }

  // Turn the GREEN LED on if the volume in the middle frequency bands is high enough
  if (volumeInBand[2] > cutoffVolume || volumeInBand[3] > cutoffVolume){
    // analogWrite(GREEN_LED, map(max(volumeInBand[2], volumeInBand[3]), cutoffVolume, maximumVolume, 0, 255));
     Serial.printf("Band 2: %i \n Band 3 %i \n", volumeInBand[2], volumeInBand[3]);
  }
    
  else {
    //  analogWrite(GREEN_LED, 0);
  }
   
 
  // Turn the BLUE LED on if the volume in the lower frequency bands is high enough
  if (volumeInBand[4] > cutoffVolume || volumeInBand[5] > cutoffVolume) {
    // analogWrite(BLUE_LED, map(max(volumeInBand[4], volumeInBand[5]), cutoffVolume, maximumVolume, 0, 255));
     Serial.printf("Band 4: %i \n Band 5 %i \n", volumeInBand[4], volumeInBand[5]);

  }
    
  else {
    //  analogWrite(BLUE_LED, 0);
  }
   
   
  // Execute this loop 20 times per second (every 50ms)
  if (millis() < nextLoopTime)
    delay(nextLoopTime - millis());
  nextLoopTime += 50;

}

// Automatically adjust the high and low volume.  This routine is called 20 times per
// second for each band, or 20 * 7 bands = 140 times per second.
void autoAdjustMinMax(int volume) {
  static int increaseMin = 0;
  static int decreaseMax = 0;

  // Adjust the minimum volume level
  if (volume < minimumVolume)
    minimumVolume = volume;
  else {
    // Move the minimum volume level upwards (1 per second)
    if (++increaseMin > 140) {
      increaseMin = 0;
      minimumVolume++;
    }
  }
  
  // Adjust the maximum volume level
  if (volume > maximumVolume)
    maximumVolume = volume;
  else {
    // Move the maximum volume level downwards (5 per second)
    if (++decreaseMax > 28) {
      decreaseMax = 0;
      // Keep a reasonable level of separation between max and min
      if (maximumVolume - minimumVolume > 100)
        maximumVolume--;
    }
  }
}

