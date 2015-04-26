 #include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 

int threshold=500;

// the setup routine runs once when you press reset:
void setup() {
  
 

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);

  
  int thisPitch = map(sensorValue, 0, 1023, 120, 1500);

  // play the pitch:
  tone(9, thisPitch, 10);
  
  
  // print out the value you read:
  Serial.print("sensorValue: ");
  Serial.print(sensorValue);
    Serial.print("  thisPitch: ");
  Serial.print(thisPitch);
  Serial.println();
  
   
  delay(15);        // delay in between reads for stability
}
