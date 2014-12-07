#include "SevSeg.h"

SevSeg::SevSeg()
{
  //Initial values
  number=8888;
  DecPlace=0;

}

//Begin
/*******************************************************************************************/
//Set pin modes and turns all displays off
void SevSeg::Begin(boolean mode_in,byte C1, byte C2, byte C3, byte C4, byte UC1, byte UC2, byte UC3, byte UC4, byte UC5, byte UC6, byte UC7, byte UC8){

  //Assign input values to variables
  //mode is what the digit pins must be set at for it to be turned on.  0 for common cathode, 1 for common anode
  mode=mode_in;
  if (mode==1){
    DigitOn=HIGH;
    DigitOff=LOW;
    SegOn=LOW;
    SegOff=HIGH;
  }
  else {
    DigitOn=LOW;
    DigitOff=HIGH;
    SegOn=HIGH;
    SegOff=LOW;
  }

  DigitPins[0]=C1;
  DigitPins[1]=C2;
  DigitPins[2]=C3;
  DigitPins[3]=C4;
  SegmentPins[0]=UC1;
  SegmentPins[1]=UC2;
  SegmentPins[2]=UC3;
  SegmentPins[3]=UC4;
  SegmentPins[4]=UC5;
  SegmentPins[5]=UC6;
  SegmentPins[6]=UC7;
  SegmentPins[7]=UC8;


  //Set Pin Modes as outputs
  for (byte digit=0;digit<4;digit++) {
    pinMode(DigitPins[digit], OUTPUT);
  }
  for (byte seg=0;seg<8;seg++) {
    pinMode(SegmentPins[seg], OUTPUT);
  }

  //Turn Everything Off
  //Set all digit pins off.  Low for common anode, high for common cathode
  for (byte digit=0;digit<4;digit++) {
    digitalWrite(DigitPins[digit], DigitOff);
  }
  //Set all segment pins off.  High for common anode, low for common cathode
  for (byte seg=0;seg<8;seg++) {
    digitalWrite(SegmentPins[seg], SegOff);
  }
}

//Refresh Display
/*******************************************************************************************/
//Cycles through each segment and turns on the correct digits for each.
//Leaves everything off
void SevSeg::PrintOutput(){
  for (byte seg=0;seg<=8;seg++) {
    //Turn the relevant segment on
    digitalWrite(SegmentPins[seg],SegOn);
    //For each digit, turn relevant digits on
    for (byte digit=0;digit<=4;digit++){
      if (lights[digit][seg]==1) {
        digitalWrite(DigitPins[digit],DigitOn);
      }
      //delay(20);
    }
    //Turn all digits off
    for (byte digit=0;digit<=4;digit++){
      digitalWrite(DigitPins[digit],DigitOff);
    }

    //Turn the relevant segment off
    digitalWrite(SegmentPins[seg],SegOff);
    digitalWrite(SegmentPins[0],SegOff); //I don't know why this line is needed, but segment a
    // stays on if it isn't included
  }
}

//New Number
/*******************************************************************************************/
//Function to update the number displayed
void SevSeg::NewNum(int number_in, byte DecPlace_in)
{
  //Feed the inputs into the library's variables
  number=number_in;
  DecPlace=DecPlace_in;
  FindNums();
  CreateArray();
}


//Find Digits (Nums)
/*******************************************************************************************/
//Function to find the four individual digits to be displayed from the variable 'number'
void SevSeg::FindNums() {
  //If the number received is negative, set the flag and make the number positive
  if (number<0) {
    negative=1;
    number=number*-1;
  }
  else {
    negative=0;
  }

  //If the number is out of range, just display '----'
  if ((negative==0 && number>9999) || (negative==1 && number>999)) {
    nums[0]=21;
    nums[1]=21;
    nums[2]=21;
    nums[3]=21;
  }

  else{
    //Find the four digits
    int total=number;
    if (negative==0) {
      nums[0]=number/1000;
      total=total-nums[0]*1000;
    }
    else {
      nums[0]=21;
    }
    nums[1]=total/100;
    total=total-nums[1]*100;
    nums[2]=total/10;
    nums[3]=total-nums[2]*10;


    //If there are zeros, set them to 20 which means a blank
    //However, don't cut out significant zeros
    if (negative==0) {
      if (nums[0]==0 && DecPlace<3){
        nums[0]=20;
        if (nums[1]==0 && DecPlace<2) {
          nums[1]=20;
          if (nums[2]==0 && DecPlace==0) {
            nums[2]=20;
          }
        }
      }
    }
    else {
      if (nums[1]==0 && DecPlace<2) {
        nums[1]=20;
        if (nums[2]==0 && DecPlace==0) {
          nums[2]=20;
        }
      }
    }
  }
}

