#include <Servo.h>

Servo servo1, servo2, servo3;

int val;

void setup() {
    servo1.attach(2);
    servo2.attach(3);
    servo3.attach(4);
    Serial.begin(115200);
}

void loop() {
    while (Serial.available()) {
        char servoID = Serial.read();
        val = Serial.parseInt();
        if (servoID == 'a')
            servo1.write(val);
        else if (servoID == 'b')
            servo2.write(val);
        else if (servoID == 'c')
            servo3.write(val);
        else if (servoID == 'A') {
            servo1.write(val);
            servo2.write(val);
            servo3.write(val);
        }
        delay(5);
        while (Serial.available() > 0)
            Serial.read();
    }
}
