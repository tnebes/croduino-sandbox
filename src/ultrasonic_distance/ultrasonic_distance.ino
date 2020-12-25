/*
 * based on code from https://e-radionica.com/hr/blog/2015/08/19/kkm-ultrazvucni-modul-hc-sr04/
 * uses Ultrasonic Ranging Module HC - SR04
 */ 

// digital pins
const int triggerPin = 2;
const int echoPin = 3;
const int redLEDPin = 4;
const int greenLEDPin = 5;
const float delayTime = 0.1;

void setup() {

    // setting up pins.
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(redLEDPin, OUTPUT);
    pinMode(greenLEDPin, OUTPUT);

    // establishing serial connection to main
    Serial.begin(9600);
    Serial.print("Measuring distance.\n");
}

void loop() {
    // pulseIn returns long value
    long time, distance;
    // Give me a ping Vasily. One ping only, please.
    onePing();

    time = pulseIn(echoPin, HIGH);
    Serial.print("Reflection time is: ");
    Serial.print(time);
    Serial.print("\n");

    distance = (time / 2) / 28;
    Serial.print("Distance in cm is: ");
    Serial.print(distance);
    Serial.print("\n");

    if (distance < 10) {
      digitalWrite(redLEDPin, HIGH);
      digitalWrite(greenLEDPin, LOW);  
    } else {
      digitalWrite(greenLEDPin, HIGH);
      digitalWrite(redLEDPin, LOW);    
    }

}

void onePing() {
    // send a pulse
    digitalWrite(triggerPin, HIGH);
    Serial.print("Ping!\n");
    // wait for ping to be sent
    delay(delayTime);
    // one ping finished
    digitalWrite(triggerPin, LOW);
}
