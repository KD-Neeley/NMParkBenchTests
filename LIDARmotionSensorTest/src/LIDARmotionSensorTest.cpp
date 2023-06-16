/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/kdneeley/Documents/IoT/NMParkBenchTests/LIDARmotionSensorTest/src/LIDARmotionSensorTest.ino"
/*
 * Project LIDARmotionSensorTest
 * Description: Simple test for the Garmin LIDAR LITE V4 sensor
 * Author: KD Neeley
 * Date: 06/15/2023
 */
#include <LIDARLite.h>
#include <wire.h>

void setup();
void loop();
#line 10 "/Users/kdneeley/Documents/IoT/NMParkBenchTests/LIDARmotionSensorTest/src/LIDARmotionSensorTest.ino"
const int I2CADDRESS = 0X62;

byte * arrayToSave[16];
LIDARLite L1;


void setup() {
 // Initialize Arduino serial port (for display of ASCII output to PC)
    Serial.begin(9600);
    Wire.begin();
    L1.begin(0, true);
}

void loop() {
    int dist;
    L1.write(0x03, 0x00, I2CADDRESS);
    L1.read(0x01, 1, arrayToSave[0], true, I2CADDRESS);
    dist = L1.distance(true, I2CADDRESS);
    // Display distance
    Serial.printf("Distance Measured = %i\n", dist);

}