 #include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 

int threshold=500;

// the setup routine runs once when you press reset:
void setup() {
  
  // attaches the servo on pin 9 to the servo object 
      myservo.attach(9);  

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);

  
  if (sensorValue>threshold){
    myservo.write(179);
  }
  else {
    myservo.write(0);
  }
  
  
  // print out the value you read:
  Serial.print("sensorValue: ");
  Serial.print(sensorValue);
  Serial.println();
  
   
  delay(15);        // delay in between reads for stability
}
