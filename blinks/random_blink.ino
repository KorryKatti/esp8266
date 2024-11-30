void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // Set the built-in LED as an output1
  randomSeed(analogRead(A0));  // Initialize random seed (use A0 to introduce variability)
}

void loop() {
  int onTime = random(100, 2000); // Generate a random ON time between 100ms and 2000ms
  int offTime = random(100, 2000); // Generate a random OFF time between 100ms and 2000ms

  digitalWrite(LED_BUILTIN, LOW); // Turn the LED on (LOW is ON for ESP8266)
  delay(onTime);                 // Wait for the random ON time
  digitalWrite(LED_BUILTIN, HIGH); // Turn the LED off (HIGH is OFF for ESP8266)
  delay(offTime);                // Wait for the random OFF time
}
