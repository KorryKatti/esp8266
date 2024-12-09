#include <math.h>

const int trainingData[3][6] = {
    {100, 5000, 98, 10000, 1, 1},  // Tech Innovators Inc.
    {102, 6000, 101, 20000, -1, 0}, // Green Energy Solutions
    {98, 4500, 99, 15000, 0, 1}    // Health & Wellness Co.
};

const char* companyNames[3] = {"Tech Innovators Inc.", "Green Energy Solutions", "Health & Wellness Co."};

float w1 = 0.0;
float w2 = 0.0;
float w3 = 0.0;
float w4 = 0.0;
float w5 = 0.0;
float b = 0.0;
const float learningRate = 0.1;

float sigmoid(float x) {
    return 1.0 / (1.0 + exp(-x));
}

float sigmoidDerivative(float x) {
    float s = sigmoid(x);
    return s * (1 - s);
}

float predict(int x1, int x2, int x3, int x4, int x5) {
    return sigmoid((w1 * x1) + (w2 * x2) + (w3 * x3) + (w4 * x4) + (w5 * x5) + b);
}

void train(int epochs) {
    for (int epoch = 0; epoch < epochs; epoch++) {
        float totalLoss = 0;

        digitalWrite(2, HIGH);
        delay(50);
        digitalWrite(2, LOW);
        delay(50);

        for (int i = 0; i < 3; i++) {
            int x1 = trainingData[i][0];
            int x2 = trainingData[i][1];
            int x3 = trainingData[i][2];
            int x4 = trainingData[i][3];
            int x5 = trainingData[i][4];
            int yTrue = trainingData[i][5];

            // Prediction
            float yPred = predict(x1, x2, x3, x4, x5);

            // Error (how off we are)
            float error = yTrue - yPred;
            totalLoss += error * error;

            // Here's the math:
            /*
            dL_dyPred = -2 * error; // how much our error changes if prediction changes
            dyPred_dz = sigmoidDerivative((w1 * x1) + (w2 * x2) + (w3 * x3) + (w4 * x4) + (w5 * x5) + b); // how much our prediction changes if sum changes
            dz_dw1 = x1; // how much sum changes if weight w1 changes
            dz_dw2 = x2;
            dz_dw3 = x3;
            dz_dw4 = x4;
            dz_dw5 = x5;
            dz_db = 1; // how much sum changes if bias b changes

            dL_dw1 = dL_dyPred * dyPred_dz * dz_dw1; // chain rule: how much our error changes if weight w1 changes
            dL_dw2 = dL_dyPred * dyPred_dz * dz_dw2;
            dL_dw3 = dL_dyPred * dyPred_dz * dz_dw3;
            dL_dw4 = dL_dyPred * dyPred_dz * dz_dw4;
            dL_dw5 = dL_dyPred * dyPred_dz * dz_dw5;
            dL_db = dL_dyPred * dyPred_dz * dz_db;

            Update weights and bias:
            w1 -= learningRate * dL_dw1;
            w2 -= learningRate * dL_dw2;
            w3 -= learningRate * dL_dw3;
            w4 -= learningRate * dL_dw4;
            w5 -= learningRate * dL_dw5;
            b -= learningRate * dL_db;
            */
            float dL_dyPred = -2 * error;
            float dyPred_dz = sigmoidDerivative((w1 * x1) + (w2 * x2) + (w3 * x3) + (w4 * x4) + (w5 * x5) + b);

            float dz_dw1 = x1;
            float dz_dw2 = x2;
            float dz_dw3 = x3;
            float dz_dw4 = x4;
            float dz_dw5 = x5;
            float dz_db = 1;

            float dL_dw1 = dL_dyPred * dyPred_dz * dz_dw1;
            float dL_dw2 = dL_dyPred * dyPred_dz * dz_dw2;
            float dL_dw3 = dL_dyPred * dyPred_dz * dz_dw3;
            float dL_dw4 = dL_dyPred * dyPred_dz * dz_dw4;
            float dL_dw5 = dL_dyPred * dyPred_dz * dz_dw5;
            float dL_db = dL_dyPred * dyPred_dz * dz_db;

            w1 -= learningRate * dL_dw1;
            w2 -= learningRate * dL_dw2;
            w3 -= learningRate * dL_dw3;
            w4 -= learningRate * dL_dw4;
            w5 -= learningRate * dL_dw5;
            b -= learningRate * dL_db;
        }

        Serial.print("Epoch ");
        Serial.print(epoch + 1);
        Serial.print(", Loss: ");
        Serial.println(totalLoss / 3);
    }
}

void waitForStart() {
    while (true) {
        if (Serial.available() > 0) {
            String input = Serial.readStringUntil('\n');
            input.trim();
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
    pinMode(2, OUTPUT);
    Serial.begin(115200);
    Serial.println("Type 'start' in Serial Monitor to begin training.");

    waitForStart();

    w1 = random(-255, 255) / 255.0;
    w2 = random(-255, 255) / 255.0;
    w3 = random(-255, 255) / 255.0;
    w4 = random(-255, 255) / 255.0;
    w5 = random(-255, 255) / 255.0;
    b = random(-255, 255) / 255.0;

    train(1000);

    Serial.println("Training complete.");
    Serial.print("Final weights: w1 = ");
    Serial.print(w1);
    Serial.print(", w2 = ");
    Serial.print(w2);
    Serial.print(", w3 = ");
    Serial.print(w3);
    Serial.print(", w4 = ");
    Serial.print(w4);
    Serial.print(", w5 = ");
    Serial.print(w5);
    Serial.print(", b = ");
    Serial.println(b);

    for (int i = 0; i < 3; i++) {
        int x1 = trainingData[i][0];
        int x2 = trainingData[i][1];
        int x3 = trainingData[i][2];
        int x4 = trainingData[i][3];
        int x5 = trainingData[i][4];
        int yTrue = trainingData[i][5];
        float yPred = predict(x1, x2, x3, x4, x5);

        Serial.print("Company: ");
        Serial.print(companyNames[i]);
        Serial.print(", Previous Day's Closing Price: ");
        Serial.print(x1);
        Serial.print(", Volume: ");
        Serial.print(x2);
        Serial.print(", Previous Week's Average Price: ");
        Serial.print(x3);
        Serial.print(", Market Cap: ");
        Serial.print(x4);
        Serial.print(", News Sentiment: ");
        Serial.print(x5);
        Serial.print(", Prediction: ");
        Serial.print(yPred > 0.5 ? "Price Increase" : "Price Decrease");
        Serial.print(", True Value: ");
        Serial.println(yTrue == 1 ? "Price Increase" : "Price Decrease");
    }
}

void loop() {
}
