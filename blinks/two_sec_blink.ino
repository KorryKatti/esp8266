void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // Set the built-in LED as an output
}

void loop() {
  digitalWrite(LED_BUILTIN, LOW); // Turn the LED on (LOW is ON for ESP8266)
  delay(2000);                   // Wait for 2 seconds
  digitalWrite(LED_BUILTIN, HIGH); // Turn the LED off (HIGH is OFF for ESP8266)
  delay(2000);                    // Wait for 2 seconds
}
