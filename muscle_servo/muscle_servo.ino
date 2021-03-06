/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
 
 This example code is in the public domain.
 */
 
 #include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 

int threshold=500;
 

// the setup routine runs once when you press reset:
void setup() {
  
    myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
  Serial.println(sensorValue);
  
  if (sensorValue>threshold){
    myservo.write(170);
  }else myservo.write(0);
  
  
  delay(100);                           // waits for the servo to get there 

}
