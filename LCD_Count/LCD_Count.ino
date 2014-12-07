#include <LiquidCrystal.h>
#define Light  7

//Pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
lcd.begin(16, 2); //Lcd cursor location.
pinMode(Light,OUTPUT); //Output pin.
digitalWrite(Light,HIGH); // Send to LCD
}

void loop()
{
lcd.setCursor(0,0); // Cursor: (column = 0,  line = 0)
lcd.print(" Merhaba ! ");
lcd.setCursor(0,1); // Another cursor
lcd.print("   ");
lcd.print(millis()/1500); // On screen time.
}
