/*
  Project: Secure Underwater Data & Audio Transmission System using Li-Fi Technology
  Target: Embedded Systems / Hardware Prototype
  Description: Microcontroller-based optical wireless communication using modulation.
*/

#include <Arduino.h>

// Define pins for Transmitter and Receiver
const int ledTxPin = 9;      // PWM Pin connected to transmitter LED/Laser
const int photoRxPin = A0;   // Analog Pin connected to photodiode receiver

const int thresholdLevel = 500; // Threshold to detect light pulses

void setup() {
  // Initialize Serial Communication for debugging
  Serial.begin(9600);
  
  // Configure Pins
  pinMode(ledTxPin, OUTPUT);
  pinMode(photoRxPin, INPUT);
  
  Serial.println("Li-Fi Communication System Initialized.");
}

void loop() {
  // --- TRANSMITTER DEMO (Sending Data via Light Modulation) ---
  char dataToSend = 'H'; // Sample character
  transmitData(dataToSend);
  
  // --- RECEIVER DEMO (Reading Data via Photodiode) ---
  int lightSensorValue = analogRead(photoRxPin);
  
  if (lightSensorValue > thresholdLevel) {
    Serial.println("Light Pulse Detected: HIGH (Binary 1)");
  } else {
    Serial.println("Light Pulse Detected: LOW (Binary 0)");
  }
  
  delay(1000); // 1-second transmission interval
}

void transmitData(char data) {
  // Simple On-Off Keying (OOK) modulation based on bits
  for (int i = 0; i < 8; i++) {
    if ((data >> i) & 0x01) {
      digitalWrite(ledTxPin, HIGH); // Send bit 1 (Light ON)
    } else {
      digitalWrite(ledTxPin, LOW);  // Send bit 0 (Light OFF)
    }
    delay(50); // Modulation delay
  }
  digitalWrite(ledTxPin, LOW);
}
