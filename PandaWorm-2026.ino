// pins defenitions
const byte SUCKTION_PUMPING = 2; // 0 = sucktion / 1 = pumping
const byte VALVE1_PIN = 3;
const byte VALVE2_PIN = 4;
const byte VALVE3_PIN = 5;

const byte TRIG_PIN = 6; // Ultrasonic trig pin
const byte ECHO_PIN = 7; // Ultrasonic echo pin

const byte BUZZER_PIN = 8; // Buzzer pin

// Timing variables
const int spike_time = 50; // Time to avoid electric spikes 
const int pumping_time = 2000 - spike_time;   // 2 seconds
const int sucktion_time = 1500 - spike_time;  // 1.5 seconds

const unsigned long sensorInterval = 60;  // Sensor reading delay
unsigned long seqInterval;                // Pumping/Sucktion delay

// millis variables
unsigned long prevSeqMillis;
unsigned long prevSensorMillis;
unsigned long currentMillis = 0;

// other variables
int sequenceStep = 0;
unsigned long dictance; // for containing ultrasonic sensor's result

void setup() {
  // pneumatics setting
  pinMode(SUCKTION_PUMPING, OUTPUT);
  pinMode(VALVE1_PIN, OUTPUT);
  pinMode(VALVE2_PIN, OUTPUT);
  pinMode(VALVE3_PIN, OUTPUT);

  // ultrasonic setting
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // buzzer setting
  pinMode(BUZZER_PIN, 1);

  // Reset before entering the big big loop
  seqInterval = sucktion_time; // start at sucktion
  prevSensorMillis = millis();
  prevSeqMillis = millis();
}

void loop() {
  currentMillis = millis(); // Resetting the current time

  if (currentMillis - prevSeqMillis >= seqInterval) {
    prevSeqMillis = currentMillis;

    switch (sequenceStep) {
      // --- sucktion ---
      // First vertebra
      case 0:
        sucktionReset(); // Enter sucktion mode
        digitalWrite(VALVE1_PIN, 0); // Navigating the pump to the first vertebra
        break;
      // Second vertebra 
      case 1:
        digitalWrite(VALVE1_PIN, 1); // Navigating the pump to the second vertebra
        break;
      // Third vertebra 
      case 2:
        digitalWrite(VALVE2_PIN, 1); // Navigating the pump to the third vertebra
        break;
      // Fourth vertebra 
      case 3:
        digitalWrite(VALVE3_PIN, 1); // Navigating the pump to the fourth vertebra
        break;

      // --- pumping ---
      // First vertebra
      case 4:
        pumpingReset(); // Enter pumping mode
        digitalWrite(VALVE1_PIN, 0); // Navigating the pump to the first vertebra
        break;
      // Second vertebra 
      case 5:
        digitalWrite(VALVE1_PIN, 1); // Navigating the pump to the second vertebra
        break;
      // Third vertebra 
      case 6:
        digitalWrite(VALVE2_PIN, 1); // Navigating the pump to the third vertebra
        break;
      // Fourth vertebra 
      case 7:
        digitalWrite(VALVE3_PIN, 1); // Navigating the pump to the fourth vertebra
        break;
    }
    sequenceStep ++; // Passing to the next case
    if (sequenceStep > 7) { // Reseting the switc case in case it ended
      sequenceStep = 0;
    }
  }


  if (currentMillis - prevSensorMillis >= sensorInterval) {
    prevSensorMillis = currentMillis;

    dictance = readUltrasonic();
    if (dictance < 15) {              // if somthing is detected beep
      digitalWrite(BUZZER_PIN, 1);
    }
    else{
      digitalWrite(BUZZER_PIN, 0);    // if nothing detected don't beep
    }
  }
}


long readUltrasonic() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2; // Returns distance in cm

  delay(spike_time); // Avoiding electrical spikes
}


// --- Reset functions ---
void sucktionReset() { // Reset to enter suction mode
  digitalWrite(VALVE1_PIN, 0);
  digitalWrite(VALVE2_PIN, 0);
  digitalWrite(VALVE3_PIN, 0);
  digitalWrite(SUCKTION_PUMPING, 0);
  seqInterval = sucktion_time; // Resetting the seqInterval to sucktion mode
}

void pumpingReset(){ // Reset to enter pumping mode
  digitalWrite(VALVE1_PIN, 0);
  digitalWrite(VALVE2_PIN, 0);
  digitalWrite(VALVE3_PIN, 0);
  digitalWrite(SUCKTION_PUMPING, 1);
  seqInterval = pumping_time; // Resetting the seqInterval to pumping mode
}