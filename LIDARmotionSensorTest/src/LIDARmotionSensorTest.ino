/*
 * Project LIDARmotionSensorTest
 * Description: Simple test for the Garmin LIDAR LITE V4 sensor
 * Author: KD Neeley
 * Date: 06/16/2023
 */

#include <LIDARLite_v4LED.h>
#include <wire.h>

const int I2CADDRESS = 0X62;
uint16_t distance;
LIDARLite_v4LED L1;

SYSTEM_MODE(SEMI_AUTOMATIC);

void setup() {
    Serial.begin(115200);
    waitFor(Serial.isConnected, 10000);
    Wire.begin();
}

void loop() {
    L1.takeRange(I2CADDRESS);
    L1.waitForBusy(I2CADDRESS);
    L1.getBusyFlag(I2CADDRESS);
    distance = L1.readDistance(I2CADDRESS);
    Serial.printf("Distance = %u\n", distance);
}
