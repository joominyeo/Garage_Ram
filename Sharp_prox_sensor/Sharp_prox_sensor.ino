
int proxSensor = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int raw = analogRead(proxSensor);
  Serial.println(raw);
  delay(100);
}