//Create Array
/*******************************************************************************************/
//From the numbers found, says which LEDs need to be turned on
void SevSeg::CreateArray() {
  for (byte digit=0;digit<=3;digit++) {
    switch (nums[digit]){
    case 0:
      lights[digit][0]=1;
      lights[digit][1]=1;
      lights[digit][2]=1;
      lights[digit][3]=1;
      lights[digit][4]=1;
      lights[digit][5]=1;
      lights[digit][6]=0;
      break;
    case 1:
      lights[digit][0]=0;
      lights[digit][1]=1;
      lights[digit][2]=1;
      lights[digit][3]=0;
      lights[digit][4]=0;
      lights[digit][5]=0;
      lights[digit][6]=0;
      break;
    case 2:
      lights[digit][0]=1;
      lights[digit][1]=1;
      lights[digit][2]=0;
      lights[digit][3]=1;
      lights[digit][4]=1;
      lights[digit][5]=0;
      lights[digit][6]=1;
      break;
    case 3:
      lights[digit][0]=1;
      lights[digit][1]=1;
      lights[digit][2]=1;
      lights[digit][3]=1;
      lights[digit][4]=0;
      lights[digit][5]=0;
      lights[digit][6]=1;
      break;
    case 4:
      lights[digit][0]=0;
      lights[digit][1]=1;
      lights[digit][2]=1;
      lights[digit][3]=0;
      lights[digit][4]=0;
      lights[digit][5]=1;
      lights[digit][6]=1;
      break;
    case 5:
      lights[digit][0]=1;
      lights[digit][1]=0;
      lights[digit][2]=1;
      lights[digit][3]=1;
      lights[digit][4]=0;
      lights[digit][5]=1;
      lights[digit][6]=1;
      break;
    case 6:
      lights[digit][0]=1;
      lights[digit][1]=0;
      lights[digit][2]=1;
      lights[digit][3]=1;
      lights[digit][4]=1;
      lights[digit][5]=1;
      lights[digit][6]=1;
      break;
    case 7:
      lights[digit][0]=1;
      lights[digit][1]=1;
      lights[digit][2]=1;
      lights[digit][3]=0;
      lights[digit][4]=0;
      lights[digit][5]=0;
      lights[digit][6]=0;
      break;
    case 8:
      lights[digit][0]=1;
      lights[digit][1]=1;
      lights[digit][2]=1;
      lights[digit][3]=1;
      lights[digit][4]=1;
      lights[digit][5]=1;
      lights[digit][6]=1;
      break;
    case 9:
      lights[digit][0]=1;
      lights[digit][1]=1;
      lights[digit][2]=1;
      lights[digit][3]=1;
      lights[digit][4]=0;
      lights[digit][5]=1;
      lights[digit][6]=1;
      break;
    case 20:
      lights[digit][0]=0;
      lights[digit][1]=0;
      lights[digit][2]=0;
      lights[digit][3]=0;
      lights[digit][4]=0;
      lights[digit][5]=0;
      lights[digit][6]=0;
      break;
    case 21:
      lights[digit][0]=0;
      lights[digit][1]=0;
      lights[digit][2]=0;
      lights[digit][3]=0;
      lights[digit][4]=0;
      lights[digit][5]=0;
      lights[digit][6]=1;
      break;
    default:
      lights[digit][0]=0;
      lights[digit][1]=0;
      lights[digit][2]=1;
      lights[digit][3]=1;
      lights[digit][4]=1;
      lights[digit][5]=0;
      lights[digit][6]=1;
      break;
    }

    //Set the decimal place lights
    if (3-digit==DecPlace){
      lights[digit][7]=1;
    }
    else {
      lights[digit][7]=0;
    }
  }
}
