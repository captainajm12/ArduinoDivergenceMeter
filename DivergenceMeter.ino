/*
 LiquidCrystal Library - Hello World

Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
library works with all LCD displays that are compatible with the 
Hitachi HD44780 driver. There are many of them out there, and you
can usually tell them by the 16-pin interface.

This sketch prints "Hello World!" to the LCD
and shows the time.

 The circuit:
* LCD RS pin to digital pin 12
* LCD Enable pin to digital pin 11
* LCD D4 pin to digital pin 5
* LCD D5 pin to digital pin 4
* LCD D6 pin to digital pin 3
* LCD D7 pin to digital pin 2
* LCD R/W pin to ground
* 10K resistor:
* ends to +5V and ground
* wiper to LCD VO pin (pin 3)

Library originally added 18 Apr 2008
by David A. Mellis
library modified 5 Jul 2009
by Limor Fried (http://www.ladyada.net)
example added 9 Jul 2009
by Tom Igoe
modified 22 Nov 2010
by Tom Igoe
modified 7/11/2014
by Jingjing Yi, LinkSprite

This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

double worldlines[] = {0.337187, 0.409431, 0.456914, 0.523307, 0.571046, 1.143688, 1.130205, 1.129848, 1.048596};
const int worldlineCount = sizeof(worldlines) / sizeof(worldlines[0]);
int sensorValue; int keyTable[31];
unsigned long base = 47;
unsigned long upBtn = 75;
unsigned long downBtn = 62;

void generateKeyTable(int vcc,int* array) {
  float resistor;
  //1 key//
  resistor = ((float)upBtn)/(base + upBtn);
  *array++ = resistor*vcc;

  resistor = ((float)downBtn)/(base + downBtn);
  *array++ = resistor*vcc;
  
  //2 key//
  resistor = ((float)upBtn)*downBtn/(upBtn+downBtn);
  resistor = resistor/(resistor+base);
  *array++ = resistor*vcc;
}

unsigned char GetKey(int value) {
 char tmpChar;
 unsigned int Rst;

 tmpChar = 0;
 do{
   if(value > keyTable[tmpChar]) Rst = value - keyTable[tmpChar];
   else  Rst = keyTable[tmpChar] - value;
   tmpChar ++;
 } while(Rst > 1);

 return tmpChar--;
}

void setup() {
 // set up the LCD's number of columns and rows: 
 lcd.begin(16, 2);
 sensorValue  = 1023;
 //generateKeyTable(analogRead(A0),KeyTable);
}

void printVal(double v, int ms) {
    lcd.clear();
    lcd.setCursor(4, 2);
    lcd.print(v, 6);
    delay(ms);
}

void loop() {
 for(int i = 0; i < worldlineCount; i++) {
   
   worldlineChange();
   
   printVal(worldlines[i], 5000);
 }
}

void worldlineChange() {
 #if 0
  double changingNum = 0.000000;
  
  while(changingNum < 9) {
    changingNum += 1.234567;
    printVal(changingNum, 90);
  }
  #else
  int cnt;
  double val;
  for ( cnt = 0; cnt < 5; cnt++) {
    val = (((double) random(80000000)) / 8000000.0) + 1.0;
    
    printVal(val, 200);
  }
  #endif
}

void changeWorldline(){

}
