/*This code works with 16 line workshop setup
 use it with heatController_16 max patch*/


#include "TimerOne.h"
#include <avr/pgmspace.h>
#include <CapacitiveSensor.h>
///////////////
//this code uses the shiftregister to output the bits
///////////////


#define PINNUM 16  //number of the pin used for output
int pinState[PINNUM];

//new variables
int lastPosition = 0; //stores the position where the while-loop stopped the last time

//Pin connected to latch pin (ST_CP) of 74HC595
const int latchPin = 5;
//Pin connected to clock pin (SH_CP) of 74HC595
const int clockPin = 4;
////Pin connected to Data in (DS) of 74HC595
const int dataPin = 6;


unsigned long previousMillis = 0;        // will store last time LED was updated

#define COMMON_PIN      2    // The common 'send' pin for all keys
#define NUM_OF_SAMPLES  10   // Higher number whens more delay but more consistent readings
#define CAP_THRESHOLD   5  // Capactive reading that triggers a note (adjust to fit your needs)
#define NUM_OF_SENSOR     8    // Number of sensors



// This macro creates a capacitance sensor object
#define CS(Y) CapacitiveSensor(2, Y)

// Defines the pins that the keys are connected to:
CapacitiveSensor sensors[] = {
  CS(3), CS(4), CS(5), CS(6), CS(7), CS(8), CS(9), CS(10)};

int onTime=300; // *10 in milisecond
int counter[NUM_OF_SENSOR];
int pin;



void setup()
{
  // set the shift register control pin to output
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);


  // reset the pinState to 0
  for(int i=0; i<PINNUM; i++) {
    pinState[i]=0;
  }

  // Turn off autocalibrate on all channels:
  for(int i=0; i<8; ++i) {
    sensors[i].set_CS_AutocaL_Millis(0xFFFFFFFF);
  }

  // turn all the pin off to start with ... for just in case
  setPin_Manual();

  // initialize the serial communication:
  Serial.begin(9600);
  Serial.println("hello");
}



void loop() {


  // Loop through each sensors:
  //for (int i = 0; i < NUM_OF_SENSOR; ++i) {  
  for (int i = 0; i < 2; ++i) {    
    // If the capacitance reading is greater than the threshold, play a note:
    if(sensors[i].capacitiveSensor(NUM_OF_SAMPLES) > CAP_THRESHOLD) {
      if (counter[i]==0){
        counter[i] = onTime;
        setPinState(i, HIGH);

        Serial.print(i);
        Serial.println("  is on");
      }
    }
  }

//for (int i = 0; i < NUM_OF_SENSOR; ++i) { 
  for (int i = 0; i < 2; ++i) { 
    if (counter[i]>0){    
      counter[i]=counter[i]-1;
    }

    if (counter[i]==1){
      setPinState(i, LOW);

      Serial.print(i);
      Serial.println("  is off");
    }
  }

  // send the status to the pins
  setPin_Manual();

  delay(10);
}

void setPinState(int pinNum, boolean state){

  // if you are usieng board with TC4428, as inputA is inverted!
  if (pinNum==0 || pinNum==3 || pinNum==4 || pinNum==6 || pinNum==9 || pinNum==11 || pinNum==13 || pinNum==15){
    pinState[pinNum] = !state;
  }
  else   pinState[pinNum] = state; 

  //   if you are usieng board with TC4427, activate the following instead
  //pinState[pinNum] = state;

}



//turn off all the heat pin setting off
void allOff(){
  for (int i=0; i<PINNUM; i++){
    // if you are usieng board with TC4428, as inputA is inverted!
    if (i==0)    pinState[i] = 1;
    if (i==1)    pinState[i] = 0;   
    if (i==2)    pinState[i] = 0;
    if (i==3)    pinState[i] = 1;  
    if (i==4)    pinState[i] = 1;
    if (i==5)    pinState[i] = 0;  
    if (i==6)    pinState[i] = 1;
    if (i==7)    pinState[i] = 0;  
    if (i==8)    pinState[i] = 0;
    if (i==9)    pinState[i] = 1; 
    if (i==10)   pinState[i] = 0;  
    if (i==11)   pinState[i] = 1;  
    if (i==12)   pinState[i] = 0;  
    if (i==13)   pinState[i] = 1;  
    if (i==14)   pinState[i] = 0;  
    if (i==15)   pinState[i] = 1;  

    // if you are usieng board with TC4427, activate the following instead
    //pinState[i] = 0; 
  }
}



// send out the heat pin state to shift register
void setPin_Manual()
{
  //shift the data out
  digitalWrite(latchPin, LOW);

  byte outint=0;
  int loopCnter = 0; //reusing the vairable

  for (int i=0; i<PINNUM/8; i++) {
    outint=0;

    //set the bits in the byte
    for (int j=0; j<8; j++) {  
      // turn on the next highest bit in bitsToSend:
      if (pinState[loopCnter] > 0) {
        bitWrite(outint, 7-j, HIGH); //MSB = 0
      }
      loopCnter++;
    }

    // shift the bits out:
    shiftOut(dataPin, clockPin, MSBFIRST, outint);

  }
  digitalWrite(latchPin, HIGH);
  ///shiftout done
}







