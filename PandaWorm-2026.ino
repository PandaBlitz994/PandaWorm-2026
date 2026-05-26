// pins defenitions
const byte SUCKTION_PUMPING = 2; // 0 = sucktion / 1 = pumping
const byte VALVE1_PIN = 3; // First valve
const byte VALVE2_PIN = 4; // Second valve
const byte VALVE3_PIN = 5; // Third valve
const byte BAT_PIN = 6; // Bttery on/off control pin
const byte BUTTON_PIN = 8; // Button pin

// Timing variables
const int spike_time = 50; // Time to avoid electric spikes 
const int pumping_time = 2000 - spike_time;   // 2 seconds
const int sucktion_time = 1500 - spike_time;  // 1.5 seconds

void setup() {
  // Components setting
  pinMode(SUCKTION_PUMPING, OUTPUT);
  pinMode(VALVE1_PIN, OUTPUT);
  pinMode(VALVE2_PIN, OUTPUT);
  pinMode(VALVE3_PIN, OUTPUT);
  pinMode(BAT_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  while (digitalRead(BUTTON_PIN)); // Waiting for the button to be pressed before passing to the loop
  delay(100);
  digitalWrite(BAT_PIN, 1);
}

void loop() {
  // --- pumping ---
  // First vertebra
  pumpingReset(); // Enter pumping mode
  digitalWrite(VALVE1_PIN, 0); // Navigating the pump to the first vertebra
  delay(pumping_time);
  // Second vertebra 
  digitalWrite(VALVE1_PIN, 1); // Navigating the pump to the second vertebra
  delay(pumping_time);
  // Third vertebra 
  digitalWrite(VALVE2_PIN, 1); // Navigating the pump to the third vertebra
  delay(pumping_time);
  // Fourth vertebra 
  digitalWrite(VALVE3_PIN, 1); // Navigating the pump to the fourth vertebra
  delay(pumping_time);

  // --- sucktion ---
  // First vertebra
  sucktionReset(); // Enter sucktion mode
  digitalWrite(VALVE1_PIN, 0); // Navigating the pump to the first vertebra
  delay(sucktion_time);
  // Second vertebra
  digitalWrite(VALVE1_PIN, 1); // Navigating the pump to the second vertebra
  delay(sucktion_time);
  // Third vertebra 
  digitalWrite(VALVE2_PIN, 1); // Navigating the pump to the third vertebra
  delay(sucktion_time);
  // Fourth vertebra 
  digitalWrite(VALVE3_PIN, 1); // Navigating the pump to the fourth vertebra
  delay(sucktion_time);
}


// --- Reset functions ---
void sucktionReset() { // Reset to enter suction mode
  digitalWrite(VALVE1_PIN, 0);
  digitalWrite(VALVE2_PIN, 0);
  digitalWrite(VALVE3_PIN, 0);
  digitalWrite(SUCKTION_PUMPING, 0);
}

void pumpingReset(){ // Reset to enter pumping mode
  digitalWrite(VALVE1_PIN, 0);
  digitalWrite(VALVE2_PIN, 0);
  digitalWrite(VALVE3_PIN, 0);
  digitalWrite(SUCKTION_PUMPING, 1);
}
