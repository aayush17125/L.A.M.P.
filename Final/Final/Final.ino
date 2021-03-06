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
//LED -> 5 PWM
//LDR -> A0 Analog Input
//SERVO -> 3 PWM
//DC MOTOR -> 6 PWM
//RED -> 9 PWM
//BLUE -> 11 PWM
//GREEN -> 10 PWM

//GLOBAL VARIABLES
const int dc_a = 8;
const int dc_b = 7;
const int dcMotorPin = 6;
int ledpin = 5;
int redPin = 9; //IT HAS TO BE A PWM
int greenPin = 10;
int bluePin = 11;
int ldrpin = A0;
int value = 0;
int rgb_global=0;
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
 	myservo.attach(3);
	Serial.begin(9600);
	pinMode(ledpin,OUTPUT);
	pinMode(echoPin,INPUT);    //Echo
	pinMode(trigPin,OUTPUT);    //Trigger
	digitalWrite(ledpin,LOW);
	digitalWrite(trigPin,LOW);
	pinMode(redPin, OUTPUT);
	pinMode(greenPin, OUTPUT);
	pinMode(bluePin, OUTPUT);
  pinMode(dc_a,OUTPUT);
  pinMode(dc_b,OUTPUT);
  setColor(0, 0, 0);
  digitalWrite(dc_a,LOW);
  digitalWrite(dc_b,LOW);
//	pinMode(ledPin, OUTPUT);
//	bluetooth.begin(9600);
}

//LOOPING CODE
void loop() {
//   analogWrite(dcM/otorPin,50); // DC motor speed control
      //Add code for LDR
      value = analogRead(ldrpin);
      value = constrain(value,0,255);
      value = map(value,0,255,255,30);
      Serial.print(value);
      Serial.println(" ldr");
//      analogWrite(ledpin, value);
      //delay(30);
   //Add code for Switch
     int time2,tim;
      digitalWrite(trigPin,HIGH);
      delayMicroseconds(100);
      digitalWrite(trigPin,LOW); 
      time2 = pulseIn(echoPin,HIGH);
      tim = time2/2;
      int dist = 0.034*tim;
      Serial.print(dist);
      Serial.println(" dist");
      if (dist<20 && dist>0){
        if (t==1){
//        digitalWrite(ledpin,HIGH);
          analogWrite(ledpin, value);
        t=0;
        }
      else{
//        digitalWrite(ledpin,LOW);
          analogWrite(ledpin,0);
        t=1;
        }
      }
      if (t==0){
        analogWrite(ledpin,value);
      }
      
	if(Serial.available() > 0){
		int toSend = Serial.read();
    Serial.print(toSend);
    Serial.println(" tosend");
		if(toSend == 200) {
			//Add code for varying RGB lights
//			setColor(1, 0, 0);  // red lowest brightness
//			delay(1000);
//			setColor(50, 0, 0);  // red
//			delay(1000);
//			setColor(140, 0, 0);  // red
//			delay(1000);
//      while(toSend != 200){
//        toSend = Serial.read();
        rgb_global = 1;}
     else if (toSend == 201){
      rgb_global = 0; 
     }
//  			setColor(255, 0, 0);  // red
//        delay(100);
//        setColor(0, 255, 0);  // green
//        delay(100);
//        setColor(0, 0, 255);  // blue
//        delay(100);
//        setColor(255, 255, 0);  // yellow
//        delay(100);  
//        setColor(80, 0, 80);  // purple
//        delay(100);
//        setColor(255, 50, 0);  // Orange
//        delay(100);
//		  }
		
		else {
		
		
			setColor(0, 0, 0);

			//Writes to DC Motor
			if(toSend == 190){
				//Move dc motor UP, rotate motor clockwise.
       digitalWrite(dc_a,HIGH); // Moving the motor
       digitalWrite(dc_b,LOW);
       delay(200);
       digitalWrite(dc_a,LOW); // Reseting the motor
       digitalWrite(dc_b,LOW);
			}
			if(toSend == 195){
				//Move dc motor down, rotate motor anticlockwise
        digitalWrite(dc_a,LOW);
        digitalWrite(dc_b,HIGH);
        delay(1000);
        digitalWrite(dc_a,LOW);
        digitalWrite(dc_b,LOW);
			}
//			if(toSend == 192){
//				Move dc motor to default location
//			}

			//Writes to servo
			//Serial.print(toSend);
			//Serial.print("\n");
     if(toSend >= 0 && toSend < 180) {
        Serial.println("loooooooooooooooooooooop");
			  myservo.write(toSend);
      }
	  }
  }
  if (rgb_global==1){
        setColor(255, 0, 0);  // red
        delay(100);
        setColor(0, 255, 0);  // green
        delay(100);
        setColor(0, 0, 255);  // blue
        delay(100);
        setColor(255, 255, 0);  // yellow
        delay(100);  
        setColor(80, 0, 80);  // purple
        delay(100);
        setColor(255, 50, 0);  // Orange
  }
  else{
    setColor(0,0,0);
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
