//PROGRAM MADE BY:
//	-ANIKET PRADHAN
//	-AAYUSH GUPTA
//	-ARAV MALIK
//	-SAI SANTOSH
//
//THE PROGRAM IS MADE FOR THE IED MINI PROJECT, I.E. THE SMART LAMP.
//IT USES VARIOUS SENSORS AND MOTORS FOR ITS WORKING.
//TO LOOK AT THE PROJECT FILES, HERE'S THE LINK: XXXXXXXXXXX

//HEADER FILES
#include <Servo.h>

//PIN INFO
//LED -> 3 PWM
//LDR -> A0 Analog Input
//SERVO -> 9 PWM
//RED -> 5 PWM
//BLUE -> 11 PWM
//GREEN -> 10 PWM

//GLOBAL VARIABLES
int ledpin = 3;
int redPin = 5; //IT HAS TO BE A PWM
int greenPin = 10;
int bluePin = 11;
int ldrpin = A0;
int value = 0;
Servo myservo;
int t=0;
int trigPin = 2;
int echoPin = 4;
//int bluetoothTx = 1;
//int ledPin = 13;
//int bluetoothRx = 0;
//SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

//SETUP CODE
void setup() {
 	myservo.attach(9);
	Serial.begin(9600);
	pinMode(ledpin,OUTPUT);
	pinMode(echoPin,INPUT);    //Echo
	pinMode(trigPin,OUTPUT);    //Trigger
	digitalWrite(ledpin,LOW);
	digitalWrite(trigPin,LOW);
	pinMode(redPin, OUTPUT);
	pinMode(greenPin, OUTPUT);
	pinMode(bluePin, OUTPUT);
//	pinMode(ledPin, OUTPUT);
//	bluetooth.begin(9600);
}

//LOOPING CODE
void loop() {
	if(Serial.available() > 0){
		int toSend = Serial.read();
		if(toSend == 200) {
			//Add code for varying RGB lights
			setColor(1, 0, 0);  // red lowest brightness
			delay(1000);
			setColor(50, 0, 0);  // red
			delay(1000);
			setColor(140, 0, 0);  // red
			delay(1000);
			setColor(255, 0, 0);  // red
			delay(1000);
			setColor(0, 255, 0);  // green
			delay(1000);
			setColor(0, 0, 255);  // blue
			delay(1000);
			setColor(255, 255, 0);  // yellow
			delay(1000);  
			setColor(80, 0, 80);  // purple
			delay(1000);
			setColor(255, 50, 0);  // Orange
			delay(1000);
		}
		else {
			//Add code for LDR
			value = analogRead(ldrpin);
			value = constrain(value,900,1010);
			value = map(value,900,1010,255,0);
			Serial.println(value);
			analogWrite(ledpin, value);
			//delay(30);
		
			//Add code for Switch
			int time2,tim;
			digitalWrite(trigPin,HIGH);
			delayMicroseconds(100);
			digitalWrite(trigPin,LOW); 
			time2 = pulseIn(echoPin,HIGH);
			tim = time2/2;
			int dist = 0.034*tim;
			Serial.println(dist);
			if (dist<20 && dist>0){
				if (t==1){
				digitalWrite(ledpin,HIGH);
				t=0;
				}
			else{
				digitalWrite(ledpin,LOW);
				t=1;
				}
			}

			//Writes to DC Motor
			if(toSend == 190){
				//Move dc motor UP, rotate motor clockwise.
			}
			if(toSend == 191){
				//Move dc motor down, rotate motor anticlockwise
			}
			if(toSend == 192){
				//Move dc motor to default location
			}

			//Writes to servo
			//Serial.print(toSend);
			//Serial.print("\n");
     if(toSend >= 0 && toSend < 180) {
			  myservo.write(toSend);
      }
	  }
  }
			delay(150);

	
}

//Extra Functions
void setColor(int red, int green, int blue)
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}

//TO-DO
//Test run on arduino
//Play music on app
//Check delay
