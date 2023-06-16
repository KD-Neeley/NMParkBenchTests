/*
 * Project LIDARmotionSensorTest
 * Description: Simple test for the Garmin LIDAR LITE V4 sensor
 * Author: KD Neeley
 * Date: 06/15/2023
 */
#include <LIDARLite.h>
#include <wire.h>

const int I2CADDRESS = 0X62;

byte * arrayToSave[2];
LIDARLite L1;


void setup() {
 // Initialize Arduino serial port (for display of ASCII output to PC)
    Serial.begin(9600);
    L1.begin(0, true);
}

void loop() {
    int dist;

    dist = L1.distance(true, I2CADDRESS); 
    L1.write(0x04, 0x00, I2CADDRESS);
    L1.read(0x01, 1, arrayToSave[0], true, I2CADDRESS);
    // Display distance
    Serial.print(dist);

}