#define IN1	3
#define IN2	9
#define IN3	10
#define IN4	11
#include<NewPing.h>// include newping library

NewPing sonar_1 (15, 15, 400);// create ultrasonic object with the following parameters (Trig=3, Echo=2, Max distance=400cm)
float distance_right;// initialize a variable of type float

NewPing sonar_2 (16, 16, 400);// create ultrasonic object with the following parameters (Trig=3, Echo=2, Max distance=400cm)
float distance_front;// initialize a variable of type float

NewPing sonar_3 (17, 17, 400);// create ultrasonic object with the following parameters (Trig=3, Echo=2, Max distance=400cm)
float distance_left;// initialize a variable of type float

int command;            //Int to store app command state.

int state = 0;

int irpin = 19; 


int a=0;


int led = 5;
int led_1 = 6;

int measurePin = A0; //Connect dust sensor to Arduino A0 pin
int ledPower = 2;   //Connect 3 led driver pins of dust sensor to Arduino D2

int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;

float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;

const int congtachanhtrinh = 3;  // Dây ra công tăc hành trình dây màu xanh nối chân 3   
//const int led =  13;  
int giatri = 0;  
#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM800L
SoftwareSerial SIM(12, 13); //SIM800L Tx & Rx is connected to Arduino #3 & #2
// Variable to store text message
String textMessage;
//String message;
// Create a variable to store Lamp state
String lampState = "HIGH";

// Relay connected to pin 12
//const int relay = 12;
char incomingChar;
void setup(){  
  
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
	pinMode(IN2, OUTPUT);
	pinMode(IN3, OUTPUT);
	pinMode(IN4, OUTPUT);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  
  pinMode(irpin, INPUT);

pinMode(led, OUTPUT);
digitalWrite(led, LOW);
  

pinMode(led_1, OUTPUT);
digitalWrite(led_1, LOW);


pinMode(ledPower,OUTPUT);

pinMode(congtachanhtrinh, INPUT);

// Set relay as OUTPUT
  //pinMode(relay, OUTPUT);

  // By default the relay is off
  //digitalWrite(relay, HIGH);
  
  // Initializing serial commmunication
  //Serial.begin(115200); 
  SIM.begin(115200);

  // Give time to your GSM shield log on to network
  delay(5000);
  Serial.println("SIM start...");
 
  // AT command to set SIM900 to SMS mode
  SIM.println("AT"); //Handshaking with SIM900
  delay(100);
  SIM.println("AT+CMGF=1"); 
  delay(100);
  // Set module to send SMS data to serial out upon receipt 
  SIM.println("AT+CNMI=2,2,0,0,0");
  delay(100);

} 

void goAhead(){ 
  
  analogWrite(IN1, LOW);
	analogWrite(IN2, 200);
  analogWrite(IN3, LOW);
	analogWrite(IN4, 200);

  }

void goBack(){ 

  analogWrite(IN1, 200);
	analogWrite(IN2, LOW);
  analogWrite(IN3, 200);
	analogWrite(IN4, LOW);

  }

void goRight(){ 

  analogWrite(IN1, 255);
  analogWrite(IN2, LOW);
  analogWrite(IN3, LOW);
  analogWrite(IN4, 255);

}

void goLeft(){
      
  analogWrite(IN1, LOW);
  analogWrite(IN2, 255);
  analogWrite(IN3, 255);
  analogWrite(IN4, LOW);
        
}

void stopRobot(){  

  analogWrite(IN1, LOW);
	analogWrite(IN2, LOW);
	analogWrite(IN3, LOW);
	analogWrite(IN4, LOW);
  
}

void Auto(){
  
distance_right = sonar_1.ping_cm();// putting the measured value in distance
Serial.print("Distance_right = ");// print "Distance"
Serial.print(distance_right);// print the value of the distance
Serial.println(" cm");// print "cm"
//delay(10);

distance_front = sonar_2.ping_cm();// putting the measured value in distance
Serial.print("Distance_front = ");// print "Distance"
Serial.print(distance_front);// print the value of the distance
Serial.println(" cm");// print "cm"
//delay(10);

distance_left = sonar_3.ping_cm();// putting the measured value in distance
Serial.print("Distance_left = ");// print "Distance"
Serial.print(distance_left);// print the value of the distance
Serial.println(" cm");// print "cm"
//delay(10);

  int s = digitalRead(irpin);
  int S_right = digitalRead(4);
  int S_left = digitalRead(7);
  if(s==HIGH)
  { 
    stopRobot();
    delay(1000);
    goBack();
    delay(1000);
    goRight();
    delay(1500);
  }

  if(S_right == LOW || S_left == LOW || (S_right == LOW && S_left == LOW))
  {
    goBack();
  }

  if((s==LOW)&&(distance_left <= 30 && distance_front <= 30 && distance_right <= 30))
    {
      goLeft();
      delay(1500);
    }
  if((s==LOW)&&(distance_left <= 30 && distance_front > 30 && distance_right <= 30))
    {
      goRight();
      delay(1500);
    }
  if ((s==LOW)&&(distance_left > 30 && distance_front > 30 && distance_right > 30))
  {//goBack
    goAhead();
  }
  if ((s==LOW)&&(distance_left <= 30 && distance_front <= 30 && distance_right > 30) || (s==LOW)&&(distance_left <= 30 && distance_front > 30 && distance_right > 30) || (s==LOW)&&(distance_left > 30 && distance_front <= 30 && distance_right > 30))
  {//goRight
    goRight();
  }
  if ((s==LOW)&&(distance_left > 30 && distance_front <= 30 && distance_right <= 30) || (s==LOW)&&(distance_left > 30 && distance_front > 30 && distance_right <= 30))
  {//goLeft
    goLeft();
  }  
  //delay(1000);

}
void highest()
{
  analogWrite(led, 255);
  //delay(100);
  analogWrite(led_1, 255);
  //delay(100);
  }
