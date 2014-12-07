int a = 3;
int b = 4;
int h;

#include "math.h"


void setup()
{
  Serial.begin(9600);
  
  Serial.println("Pythagorean");
  
  Serial.print("a =");
  Serial.println(a);
  Serial.print("b =");
  Serial.println(b);
  h = sqrt(a*a + b*b);
  
  Serial.print("h =");
  Serial.println(h);
}

void loop()
{
  
}
