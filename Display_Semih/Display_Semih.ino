#include <LiquidCrystal.h>
#define Light 7

// initializing  and declaring PIN's and global variables.

    LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
    String name = "Semih Onay";
    String department = "Computer Science";

void setup() {
// Setting up LCD columns and rows.
  
  lcd.begin(16, 2);
  pinMode(Light,OUTPUT);
  digitalWrite(Light,HIGH);
  
// Printing on LCD
  lcd.print(name);
  lcd.setCursor(0,1);
  lcd.print(department);
}

//Text Scroll

void loop() {
  
  for (int i = 0; i < 17; i++) {
    
// scroll one position leftt:
    lcd.scrollDisplayLeft(); 
// Delaying...
    delay(400);
  }
  
  for (int i = 0; i < 17; i++) {
    
// scrolling to the right:
    lcd.scrollDisplayRight(); 
// Delaying...
    delay(400);
  }
  
  for (int i = 0; i < 3; i++) {
    
    lcd.noDisplay();
    delay(500);
    lcd.display();
    delay(500);
    
  }
  
  delay(500);
}  

