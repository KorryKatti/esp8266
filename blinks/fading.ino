void setup() {
  pinMode(LED_BUILTIN, OUTPUT);  // Set the built-in LED as output
}

void loop() {
  // Fade in slowly with a smoother, natural transition
  for (int i = 0; i <= 255; i++) {
    int brightness = int(127.5 * (sin(i * PI / 255) + 1));  // Smooth sine wave transition
    analogWrite(LED_BUILTIN, brightness);  // Set the brightness of the LED
    delay(30);  // Slow down the fade-in transition even more
  }

  delay(2000);  // Pause at full brightness for 2 seconds

  // Fade out slowly with a smoother, natural transition
  for (int i = 255; i >= 0; i--) {
    int brightness = int(127.5 * (sin(i * PI / 255) + 1));  // Smooth sine wave transition
    analogWrite(LED_BUILTIN, brightness);  // Set the brightness of the LED
    delay(30);  // Slow down the fade-out transition even more
  }

  delay(2000);  // Pause at off state for 2 seconds
}
