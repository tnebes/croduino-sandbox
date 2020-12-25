/*
 * A simple hello lamp program that makes the lamp on the breadboard blink.
 */

int duration = 1000;

void setup() {
  pinMode(2, OUTPUT);
}

void loop() {
  digitalWrite(2, HIGH);
  delay(duration);
  duration -= 100;
  digitalWrite(2, LOW);
  delay(duration);
  duration -= 100;
  if (duration < 200) {
    duration = 1000;
  }
}
