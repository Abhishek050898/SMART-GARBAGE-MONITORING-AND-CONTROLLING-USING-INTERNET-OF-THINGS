#include<LiquidCrystal.h> //HEADER FILE FOR LCD
LiquidCrystallcd(8, 9, 10, 11, 12, 13); //LCD WITH CONTROLLER CONNECTION (RS=8,
EN=9, D4=10, D5=11, D6=12, D7=13)
#define FULL 6 //ASSIGNED VALUE FOR GARBAGE FULL CONDITION
#include <Servo.h> //SERVO MOTOR HEADER FILE
Servo s1; //SERVO MOTOR 1
Servo s2; //SERVO MOTOR 1
const int trigPin = 5; //5th pin of the controller is connected to the trig pin of the ultrasonic
sensor
const int echoPin = 4; //4th pin of the controller is connected to the echo pin of the
ultrasonic sensor
#define metal A15 //A15 pin connected with metal sensor
#define buz 22 //22nd pin is connected with buzzer
#define mois A0 //A0 pin connected with moisture sensor
long duration, inches, cm; // ULTRA
int pos = 90, pos1 = 90, pos2 = 90 ; // FOR SERVO ROTATION
void iotsend(String datas); //iot function
void setup()
{
Serial.begin(9600);//input from matlab
 Serial2.begin(9600);//FOR IOT
[62]
lcd.begin(16, 2);
 //////////SERVO PINSETUP//////////////////////////
 s1.attach(6);//S.MOT1 PIN1
 s2.attach(7);//S.MOT2 PIN2
 //////////PIN SETUP/////////////////////////////////
pinMode(metal, INPUT);
pinMode(mois, INPUT);
pinMode(buz, OUTPUT);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
 ///////////LCD SETUP////////////////////////////
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("GARBAGE MONITOR");
lcd.setCursor(3, 1);
lcd.print("USING IOT");
delay(3000);
lcd.clear();
}
void loop()
{
 int wread = digitalRead(mois);
 int mread = analogRead(metal);
digitalWrite(trigPin, LOW); //ULTRASONIC
delayMicroseconds(2);
[63]
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 cm = duration * 0.034 / 2; // / 29 / 2;// calc to convert to cm
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("GARBAGE FILLING");
lcd.setCursor(0, 1);
lcd.print("DIST:");
lcd.print(cm);
lcd.print(" cm");
delay(700);
 if (cm < FULL)
 {
lcd.clear();
lcd.setCursor(2, 0);
lcd.print("GARBAGE FULL");
lcd.setCursor(0, 1);
lcd.print("DIST:" + String(cm) + " cm");
iotsend("*GARBAGE FULL#");
delay(2000);
 }
 else if(cm>20){
lcd.clear();
[64]
lcd.setCursor(2, 0);
lcd.print("GARBAGE EMPTY");
lcd.setCursor(0, 1);
lcd.print("DIST:" + String(cm) + " cm");
delay(2000);
 }
 while (Serial.available() > 0) //MATLAB DATA RECEIVING CHECK
 {
 char c = Serial.read();
 if (c == 'A') //plastic garbage
 {
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("PLASTIC GARBAGE");
digitalWrite(buz, HIGH);
delay(1000);
digitalWrite(buz, LOW);
 ///////////////////GARBAGE DISPOSED///////////////////////////////
 for (pos = 90; pos<= 160; pos += 1)
{ // goes from 90 degrees to 180 degrees
 s2.write(pos); // in steps of 1 degree
delay(12); // tell servo to go to position in variable 'pos'
 }
delay(500);
 /////////CLOSING////////////////////
 for (pos = 160; pos>= 90; pos -= 1)
[65]
 {
 s2.write(pos);
delay(12);
 }
iotsend("*PLASTIC GARBAGE#");
 c = 0;
 }
 else if(c == 'B'){
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("DECOMPOSABLE");
digitalWrite(buz, HIGH);
delay(1000);
digitalWrite(buz, LOW);
 ///////////////////GARBAGE DISPOSED///////////////////////////////
 for (pos = 90; pos<= 160; pos += 1)
{ // goes from 90 degrees to 180 degrees
 s2.write(pos); // in steps of 1 degree
delay(12); // tell servo to go to position in variable 'pos'
 }
delay(500);
 /////////CLOSING////////////////////
 for (pos = 160; pos>= 90; pos -= 1)
 {
 s2.write(pos);
delay(12);
 }
[66]
iotsend("*DECOMPOSABLE#");
 c = 0;
 }
 }
 if ( wread == 0 ) //wet garbage
 {
lcd.clear();
lcd.setCursor(0, 0);
digitalWrite(buz, HIGH);
lcd.print("WET GARBAGE");
delay(1000);
digitalWrite(buz, LOW);
 ///////////////////GARBAGE DISPOSED///////////////////////////////
 for (pos = 90; pos>= 20; pos -= 1)
{ // goes from 90 degrees to 0 degrees
 s1.write(pos); // in steps of 1 degree
delay(12); // tell servo to go to position in variable 'pos'
 }
delay(500);
 /////////CLOSING////////////////////
 for (pos = 20; pos<= 90; pos += 1)
 {
 s1.write(pos);
delay(12);
 }
iotsend("*WET GARBAGE#");
[67]
 }
 if (mread == 0) //metal garbage
 {
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("METAL GARBAGE");
digitalWrite(buz, HIGH);
delay(1000);
digitalWrite(buz, LOW);
 ///////////////////GARBAGE DISPOSED///////////////////////////////
 while ((pos1 <= 180) && (pos2 >= 45)) // to down
 {
 s1.write(pos1);
 s2.write(pos2);
 pos1++;
 pos2--;
delay(12);
 }
delay(1500);
 while ((pos1 >= 90) && (pos2 <= 90)) // to up
 {
 s1.write(pos1);
 s2.write(pos2);
 pos1--;
 pos2++;
delay(12);
[68]
 }
iotsend("*METAL GARBAGE#");
 }
}
void iotsend(String datas)
{
 for (int i = 0; i<datas.length(); i++)
 {
 Serial2.write(datas[i]);
 }
delay(1000);
 Serial2.println();
}
