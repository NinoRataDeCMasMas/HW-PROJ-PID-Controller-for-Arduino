#include "Test.h"

Test* test;

void setup()
{
  Serial.begin(9600);
  test = new Test(A0, 9);
}

void loop()
{
  delay(3000);
  test->totalRange();
  while(1);
}
