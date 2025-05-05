
#include<SoftwareSerial.h>

/* Create object named bt of the class SoftwareSerial */ 
SoftwareSerial bt(0,1); /* (Rx,Tx) */	

int pirPin = 2; // The pin where the PIR sensor is connected
int buzzerPin = 5;
unsigned char buzzerVolume = 0;
//int ledPin = 13; // The onboard LED pin



void setup() {
  bt.begin(9600);	/* Define baud rate for software serial communication */
  Serial.begin(9600); // Initialize serial communication for debugging
  pinMode(pirPin, INPUT); // Set the PIR pin as input
  pinMode(buzzerPin, OUTPUT); // Set the LED pin as output
  Serial.println("PIR Motion Sensor Test");
  delay(20000);   /* Power On Warm Up Delay */
}

void loop() 
{
  static unsigned char print_count = 0;
  if (bt.available())	/* If data is available on serial port */
  {
    char c = bt.read();
    if(c == 'A') buzzerVolume = 0;
    if(c == 'B') buzzerVolume = 50;
    if(c == 'C') buzzerVolume = 100;
    if(c == 'D') buzzerVolume = 150;
    if(c == 'E') buzzerVolume = 200;
    if(c == 'F') buzzerVolume = 250;
    Serial.write(buzzerVolume);	
  }
  int motionState = digitalRead(pirPin); // Read the motion state from the PIR sensor
  if (motionState == HIGH) 
  {
    analogWrite(buzzerPin, buzzerVolume);
    //digitalWrite(buzzerPin, HIGH); // Turn on the LED when motion is detected
    Serial.println("Motion detected!");
  } 
  else 
  {
    analogWrite(buzzerPin, 0);
    //digitalWrite(buzzerPin, LOW); // Turn off the LED when no motion is detected
    if(print_count % 50 == 0) Serial.println("No motion."); // for less number of print on serial monitor / here BT serial monitor
  }
  delay(100); // Small delay for stability
  print_count++;
}



