// Footstep Energy Generator - Sensor Monitoring
// Board: Arduino Nano | Sensors: 8 piezoelectric elements (A0-A7)

const int NUM_SENSORS = 8;
const int sensorPins[NUM_SENSORS] = {A0, A1, A2, A3, A4, A5, A6, A7};
const float VREF = 5.0;          // Nano reference voltage
const float STEP_THRESHOLD = 0.5; // Volts; adjust after testing

void setup() {
  Serial.begin(9600);
  Serial.println("Footstep Energy Generator started");
}

void loop() {
  float total = 0;

  for (int i = 0; i < NUM_SENSORS; i++) {
    int raw = analogRead(sensorPins[i]);
    float volts = raw * (VREF / 1023.0);
    total += volts;

    if (volts > STEP_THRESHOLD) {
      Serial.print("Footstep on sensor ");
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(volts, 2);
      Serial.println(" V");
    }
  }

  if (total > STEP_THRESHOLD) {
    Serial.print("Total voltage: ");
    Serial.print(total, 2);
    Serial.println(" V");
  }

  delay(50);
}
