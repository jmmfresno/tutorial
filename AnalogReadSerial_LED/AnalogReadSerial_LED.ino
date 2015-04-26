/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
 
 This example code is in the public domain.
 */

// the setup routine runs once when you press reset:
void setup() {
  // set digitalPin12 as output
  pinMode(11,OUTPUT);
  
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);

  
  // map the sensorValue(0-1023) to the range of PWM (0-255)
  int val = map(sensorValue, 0, 1023, 0, 255);
  
  // make sure that the val does not go out of the range
  val=constrain(val,0,255);
  
  // control the voltage going out of the pin 11
  analogWrite(11, val);
  
  
  // print out the value you read:
  Serial.print("sensorValue: ");
  Serial.print(sensorValue);
  Serial.print("  val: ");
  Serial.print(val);
  Serial.println();
  
   
  delay(10);        // delay in between reads for stability
}
