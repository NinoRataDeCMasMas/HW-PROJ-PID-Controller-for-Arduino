#include <ComplementaryFilter.h>
#include <Servo.h>
#include "Printer.h"

class Test
{
  int sensor;
  Servo* servoMotor;
  ComplementaryFilter *filter1, *filter2;

public:
  Test(int sensor, int servo);  
  void totalRange( void );
  void stablePos( void );
};

Test::Test(int sensor, int servo): sensor(sensor)
{
  filter1 = new ComplementaryFilter(0.65);
  filter2 = new ComplementaryFilter(0.75);
  servoMotor = new Servo;
  servoMotor->attach(servo);  
}

void Test::totalRange( void )
{  
  for(int i = 0; i < 180; ++i)
  {
    servoMotor->write(i);
    double acdLecture = analogRead(A0);
    /* We analize raw and filtered signals with diferent configurations */
    Serial << acdLecture << "," << filter1->compute(acdLecture) << "," << filter2->compute(acdLecture) << endl;
    delay(25);
  }
}

void Test::stablePos( void )
{
    servoMotor->write(98);
    double acdLecture = analogRead(A0);
    Serial << filter2->compute(acdLecture) << endl;
    delay(25);  
}
