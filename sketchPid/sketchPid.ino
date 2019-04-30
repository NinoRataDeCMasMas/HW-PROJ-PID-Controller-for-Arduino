/**
 * @file   ComplementaryFilter.h
 * @date   Abr 22, 2019
 * @brief  Example code for PID implementation by Arduino.
 */
#include <ComplementaryFilter.h>
#include <Controller.h>
#include <PIDController.h>
#include <PIController.h>
#include <PDController.h>
#include <Servo.h>
#include "Printer.h"

/* We declare the variable to control the servo and read the sensor */
Servo* servoMotor;
Controller* controller;
ComplementaryFilter* filter;

/* Define Variables we'll be connecting to */
const int servoZeroPos = 98;
const double sensorZeroPos = 290.0;
double setpoint = 0.0, input = 0.0, output = 0.0;
/*
 * @brief setup function.
 */
void setup( void )
{
  /* We start the complementary filter */
  filter = new ComplementaryFilter(0.65);
  /* We start the servo to start working with pin 9 */
  servoMotor = new Servo;
  servoMotor->attach(9);  
  /* We start the proportional controller */
  controller = new PIDController(&setpoint, &input, &output, 0.3464, 0.4849, 0.001);  
  /* Serial communication to 9600 bauds */
  Serial.begin(9600);  
}
/*
 * @brief loop function.
 */
void loop( void )
{
  double acdLecture = analogRead(A0);
  input = filter->compute(acdLecture) - sensorZeroPos;
  controller->compute();
  Serial << input << "," << output << endl;
  servoMotor->write(output + servoZeroPos);
  delay(25);  
}
/* EOF */
