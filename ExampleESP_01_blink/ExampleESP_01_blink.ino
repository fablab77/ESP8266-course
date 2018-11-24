#define LED_PIN D0
long lastChange = 0;
long ms;
int period = 300;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  ms = millis();
  if (ms - lastChange > period) {
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    lastChange = ms;
  }

}
