# Garage_Ram
 * Written by: Joo Min (Cai) Yeo
 * Last Edit: 201508021352 PST
 * Location: Fullerton, California, United States
 *
 * Project Description: This project was created to prevent my parent's cars from ramming
                       into garage walls when parking - inspired by watching my mother
                       and father scream after punching a hole in the wall with their car.
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
