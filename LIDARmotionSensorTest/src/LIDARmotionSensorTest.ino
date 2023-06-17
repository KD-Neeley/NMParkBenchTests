/*
 * Project LIDARmotionSensorTest
 * Description: Simple test for the Garmin LIDAR LITE V4 sensor
 * Author: KD Neeley
 * Date: 06/16/2023
 */
#include <LIDARLite_v4LED.h>

const int I2CADDRESS = 0X62;
// const int TRIGGER = A0;
// const int MONITOR = A1;



byte * arrayToSaveReading[8] = {}; //how do I write to 0x00? double check array syntax



LIDARLite_v4LED L1;



void setup() {
    Serial.begin(9600);
   
}

void loop() {

    int dist;
  
    L1.write(0x04, *arrayToSaveReading, 8, I2CADDRESS);

    //repeat the following until bit 0 is low
    L1.read(0x01, *arrayToSaveReading,8, I2CADDRESS);
    
    //make the following a function that returns the range
    L1.read(0x10, *arrayToSaveReading, 8, I2CADDRESS);
    L1.read(0x11, *arrayToSaveReading, 8, I2CADDRESS);
    
    Serial.printf("Distance Measured = %i\n", dist);

}