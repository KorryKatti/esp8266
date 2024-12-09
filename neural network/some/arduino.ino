#include <math.h>

// Training data (x1 = age, x2 = income, y_true = expected output)
const int trainingData[3][3] = {
    {30, 40000, 1},  // Example 1
    {45, 50000, 1},  // Example 2
    {25, 20000, 0}   // Example 3
};

// Neural network parameters (declaring them as floats)
float w1 = 0.0;  // Initial weight for x1 (age)
float w2 = 0.0;  // Initial weight for x2 (income)
float b = 0.0;   // Initial bias
const float learningRate = 0.1; // Learning rate (eta)

// Sigmoid activation function
float sigmoid(float x) {
    return 1.0 / (1.0 + exp(-x));
}

// Derivative of sigmoid function
float sigmoidDerivative(float x) {
    float s = sigmoid(x);
    return s * (1 - s);
}

// Forward pass to compute prediction
float predict(int x1, int x2) {
    return sigmoid((w1 * x1) + (w2 * x2) + b);
}

// Training function
void train(int epochs) {
    for (int epoch = 0; epoch < epochs; epoch++) {
        float totalLoss = 0; // Sum of MSE for this epoch

        // Blink the LED to indicate "thinking"
        digitalWrite(LED_BUILTIN, HIGH);
        delay(50);
        digitalWrite(LED_BUILTIN, LOW);
        delay(50);

        // Loop through training examples
        for (int i = 0; i < 3; i++) {
            int x1 = trainingData[i][0];
            int x2 = trainingData[i][1];
            int yTrue = trainingData[i][2];

            // Forward pass: calculate prediction
            float yPred = predict(x1, x2);

            // Calculate loss (MSE for this example)
            float error = yTrue - yPred;
            totalLoss += error * error;

            // Backward pass: compute gradients
            float dL_dyPred = -2 * error; // Derivative of MSE
            float dyPred_dz = sigmoidDerivative((w1 * x1) + (w2 * x2) + b); // Derivative of sigmoid

            // Gradients of weights and bias
            float dz_dw1 = x1;
            float dz_dw2 = x2;
            float dz_db = 1;

            // Chain rule to calculate parameter updates
            float dL_dw1 = dL_dyPred * dyPred_dz * dz_dw1;
            float dL_dw2 = dL_dyPred * dyPred_dz * dz_dw2;
            float dL_db = dL_dyPred * dyPred_dz * dz_db;

            // Update weights and bias
            w1 -= learningRate * dL_dw1;
            w2 -= learningRate * dL_dw2;
            b -= learningRate * dL_db;
        }

        // Print loss for this epoch
        Serial.print("Epoch ");
        Serial.print(epoch + 1);
        Serial.print(", Loss: ");
        Serial.println(totalLoss / 3); // Average loss
    }
}

void waitForStart() {
    while (true) {
        if (Serial.available() > 0) {
            String input = Serial.readStringUntil('\n');
            input.trim(); // Remove extra spaces or newline characters
            if (input.equalsIgnoreCase("start")) {
                Serial.println("Starting training...");
                break;
            } else {
                Serial.println("Type 'start' to begin.");
            }
        }
    }
}

void setup() {
    pinMode(LED_BUILTIN, OUTPUT); // Set the built-in LED as output
    Serial.begin(115200);        // Initialize Serial communication
    Serial.println("Type 'start' in Serial Monitor to begin training.");

    waitForStart(); // Wait for the user to type 'start'

    // Initialize weights randomly
    w1 = random(-255, 255) / 255.0;  // Random value between -1 and 1
    w2 = random(-255, 255) / 255.0;
    b = random(-255, 255) / 255.0;

    train(1000); // Train for 1000 epochs

    Serial.println("Training complete.");
    Serial.print("Final weights: w1 = ");
    Serial.print(w1);
    Serial.print(", w2 = ");
    Serial.print(w2);
    Serial.print(", b = ");
    Serial.println(b);

    // Test predictions
    for (int i = 0; i < 3; i++) {
        int x1 = trainingData[i][0];
        int x2 = trainingData[i][1];
        int yTrue = trainingData[i][2];
        float yPred = predict(x1, x2);

        Serial.print("Example ");
        Serial.print(i + 1);
        Serial.print(", Prediction: ");
        Serial.print(yPred);
        Serial.print(", True Value: ");
        Serial.println(yTrue);
    }
}

void loop() {
    // Nothing to do in loop since training is complete
}
