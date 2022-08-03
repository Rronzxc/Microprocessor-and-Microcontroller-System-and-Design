/*
Egg Incubator Remote

Objectives:
1.  To create a program using Arduino Uno R3, IR Remote Control and PIR Sensor.
2.  To utilize millis() in a program.
3.  To create an own circuit design that will satisfy the first two objectives of this study.


*Flow of the Program*
1. Start the system by clicking "Start Simulation". 
2. After clicking, the LCD will turn ON and a welcome message will flash on. 
   The LED for the system will also blink,indicating that the system is working.
3. Click the number from 1 to 3 to get a desired color for egg incubator
(1-RED, 2-GREEN, 3-WHITE). 
4. Lastly, when PIR sensor detects something is moving
the buzzer as well as its LED, will operate. After it detects that something
is moving, click the func/stop button and LCD will turn OFF(note: LED for the
system is still blinking because the system is still plugged in). 
5. Then click the power button to turn ON the LCD and start again the program. 
*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <IRremote.h>
LiquidCrystal_I2C lcd(32,16,2);
int IRpin=3;
IRrecv IR(IRpin);
int t=1000;
// RED LED Pin
int LED=8;
//  LED state
int LEDstate;
//RGB LED Pins//
int redLED=11;
int blueLED=10;
int greenLED=9;
//RGB read values//
int redVal;
int blueVal;
int greenVal;
//
int buzzer=7;
//Pir variables
int PIRPin=4;
int PIRVal;

//millis variables
unsigned long fromStartms;
unsigned long prevms;
unsigned long interval=500;

void setup()
{
Serial.begin(9600);
//IR sensor//
IR.enableIRIn();

pinMode(4, INPUT);
pinMode(13, OUTPUT);
  
//I2C LCD//
lcd.begin(16,2);
lcd.init();
lcd.backlight();
//LED
pinMode(LED,OUTPUT);

  //RGB LED//
pinMode(redLED,OUTPUT);
pinMode(blueLED,OUTPUT);
pinMode(greenLED,OUTPUT);
//PIR
pinMode(PIRPin,INPUT);

}

void loop()
{
{
lcd.setCursor(5,0);
lcd.print("HELLO!");
lcd.setCursor(3,1);
lcd.print("WELCOME TO");
delay(3000);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("RemoteControlled");
delay(1000);
lcd.setCursor(2,1);
lcd.print("EGG Incubator");
delay(1000);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Click Number Any");
lcd.setCursor(2,1);
lcd.print("From 1 to 3");
while(Serial.available()==0){
 
  {
  if (digitalRead(4) == HIGH) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }
  delay(10); // Delay a little bit to improve simulation performance
}
  
  //RGB read value//
  redVal=analogRead(redLED);
  blueVal=analogRead(blueLED);
  greenVal=analogRead(greenLED);
  
 
 
  //PIR read values
  PIRVal=digitalRead(PIRPin);
  // Pir Condition
  if(PIRVal==1)
  {
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("The egg has been");
   delay(500);
   lcd.setCursor(4,1);
   lcd.print("hatched!");
   delay(500);
 



  }
  //Blink LED
  
  fromStartms=millis();
  if(fromStartms - prevms > interval)
  {
    prevms = fromStartms;
    if(LEDstate==LOW);
    {
      LEDstate=HIGH;
      digitalWrite(LED,LEDstate);
    }
  }
      else
     {
       LEDstate=LOW;
       digitalWrite(LED,LEDstate);
     }
//IR sensor with Serial Monitor//

while (IR.decode())
{
 //Serial.println(IR.decodedIRData.decodedRawData,HEX);
 if(IR.decodedIRData.decodedRawData==0xEF10BF00)
 {
  Serial.println("1");
  //RGB LED Color:RED 
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("The Incubator");
  lcd.setCursor(1,1);
  lcd.print("Light is RED"); 
  analogWrite(redLED,255);
  analogWrite(greenLED,0);
  analogWrite(blueLED,0);
 
 }
 else if(IR.decodedIRData.decodedRawData==0xEE11BF00)
 {
  Serial.println("2");
  //RGB LED Color:Blue
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("The Incubator");
  lcd.setCursor(1,1);
  lcd.print("Light is GREEN");
  analogWrite(redLED,0);
  analogWrite(greenLED,255);
  analogWrite(blueLED,0);
  
  
 }
 else if(IR.decodedIRData.decodedRawData==0xED12BF00)
 {
  Serial.println("3");
  //RGB LED Color:Green
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("The Incubator");
  lcd.setCursor(1,1);
  lcd.print("Light is WHITE");
  analogWrite(redLED,255);
  analogWrite(greenLED,255);
  analogWrite(blueLED,255);
  
 }
else if(IR.decodedIRData.decodedRawData==0xFD02BF00)
{
lcd.clear();
Serial.println("Off");
analogWrite(redLED,0);
analogWrite(greenLED,0);
analogWrite(blueLED,0);
lcd.setCursor(5,0);
lcd.print("Remove");
delay(1000);
lcd.setCursor(3,1);
lcd.print("The Chick");
delay(1000);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Click the power.");
delay(1000);
lcd.setCursor(3,1);
lcd.print("To Turn On");
delay(1000);
lcd.setBacklight(0);
lcd.clear();
delay(2000);
IR.resume();
}
else if(IR.decodedIRData.decodedRawData==0xFF00BF00)
{ 
lcd.setBacklight(1);
lcd.setCursor(0,0);
lcd.print("Click Number Any");
lcd.setCursor(2,1);
lcd.print("From 1 to 3");
} 

delay(t);
IR.resume();
  
 
}  
  
}
}
}
