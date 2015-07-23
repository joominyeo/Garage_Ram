
int proxSensor = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Start countdown:");
  Serial.println("3");
  delay(1000);
  Serial.println("2");
  delay(1000);
  Serial.println("1");
  delay(1000);
  Serial.println("GO");
  delay(1000);
}

void loop() {
  int raw = analogRead(proxSensor);
  int dist = 20798 * pow(raw,-1.109);
  Serial.println(dist);
  delay(1000);
}
