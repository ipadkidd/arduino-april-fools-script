// Arduino Ultrasonic Buzzer Script

const int TRIG_PIN   = 6;
const int ECHO_PIN   = 5;
const int BUZZER_PIN = 3;

const int ON_THRESHOLD  = 20;
const int OFF_THRESHOLD = 28;

bool buzzerOn = false;

void setup() {
  pinMode(TRIG_PIN,   OUTPUT);
  pinMode(ECHO_PIN,   INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

long readDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  if (duration == 0) return 999;
  return duration / 58;
}

void loop() {
  long distance = readDistanceCM();

  if (!buzzerOn && distance <= ON_THRESHOLD) {
    buzzerOn = true;
    digitalWrite(BUZZER_PIN, HIGH);
  } else if (buzzerOn && distance > OFF_THRESHOLD) {
    buzzerOn = false;
    digitalWrite(BUZZER_PIN, LOW);
  }

  delay(100);
}