void medium()
{
  analogWrite(led, 200);
  analogWrite(led_1, 200);
  }
void lowest()
{
  analogWrite(led, 150);
  analogWrite(led_1, 150);
  }
void stop_mos()
{
  analogWrite(led,0);
  analogWrite(led_1,0);
  
  }
void Circle()
{
  goRight();
  delay(5000);
  goAhead();
  delay(1000);

}

void dust()
{
  digitalWrite(ledPower,LOW); // power on the LED
  delayMicroseconds(samplingTime);

  voMeasured = analogRead(measurePin); // read the dust value

  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH); // turn the LED off
  delayMicroseconds(sleepTime);

  // 0 - 5V mapped to 0 - 1023 integer values
  // recover voltage
  calcVoltage = voMeasured * (5.0 / 1024.0);

  // linear eqaution taken from http://www.howmuchsnow.com/arduino/airquality/
  // Chris Nafis (c) 2012
  dustDensity = 170 * calcVoltage - 0.1;


  Serial.println("Raw Signal Value (0-1023):");
  Serial.println(voMeasured);

  Serial.println("Voltage:");
  Serial.println(calcVoltage);

  Serial.println("Dust Density:");
  Serial.println(dustDensity); // unit: (muy) ug/m3
  //int a = round(dustDensity);
  if(dustDensity > 600)
  {
    Serial.println("HIGH");
    //String humidity = "Humidity: " + String(h) + "%";
    //String dust = a;
    String dust = "Dust density =" + String(dustDensity) + "ug/m3";    
    sendSMS_warning(dust);
    }
  else{
    Serial.println("LOW");
    /*for(int i=0; i <= 1;i++){
    String dust = "Dust density =" + String(dustDensity) + "ug/m3";
    sendSMS_warning(dust);
    }*/
    }
  
  delay(1000);
}

void dust_sensor()
{
  digitalWrite(ledPower,LOW); // power on the LED
  delayMicroseconds(samplingTime);

  voMeasured = analogRead(measurePin); // read the dust value

  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH); // turn the LED off
  delayMicroseconds(sleepTime);

  // 0 - 5V mapped to 0 - 1023 integer values
  // recover voltage
  calcVoltage = voMeasured * (5.0 / 1024.0);

  // linear eqaution taken from http://www.howmuchsnow.com/arduino/airquality/
  // Chris Nafis (c) 2012
  dustDensity = 170 * calcVoltage - 0.1;


  Serial.println("Raw Signal Value (0-1023):");
  Serial.println(voMeasured);

  Serial.println("Voltage:");
  Serial.println(calcVoltage);

  Serial.println("Dust Density:");
  Serial.println(dustDensity); // unit: (muy) ug/m3
  //int a = round(dustDensity);
  
  String dust = "Dust density =" + String(dustDensity) + "ug/m3";    
  sendSMS_warning(dust);
}

