/* Explorer 1 With LED Module 
 Use 2 hc 04 modules + 8x8 display module for debug. */
#include "display.h"
#include "sonar.h"
#include "TurtleMotors.h"

Motor motor_left = {10, 8, 9};
Motor motor_right = {3, 4, 5};
SR04 sensor_left = {11, 12};
SR04 sensor_right = {6, 7};
Max7219 display_hw = Max7219(A0, A1, A2);
DisplayFace face = {display_hw};

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  motor_left.setup();
  motor_right.setup();
  sensor_left.setup();
  sensor_right.setup();
  display_hw.setup();
  face.smile(0, 0);
  digitalWrite(13, LOW);
  motor_left.forward(0xff);
  motor_right.forward(0xff);
}
#define THRES 2
#define RETURN 3
void loop() {
  //read the sonar
  char left = sensor_left.readDist() / 10;
  char right = sensor_right.readDist() / 10;
  
  //if either below threshold
  if(left < THRES || right < THRES) {
    face.close_eyes(8 - left, 8 - right);
    
    if(left < THRES) {
      motor_right.backward(0xff);
      delay(100);
    }
    if(right < THRES) {
      motor_left.backward(0xff);
      delay(100);
    }
  }
  //once both above return threshold - hyst value
  else if(left > RETURN && right > RETURN) {
    face.smile(8 - left, 8 - right);
    motor_left.forward(0xff);
    motor_right.forward(0xff);
  }
  else {
    face.close_eyes(8 - left, 8 - right);
  }
}
