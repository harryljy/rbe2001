#ifndef MOTION_H
#define MOTION_H

#include <Arduino.h>
#include <Servo.h>
#include <Encoder.h>
#include <PID_v1.h>

#include "LineSensor.h"

enum MotionState {
  TURN_RIGHT,
  TURN_LEFT,
  TURN_180,
  BACKWARDS,
  TRACK_TO_INTERSECTION,
  TRACK_TO_BUMP,
  ARM_DOWN,
  ARM_UP,
  INTAKE_IN,
  INTAKE_OUT
};

class Motion {
public:
  Motion();
  void initialize();
  bool isDone();
  void turnRight();
  void turnLeft();
  void turn180();
  void reverse();
  void trackToIntersection(int count);
  void trackToBump();
  void armDown();
  void armUp();
  void intakeIn();
  void intakeOut();
  void update();

private:
  void setupEncoderMotion(int leftLimit, int leftSpeed, int rightLimit, int rightSpeed);
  void resetEncoders();
  void driveFromEncoder();
  void trackLine();
  void moveArm(int leftBumpPin, int rightBumpPin, int speed);
  void driveIntake(int speed);

  const int lineSensorPins[8] = { 5, 6, 7, 1, 0, 2, 3, 4 };
  LineSensor sensor;

  const int posIntThresh = 300;
  const int negIntThresh = 200;
  bool isInIntersection = false;
  int intersectionCount = 0;
  int intersectionTarget = 0;

  Servo left, right;
  Encoder leftEnc, rightEnc;
  int leftLimit, leftSpeed, rightLimit, rightSpeed;

  double setpoint, input, output;
  PID pid;

  Servo armLeft, armRight, armIntake;
  bool hitLeft, hitRight;
  long leftHitTime, rightHitTime, intakeStartTime;

  bool done = true;
  enum MotionState state;
};

#endif
