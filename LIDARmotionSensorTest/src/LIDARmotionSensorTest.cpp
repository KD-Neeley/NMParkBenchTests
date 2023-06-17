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

// #include <Wire.h>
// #include <LIDARLite_v4LED.h>

// LIDARLite_v4LED lidar;

// void setup() {
//   Serial.begin(115200);
//   Wire.begin();
//   lidar.configure();
// }

// void loop() {
//   uint16_t distance = lidar.readDistance();
//   Serial.print("Distance: ");
//   Serial.print(distance);
//   Serial.println(" cm");
//   delay(100);
// }


//----
#include <LIDARLite_v4LED.h>
#include <wire.h>

void setup();
void loop();
#line 32 "/Users/kdneeley/Documents/IoT/NMParkBenchTests/LIDARmotionSensorTest/src/LIDARmotionSensorTest.ino"
const int I2CADDRESS = 0X62;
uint16_t distance;
LIDARLite_v4LED L1;

void setup() {
    Serial.begin(115200);
    Wire.begin();
}

void loop() {
    L1.takeRange(I2CADDRESS);
    L1.waitForBusy(I2CADDRESS);
    L1.getBusyFlag(I2CADDRESS);
    distance = L1.readDistance(I2CADDRESS);
    Serial.printf("Distance = %u\n", distance);
}
//____________________________________________________________
// void LIDARLite_v4LED::waitForBusy(uint8_t I2CADDRESS)
// {
//     uint8_t  busyFlag;

//     do
//     {
//         busyFlag = getBusyFlag(I2CADDRESS);
//     } while (busyFlag);

// }
// uint8_t LIDARLite_v4LED::getBusyFlag(uint8_t I2CADDRESS)
// {
//     uint8_t  statusByte = 0;
//     uint8_t  busyFlag; // busyFlag monitors when the device is done with a measurement

//     // Read status register to check busy flag
//     read(0x01, &statusByte, 1, I2CADDRESS);

//     // STATUS bit 0 is busyFlag
//     busyFlag = statusByte & 0x01;

//     return busyFlag;
// }
// uint16_t LIDARLite_v4LED::readDistance(uint8_t I2CADDRESS)
// {
//     uint16_t  distance;
//     uint8_t * dataBytes = (uint8_t *) &distance;
//     // Read two bytes from registers 0x10 and 0x11
//     read(0x10, dataBytes, 2, I2CADDRESS);
//     return (distance);
// }
// LIDARLite_v4LED::readDistance */


//The following returns 0 repeatedly
    // L1.write(0x04, arrayToSaveReading, 8, I2CADDRESS);

    // //repeat the following until bit 0 is low
    // L1.read(0x01, arrayToSaveReading,8, I2CADDRESS);
    // while(arrayToSaveReading[0] != 0x00) {
    //     L1.read(0x01, arrayToSaveReading,8, I2CADDRESS);
    // }
    
    // //make the following a function that returns the range
    // L1.read(0x10, arrayToSaveReading, 2, I2CADDRESS);
    // dist = arrayToSaveReading[1] << 8 | arrayToSaveReading[0];