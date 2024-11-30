void setup() {
  Serial.begin(115200);           // Initialize serial communication
  pinMode(LED_BUILTIN, OUTPUT);    // Set built-in LED as output
  Serial.println("2x2 Matrix Operations");
}

void loop() {
  // Wait for "start" to begin
  Serial.println("Type 'start' to begin inputting matrices.");
  while (true) {
    while (Serial.available() == 0) {}  // Wait for input
    String command = Serial.readString();  // Read the input string
    command.trim();  // Remove any extra spaces or newlines
    if (command == "start") {
      break;  // Break out of the loop when user types "start"
    } else {
      Serial.println("Invalid command! Type 'start' to begin.");
    }
  }

  // Declare 2x2 matrices
  int matrixA[2][2], matrixB[2][2], result[2][2];
  
  // Get matrix A input
  Serial.println("Enter values for Matrix A (2x2):");
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      Serial.print("Enter A[");
      Serial.print(i);
      Serial.print("][");
      Serial.print(j);
      Serial.print("]: ");
      while (Serial.available() == 0) {} // Wait for input
      matrixA[i][j] = Serial.parseInt(); // Get the value
      while (Serial.available() > 0) { Serial.read(); } // Clear remaining data in the buffer
    }
  }

  // Get matrix B input
  Serial.println("Enter values for Matrix B (2x2):");
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      Serial.print("Enter B[");
      Serial.print(i);
      Serial.print("][");
      Serial.print(j);
      Serial.print("]: ");
      while (Serial.available() == 0) {} // Wait for input
      matrixB[i][j] = Serial.parseInt(); // Get the value
      while (Serial.available() > 0) { Serial.read(); } // Clear remaining data in the buffer
    }
  }

  // Display the input matrices
  Serial.println("\nMatrix A:");
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      Serial.print(matrixA[i][j]);
      Serial.print(" ");
    }
    Serial.println();
  }

  Serial.println("\nMatrix B:");
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      Serial.print(matrixB[i][j]);
      Serial.print(" ");
    }
    Serial.println();
  }

  // Choose operation
  Serial.println("Choose operation: +, -, or *");
  while (Serial.available() == 0) {} // Wait for operation input
  char operation = Serial.read(); // Read the operation
  while (Serial.available() > 0) { Serial.read(); } // Clear any remaining data

  // Blink the LED to indicate "thinking"
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_BUILTIN, LOW); // Turn LED ON
    delay(200);                     // 200ms delay
    digitalWrite(LED_BUILTIN, HIGH); // Turn LED OFF
    delay(200);                     // 200ms delay
  }

  // Perform the chosen operation
  switch (operation) {
    case '+':
      // Matrix addition
      for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
          result[i][j] = matrixA[i][j] + matrixB[i][j];
        }
      }
      Serial.println("Result of A + B:");
      break;

    case '-':
      // Matrix subtraction
      for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
          result[i][j] = matrixA[i][j] - matrixB[i][j];
        }
      }
      Serial.println("Result of A - B:");
      break;

    case '*':
      // Matrix multiplication
      for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
          result[i][j] = 0;
          for (int k = 0; k < 2; k++) {
            result[i][j] += matrixA[i][k] * matrixB[k][j];
          }
        }
      }
      Serial.println("Result of A * B:");
      break;

    default:
      Serial.println("Invalid operation! Please use +, -, or *.");
      return; // Exit loop if invalid operation
  }

  // Display result matrix
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      Serial.print(result[i][j]);
      Serial.print(" ");
    }
    Serial.println();
  }

  // LED ON for 2 seconds to indicate result
  digitalWrite(LED_BUILTIN, LOW); // Turn LED ON
  delay(2000);                    // Wait 2 seconds
  digitalWrite(LED_BUILTIN, HIGH); // Turn LED OFF

  // Wait before restarting
  delay(5000); // Delay 5 seconds before restarting loop
}


// serial monitor baud 115200 btw