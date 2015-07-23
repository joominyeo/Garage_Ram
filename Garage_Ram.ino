/*
 * Written by: Joo Min (Cai) Yeo
 * Last Edit: 201507231134 PST
 * Location: Fullerton, California, United States
 *
 * Project Description: This project was created to prevent my parent's cars from ramming
 *                      into garage walls when parking - inspired by watching my mother
 *                      and father scream after punching a hole in the wall with their car.
 *
 * Project Cost: $29.94 USD
 *
 * Analog write reference, https://www.arduino.cc/en/Reference/analogWrite
 * 7-Seg display code from Rui Santos, http://randomnerdtutorials.com/arduino-temperature-displayed-on-4-digit-7-segment/
 * Wiring schematics, http://www.instructables.com/id/Arduino-4-digit-7-segment-display/
 *
 * 1) Sound Sensor(SON) picks up the sound from Analog 0
 * 2) Photoresistor Sensor(PHR) picks up the light fron the headlights only at night from Analog 1
 * 3) Sharp IR Sensor(SIR) measure the distance from 20 - 150 cm from Analog 2
 * 4) Distance 80 ~ 150 cm lights the Green LED's at Digital 2
 * 5) Distance 30 ~ 80 cm lights the Yellow LED's at Digital 3
 * 6) 7 Segment 4 Digit Anode displays(SFD) the distance as it is updated by the SIR
 * 7) IR Obstacle Avoidance Module(OAM) measure the distance from 3 - 30 cm from Analog 3
 * 8) Distance 2 ~ 30 cm lights the Red LED's at Digital 4
 *
*/

int SONpin = 0;
int SON = 0;
int PHRpin = 1;
int PHR = 0;
int SIRpin = 2;
int SIR = 0;
int OAMpin = 3;
int OAM = 0;
int dist = 650; //in centimetres

const int digitPins[4] = {
  5,6,7,8};                 //4 common anode pins of the display
const int clockPin = 9;    //74HC595 Pin 9
const int latchPin = 10;    //74HC595 Pin 10
const int dataPin = 11;     //74HC595 Pin 11
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
int digitBuffer[4] = {0};
int digitScan = 0, flag=0,  soft_scaler = 0;

void setup() {
  delay(100);
  Serial.begin(9600);
  delay(100);
  Serial.println("Initiating Garage_Ram");
  
  for(int i=0;i<4;i++) {
    pinMode(digitPins[i],OUTPUT);
  }
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  for (int x = 0; x < 10; x++) {
    Serial.print(".");
    delay(500);
  }
  Serial.println(" 100%");
  delay(1000);
  Serial.println("Preventing Garage Ramming!");
  delay(100);
}

void loop() {
  if(dist > 150 && (SON > 400 || PHR < 500)) { //SOUND INPUT FROM GARAGE & LUX FROM HEADLIGHTS
    //flash all three LED's
    updateDist(0);
  }
  else{
    if(dist < 150 && dist > 70) {
      /*GREEN LED's
      */
      updateDist(0);
      updateDisp;
      delay(2);
    }
    else if(dist < 90 && dist > 30) {
      /*YELLOW LED's
      */
      updateDist(0);
      updateDisp;
      delay(2);
    }
    else if(dist < 30) {
      /*RED LED's
      */
      updateDist(1);
      updateDisp;
      delay(2);
    }
  }
}

void updateDist(int mode) {
  if (mode == 0) dist = 20798 * pow(analogRead(SIR),-1.109);
  else ;//EQUATION FOR OAM - NEEDS TO BE CALIBRATED
}

void updateDisp(){
  digitBuffer[3] = int(dist * 100)/1000;
  digitBuffer[2] = (int(dist * 100)%1000)/100;
  digitBuffer[1] = (int(dist * 100)%100)/10;
  digitBuffer[0] = (int(dist * 100)%100)%10;
  
  for(byte j=0; j<4; j++)  
    digitalWrite(digitPins[j], LOW);
 
  digitalWrite(latchPin, LOW);  
  shiftOut(dataPin, clockPin, MSBFIRST, B11111111);
  digitalWrite(latchPin, HIGH);
 
  delayMicroseconds(100);
  digitalWrite(digitPins[digitScan], HIGH); 
 
  digitalWrite(latchPin, LOW);  
  /* NO NEED FOR DECIMAL POINT b/c dist IN CENTIMETRES
  if(digitScan==2)
    shiftOut(dataPin, clockPin, MSBFIRST, ~(digit[digitBuffer[digitScan]] | B10000000)); //print the decimal point on the 3rd digit
  else
    shiftOut(dataPin, clockPin, MSBFIRST, ~digit[digitBuffer[digitScan]]);
   */
  digitalWrite(latchPin, HIGH);
  digitScan++;
  if(digitScan>3) digitScan=0; 
}
