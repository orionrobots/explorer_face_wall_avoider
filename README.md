Orionrobots Explorer Face Wall Avoider
======================================

This is the code for a robot which will avoid walls using 2 ultrasonic range modules, and display a face on a LED matrix.
The face will smile when driving, and cringe/blink when the robot has something in collision distance.
The robot will then turn away.
The display also has the outer set of pixels used as a bar to show the proximity sensed on each side.

#License

CC-BY-SA-3.0

# Hardware:
### An Orion Explorer 1 Wall Avoider Robot
This robot kit includes:
- Arduino
- 4 geared motors
- L298 based motor board (handy if it has debug LED's)
- Battery Box
- Wheels + Chassis
- Jump Cables - 40 x male to female.
- 2xHC-04 Distance range modules
- 400 pin breadboard
- 20 x Male to Male Cables

### A MAX 7219 based 8x8 LED Display module
### 6xAA Batteries 

# Quick Overview

This uses 4 tabs in the Arduino editor. 
TurtleMotors.h is the standard orionrobots motor header, however, this only uses the basic motor controller and not the turtle one - it controls each motor individually.
sonar.h - Distance sensor code - this is code to drive the HC-04 sensor module, and convert its pulse timing into a distance.

display.h - This has two parts. First a bit of code to drive the display module and handle its protocol. Then the "DisplayFace" class. This class has hard coded into it the two face bitmaps, and generates the bar charts (see the "with_bars" function).

Finally - the main tab.
First all the hardware is defined and given pins, with the DisplayFace setup lastly and pointing at the MAX7219 display.
In Setup - each of these has their setup method called, and the motors are started. Note that pin 13 was used to debug something here, you can mostly ignore that part.

The loop function is fairly simple:
We define a threshold past which the robot will turn, and a different value to return to normal operation - this prevents the robot jittering at a threshold and means it will act on things. It delays the return to "normal" drive forawrd behaviour.
At each loop, the two sensor values are read. If either is closer than the threshold distance, then tell the face to "close eyes", and drive the motors /opposite/ the sensor back. This may mean both wheels go back - but it will favour driving to one side.

It is only if both values are further away from the return that forward driving will start, and the face will smile again. Anything between these two values and the robot will be in the "closed eyes" mode.

