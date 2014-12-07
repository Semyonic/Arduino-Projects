int segments[7] = {12,13,3,4,5,10,9};
int digits[2] = {7,11}; 
int theNumber = 0;
byte seven_seg_segments[10][7] = { 
  {1,1,1,1,1,1,0},  // = 0
  {0,1,1,0,0,0,0},  // = 1
  {1,1,0,1,1,0,1},  // = 2
  {1,1,1,1,0,0,1},  // = 3
  {0,1,1,0,0,1,1},  // = 4
  {1,0,1,1,0,1,1},  // = 5
  {1,0,1,1,1,1,1},  // = 6
  {1,1,1,0,0,0,0},  // = 7
  {1,1,1,1,1,1,1},  // = 8
  {1,1,1,1,0,1,1}   // = 9
};

void setup() {    
  
  for (int i=0; i<7; i++){
    pinMode(segments[i], OUTPUT);           // sets the seven segment outputs
  }
  
  for (int i=0; i<2; i++){
    pinMode(digits[i], OUTPUT);             // sets the seven segment outputs 
  }
  
}

void sevenSegWrite(int thePosition, int digit) {  // write a number to a seven segment digit
  for (int i = 0; i < 7; i++) {          
    if (seven_seg_segments[digit][i] == 1){  
      digitalWrite(segments[i], LOW);
    } 
    else {
      digitalWrite(segments[i], HIGH);
    }
  }
  digitalWrite(digits[thePosition], HIGH);
  delayMicroseconds(200);
  digitalWrite(digits[thePosition], LOW);
  delayMicroseconds(200);
}

void clearDisplay() {                              // clear the display
  for (int i=0; i<5; i++){
    digitalWrite(digits[i], LOW);
  }
}

void showNumber(){                                 // show the number
    char szZahl[1];
    sprintf(szZahl, "%d", theNumber);
    int ergebnis = szZahl[0] - '0';
    if (ergebnis>-1){
      sevenSegWrite(1,ergebnis);
      delayMicroseconds(10);
    } else {
      sevenSegWrite(1,0);
      delayMicroseconds(10);
    }
    delay(1);
    clearDisplay();
}

void loop() {
  
  sevenSegWrite(1,3);
  
  showNumber();
  delay(1);
  
}
