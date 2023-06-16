/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/kdneeley/Documents/IoT/NMParkBenchTests/LIDARmotionSensorTest/src/LIDARmotionSensorTest.ino"
/*
 * Project LIDARmotionSensorTest
 * Description: Simple test for the Garmin LIDAR LITE V4 sensor
 * Author: KD Neeley
 * Date: 06/16/2023
 */
#include <LIDARLite_v4LED.h>

void setup();
void loop();
#line 9 "/Users/kdneeley/Documents/IoT/NMParkBenchTests/LIDARmotionSensorTest/src/LIDARmotionSensorTest.ino"
const int I2CADDRESS = 0X62;

byte * arrayToSave[8];
LIDARLite_v4LED L1;


void setup() {
    Serial.begin(9600);
    L1.takeRange(I2CADDRESS);
}

void loop() {
    int dist;
    L1.waitForBusy(I2CADDRESS);
    dist = L1.readDistance(I2CADDRESS);
    Serial.printf("Distance Measured = %i\n", dist);

}