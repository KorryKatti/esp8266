void setup() {
  Serial.begin(115200);          // Initialize Serial communication
  pinMode(LED_BUILTIN, OUTPUT);  // Set built-in LED as output
  Serial.println("Basic Calculator Ready!");
}

void loop() {
  // Prompt the user for input
  Serial.println("Enter an operation (+ or -) followed by two numbers:");
  Serial.println("Example: + 12 5 or - 8 3");
  
  while (Serial.available() == 0) {
    // Wait for input
  }
  
  // Read the input
  char operation = Serial.read();   // Read the operator
  int num1 = Serial.parseInt();     // Read the first number
  int num2 = Serial.parseInt();     // Read the second number
  
  int result = 0;                   // Store the result
  bool validOperation = true;       // Flag for valid operations
  
  // Blink the LED to indicate "thinking"
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_BUILTIN, LOW); // Turn LED ON
    delay(200);                     // 200ms delay
    digitalWrite(LED_BUILTIN, HIGH); // Turn LED OFF
    delay(200);                     // 200ms delay
  }
  
  // Perform the calculation
  if (operation == '+') {
    result = num1 + num2;
  } else if (operation == '-') {
    result = num1 - num2;
  } else {
    Serial.println("Invalid operation! Please use + or -.");
    validOperation = false;
  }
  
  // If the operation is valid, display the result
  if (validOperation) {
    Serial.print("Result: ");
    Serial.println(result);
    
    // LED ON for 2 seconds to indicate the result
    digitalWrite(LED_BUILTIN, LOW); // Turn LED ON
    delay(2000);                   // Wait 2 seconds
    digitalWrite(LED_BUILTIN, HIGH); // Turn LED OFF
  }
}
