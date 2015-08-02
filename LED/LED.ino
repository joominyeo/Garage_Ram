int gled = 2;
int yled = 3;
int rled = 4;
void setup() {
  pinMode(gled, OUTPUT);
  pinMode(yled, OUTPUT);
  pinMode(rled, OUTPUT);
}

void loop() {
  digitalWrite(gled, HIGH);
  digitalWrite(gled, LOW);
  digitalWrite(yled, HIGH);
  digitalWrite(yled, LOW);
  digitalWrite(rled, HIGH);
  digitalWrite(rled, LOW);
}
