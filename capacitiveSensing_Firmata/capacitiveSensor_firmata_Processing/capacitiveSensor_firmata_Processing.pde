import processing.serial.*;

import cc.arduino.*;

Arduino arduino;

int total1;
//int total2;
//int total3;


void setup() {
  // window size
  size(470, 280);
  background(0);
  // print out all the device connected to serial ports
  println(Arduino.list());
  
  arduino = new Arduino(this, Arduino.list()[0], 57600);
   
}

void draw() {
  fill(0,0,0,5);
  rect(0,0,width,height);
  
  
 // read capacitive sensor value sent via firmata 
  total1=arduino.analogRead(8) ;
 // total2=arduino.analogRead(9) ;
 // total3=arduino.analogRead(10) ;
 
 print("total1 : ");
 print(total1);
// print(" total2 : ");
// print(total2);
// print(" total3 : ");
// print(total3);
 println();
 
 fill(255,255,255,50);
 noStroke();
 smooth();
 ellipse(width/2, height/2, total1, total1);

   
}