void loop(){

  if (Serial.available() > 0){ 
  command = Serial.read();
  
      if (command == 'F') state = 2;
      else if (command == 'B') state = 3;
      else if (command == 'L') state = 4;
      else if (command == 'R') state = 5;
      //else if (command == 'J') goBackRight();
      //else if (command == 'H') goBackLeft();
     /* else if (command == '0') speedCar = 400;
      else if (command == '1') speedCar = 470;
      else if (command == '2') speedCar = 540;
      else if (command == '3') speedCar = 610;
      else if (command == '4') speedCar = 680;
      else if (command == '5') speedCar = 750;
      else if (command == '6') speedCar = 820;
      else if (command == '7') speedCar = 890;
      else if (command == '8') speedCar = 960;
      else if (command == '9') speedCar = 1023;*/
      else if (command == 'S') state = 6;

      else if (command == 'A') state = 1;
      
      else if (command == 'P') state = 0;
      
      else if (command == 'O') state = 7;
      else if (command == 'M') state = 8;
      else if (command == 'C') state = 9;
      else if (command == 'I') state = 10;
      else if (command == 'U') state = 11;
      else if (command == 'D') state = 12;
      else if (command == 'G') state = 13;
      }

if(state == 1)
{
  Auto();
  }
  else if(state == 2)
  {
    goAhead();
    }
    else if(state == 3)
  {
    goBack();
    }
    else if(state == 4)
  {
    goLeft();
    }
    else if(state == 5)
  {
    goRight();
    }
    else if(state == 6)
  {
    stopRobot();
    }
    else if(state == 7)
  {
    highest();
    }
    else if(state == 8)
  {
    medium();
    }
    else if(state == 9)
  {
    lowest();
    }
    else if(state == 10)
  {
    Circle();
    }
    else if(state == 11)
  {
    //zigzag();
    }
    else if(state == 12)
  {
    dust_sensor();
    }
    else if(state == 13)
  {
    dust();
    }
  else
  {
      stop_mos();
    }

if(SIM.available()>0){
    textMessage = SIM.readString();
    Serial.print(textMessage);    
    delay(10);
  } 
  if(textMessage.indexOf("6541")>=0){
    
    goAhead();
    lampState = "goAhead";
    textMessage = "";   
  }
  if(textMessage.indexOf("6642")>=0){
    
    goBack();
    lampState = "goBack"; 
    textMessage = ""; 
  }
  
if(textMessage.indexOf("8353")>=0){
  
    lampState = "stop";
    stopRobot();   
    textMessage = ""; 
  }
if(textMessage.indexOf("2009")>=0){
  
    //lampState = "stop";
    dust_sensor();   
    textMessage = ""; 
  }
if(textMessage.indexOf("8454")>=0){
    String message = "State is " + lampState;
    sendSMS(message);
    textMessage = "";
  }

if (SMSRequest()){
    if(readData()){
      delay(10);
      // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
      // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
      SIM.println("AT + CMGS = \"+84358845831\"");
      delay(100);
      // REPLACE WITH YOUR OWN SMS MESSAGE CONTENT
      String read = "Dust density =" + String(dustDensity) + "ug/m3"; 
      SIM.print(read);
      delay(100);
      // End AT command with a ^Z, ASCII code 26
      SIM.write(26); 
      delay(100);
      SIM.println();
      // Give module time to send SMS
      delay(5000);  
    }
  }
  delay(10); 

}


// Function that sends SMS
void sendSMS(String message){
  // AT command to set SIM900 to SMS mode
  SIM.println("AT+CMGF=1"); 
  delay(100);

  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
  SIM.println("AT+CMGS=\"+84358845831\""); 
  delay(100);
  // Send the SMS
  SIM.println(message); 
  delay(100);

  // End AT command with a ^Z, ASCII code 26
  SIM.write(26); 
  delay(100);
  SIM.println();
  // Give module time to send SMS
  delay(5000);  
}

void sendSMS_warning(String dust){
  // AT command to set SIM900 to SMS mode
  SIM.println("AT+CMGF=1"); 
  delay(100);

  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
  SIM.println("AT+CMGS=\"+84358845831\""); 
  delay(100);
  // Send the SMS
  SIM.println(dust); 
  delay(100);

  // End AT command with a ^Z, ASCII code 26
  SIM.write(26); 
  delay(100);
  SIM.println();
  // Give module time to send SMS
  delay(5000);  
}

boolean readData()
{
  digitalWrite(ledPower,LOW); // power on the LED
  delayMicroseconds(samplingTime);

  voMeasured = analogRead(measurePin); // read the dust value

  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH); // turn the LED off
  delayMicroseconds(sleepTime);

  // 0 - 5V mapped to 0 - 1023 integer values
  // recover voltage
  calcVoltage = voMeasured * (5.0 / 1024.0);

  // linear eqaution taken from http://www.howmuchsnow.com/arduino/airquality/
  // Chris Nafis (c) 2012
  dustDensity = 170 * calcVoltage - 0.1;
if (isnan(dustDensity)) {
    Serial.println("Failed to read from DHT sensor!");
    return false;
  }

  Serial.println("Raw Signal Value (0-1023):");
  Serial.println(voMeasured);

  Serial.println("Voltage:");
  Serial.println(calcVoltage);

  Serial.println("Dust Density:");
  Serial.println(dustDensity); // unit: (muy) ug/m3
  return true;
}

boolean SMSRequest() {
  if(SIM.available() >0) {
    incomingChar=SIM.read();
    if(incomingChar=='53') {
      delay(10);
      Serial.print(incomingChar);
      incomingChar=SIM.read();
      if(incomingChar =='54') {
        delay(10);
        Serial.print(incomingChar);
        Serial.print("...Request Received \n");
              return true;
      }
    }
  }
  return false;
}