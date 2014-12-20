/*
  Receives compass sensor events from your phone.
 
 */

#include <MeetAndroid.h>


// MeetAndroid meetAndroid();
// you can define your own error function to catch messages
// where not fuction has been attached for
MeetAndroid meetAndroid(error);

int data=0;
float fData=0;
int intData[3] = {0};
float floatData[3] = {0};

int outPin1=4;
int outPin2=5;

int redPin=9;
int greenPin=10;
int bluePin=11;


void error(uint8_t flag, uint8_t values){
  Serial.print("ERROR: ");
  Serial.print(flag);
}

void setup()  
{
  // use the baud rate your bluetooth module is configured to 
  // not all baud rates are working well, i.e. ATMEGA168 works best with 57600
  Serial.begin(115200);

  // register callback functions, which will be called when an associated event occurs.
  // - the first parameter is the name of your function (see below)
  // - match the second parameter ('A', 'B', 'a', etc...) with the flag on your Android application
  meetAndroid.registerFunction(orientation, 'A');  
  meetAndroid.registerFunction(proximate, 'B');  
  meetAndroid.registerFunction(what_ever_the_name_of_a_function, 'C');  


// set pinmode 
  pinMode(outPin1,OUTPUT);
  pinMode(outPin2,OUTPUT);
  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);

}

void loop()
{
  meetAndroid.receive(); // you need to keep this in your loop() to receive events
}


void orientation(byte flag, byte numOfValues){
  //x direction: intdata[0] range 0 to 359
  //y direction: intdata[1] range -180 to 180
  // z direction: intdata[2],-90 to 90
  meetAndroid.getIntValues(intData); 

  // example: control a RGB LED
  // the orientation sensor z direction is mapped into analog write range of 0-255
  int color = map (intData[2], -90, 90, 0, 255);

  // calculate 3 clolor intensity from the orientation sensor data
  int red = color;
  int green = 255 - color;
  int blue = 128 - color/2;
  
  // output to the R,G,B pins of the LED
  analogWrite(redPin,red);
  analogWrite(greenPin,green);
  analogWrite(bluePin,blue);

}

void proximate(byte flag, byte numOfValues){
  // it is on/off. If there are something near, it is 0, otherwise it is 5
    data = meetAndroid.getInt();

// when something is close to the sensor, it is 0, but just in case, here we say smaller than 2
  if (data <2){    
    digitalWrite(outPin1,HIGH);  // turn on the outPin1
  }
  else digitalWrite(outPin1,LOW);   // turn off the outPin1
  
}

void what_ever_the_name_of_a_function(byte flag, byte numOfValues){
  // if you had ID as 'C' on your Amarino App on the phone, it will trigger this function as it is assigned to C and send data here.

  // this will be single int data
  //data = meetAndroid.getInt();
  // this will be single int data
  //fData = meetAndroid.getFloat();
  // this will be if it was several int value
  //meetAndroid.getIntValues(intdata); 
  // this will be if it was several float value
  //meetAndroid.getFloatValues(data);
  
  // and here, write what you want to do with the data you get

}





