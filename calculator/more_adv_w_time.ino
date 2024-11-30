void setup() {
  Serial.begin(115200);          // Initialize Serial communication
  pinMode(LED_BUILTIN, OUTPUT);  // Set built-in LED as output
  Serial.println("Enhanced Calculator Ready!");
}

void loop() {
  // Prompt the user for input
  Serial.println("Enter an operation (+, -, *, /) followed by two numbers:");
  Serial.println("Example: + 12 5, * -3 4, or / 10 2");
  
  while (Serial.available() == 0) {
    // Wait for input
  }
  
  // Read the input
  char operation = Serial.read();   // Read the operator
  int num1 = Serial.parseInt();     // Read the first number
  int num2 = Serial.parseInt();     // Read the second number
  
  float result = 0;                 // Store the result (use float for division)
  bool validOperation = true;       // Flag for valid operations

  // Blink the LED to indicate "thinking"
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_BUILTIN, LOW); // Turn LED ON
    delay(200);                     // 200ms delay
    digitalWrite(LED_BUILTIN, HIGH); // Turn LED OFF
    delay(200);                     // 200ms delay
  }
  

  // to run go to serial monitor baud 115200
  // Measure calculation time
  unsigned long startTime = millis(); // Start time

  // Perform the calculation
  if (operation == '+') {
    result = num1 + num2;
  } else if (operation == '-') {
    result = num1 - num2;
  } else if (operation == '*') {
    result = num1 * num2;
  } else if (operation == '/') {
    if (num2 != 0) {
      result = (float)num1 / num2;  // Perform division, cast to float for decimals
    } else {
      Serial.println("Error: Division by zero!");
      validOperation = false;
    }
  } else {
    Serial.println("Invalid operation! Please use +, -, *, or /.");
    validOperation = false;
  }

  unsigned long endTime = millis(); // End time
  unsigned long elapsedTime = endTime - startTime; // Calculate elapsed time
  
  // If the operation is valid, display the result and calculation time
  if (validOperation) {
    Serial.print("Result: ");
    Serial.println(result);
    Serial.print("Calculation Time: ");
    Serial.print(elapsedTime);
    Serial.println(" ms");

    // LED ON for 2 seconds to indicate the result
    digitalWrite(LED_BUILTIN, LOW); // Turn LED ON
    delay(2000);                   // Wait 2 seconds
    digitalWrite(LED_BUILTIN, HIGH); // Turn LED OFF
  }
}
