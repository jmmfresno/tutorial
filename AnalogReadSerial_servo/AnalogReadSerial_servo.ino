 #include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 



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

  
  // map the sensorValue(0-1023) to the range of servo (0-179)
  int val = map(sensorValue, 0, 1023, 0, 179);
  
  // make sure that the val does not go out of the range
  val=constrain(val,0,179);
  
  // control the servo angle
  myservo.write(val);
  
  
  // print out the value you read:
  Serial.print("sensorValue: ");
  Serial.print(sensorValue);
  Serial.print("  val: ");
  Serial.print(val);
  Serial.println();
  
   
  delay(15);        // delay in between reads for stability
}
