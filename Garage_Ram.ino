/*
 * Written by: Joo Min (Cai) Yeo
 * Last Edit: 201507152258 PST
 *
 * Project Description: This project was created to prevent the cars from ramming into
 *                      garage walls when parking - inspired by watching my mother and
 *                      father scream after punching a hole in the wall.
 *
 * Project Cost: $29.94 USD
 *
 * Analog write reference, https://www.arduino.cc/en/Reference/analogWrite
 * 7-Seg display code from Rui Santos, http://randomnerdtutorials.com/arduino-temperature-displayed-on-4-digit-7-segment/
 * Wiring schematics, http://www.instructables.com/id/Arduino-4-digit-7-segment-display/
*/

const int digitPins[4] = {
  4,5,6,7};                 //4 common anode pins of the display
const int clockPin = 11;    //74HC595 Pin 11 
const int latchPin = 12;    //74HC595 Pin 12
const int dataPin = 13;     //74HC595 Pin 14
const int tempPin = A0;     //temperature sensor pin
const byte digit[10] =      //seven segment digits in bits
{
  B00111111, //0
  B00000110, //1
  B01011011, //2
  B01001111, //3
  B01100110, //4
  B01101101, //5
  B01111101, //6
  B00000111, //7
  B01111111, //8
  B01101111  //9
};
int digitBuffer[4] = {
  0};
int digitScan = 0, flag=0,  soft_scaler = 0;
;
float tempK, tempC, tempF, temp;
 
void setup(){                
  for(int i=0;i<4;i++)
  {
    pinMode(digitPins[i],OUTPUT);
  }
  pinMode(tempPin, INPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(tempPin, INPUT);
}

void loop(){ 
  updateDisp();
  delay(2);
}
 
//writes the temperature on display
void updateDisp(){
  tempK = (((analogRead(tempPin)/ 1023.0) * 5.0) * 100.0);  
  //Converts Kelvin to Celsius minus 2.5 degrees error
  tempC = tempK - 273.0;   
  tempF = ((tempK - 2.5) * 9 / 5) - 459.67;
  //Celsius temperature display
  tempC = int(tempC*100);
  digitBuffer[3] = int(tempC)/1000;
  digitBuffer[2] = (int(tempC)%1000)/100;
  digitBuffer[1] = (int(tempC)%100)/10;
  digitBuffer[0] = (int(tempC)%100)%10;
  
  for(byte j=0; j<4; j++)  
    digitalWrite(digitPins[j], LOW);
 
  digitalWrite(latchPin, LOW);  
  shiftOut(dataPin, clockPin, MSBFIRST, B11111111);
  digitalWrite(latchPin, HIGH);
 
  delayMicroseconds(100);
  digitalWrite(digitPins[digitScan], HIGH); 
 
  digitalWrite(latchPin, LOW);  
  if(digitScan==2)
    shiftOut(dataPin, clockPin, MSBFIRST, ~(digit[digitBuffer[digitScan]] | B10000000)); //print the decimal point on the 3rd digit
    // NO NEED FOR DECIMAL POINT b/c dist IN CENTIMETRES
  else
    shiftOut(dataPin, clockPin, MSBFIRST, ~digit[digitBuffer[digitScan]]);
 
  digitalWrite(latchPin, HIGH);
  digitScan++;
  if(digitScan>3) digitScan=0; 
}
