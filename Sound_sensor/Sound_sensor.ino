int SONpin = 0;
int SON = 0;

void setup() {
  delay(1000);
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  Serial.println(analogRead(SONpin));
  delay(10);

}
