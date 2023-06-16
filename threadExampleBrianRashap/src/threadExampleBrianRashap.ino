/*
 * Project ThreadTheNeedle
 * Description: Sample Code of Using Threads
 * Author: Brian Rashap
 * Date: 14-JUN-2023
 */

bool toggle,prevToggle;
unsigned int currentTime;

SYSTEM_THREAD(ENABLED);
void threadCode1(void);
Thread thread("myThread", threadCode1);

void setup() {
  Serial.begin(9600);
  waitFor(Serial.isConnected,5000);
  delay(500);

  pinMode(D7,OUTPUT);
  Serial.printf("Starting Thread\n");
}

void loop() {
  currentTime = millis();
  if(toggle != prevToggle) {
    prevToggle = toggle;
    if(toggle) {
      Serial.printf("Hello Toggling World\n");
    }
  }
}

void threadCode1(void) {
  unsigned int lastToggle;

  while(true) {
    if(millis()-lastToggle > 1000) {
      lastToggle = millis();
      toggle = !toggle;
      if(toggle) {
        digitalWrite(D7,HIGH);
      }
      else {
        digitalWrite(D7,LOW);
      }
    }
    os_thread_yield();
  }
}