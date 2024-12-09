import numpy as np

# Training data and company names
training_data = np.array([
    [100, 5000, 98, 10000, 1, 1], 
    [102, 6000, 101, 20000, -1, 0],
    [98, 4500, 99, 15000, 0, 1]
])
company_names = ["Tech Innovators Inc.", "Green Energy Solutions", "Health & Wellness Co."]

# Initialize parameters randomly
def initialize_parameters():
    return np.random.uniform(-1, 1, 6)

w1, w2, w3, w4, w5, b = initialize_parameters()
learning_rate = 0.01  # Reduced learning rate

# Sigmoid functions
def sigmoid(x):
    return 1.0 / (1.0 + np.exp(-x))

def sigmoid_derivative(x):
    s = sigmoid(x)
    return s * (1 - s)

# Prediction function
def predict(x1, x2, x3, x4, x5):
    return sigmoid((w1 * x1) + (w2 * x2) + (w3 * x3) + (w4 * x4) + (w5 * x5) + b)

# Training function
def train(epochs):
    global w1, w2, w3, w4, w5, b
    for epoch in range(epochs):
        total_loss = 0
        for example in training_data:
            x1, x2, x3, x4, x5, y_true = example

            # Forward pass
            y_pred = predict(x1, x2, x3, x4, x5)
            error = y_true - y_pred
            total_loss += error ** 2

            # Backpropagation
            dL_dyPred = -2 * error
            dyPred_dz = sigmoid_derivative((w1 * x1) + (w2 * x2) + (w3 * x3) + (w4 * x4) + (w5 * x5) + b)
            dz_dw1, dz_dw2, dz_dw3, dz_dw4, dz_dw5, dz_db = x1, x2, x3, x4, x5, 1

            dL_dw1 = dL_dyPred * dyPred_dz * dz_dw1
            dL_dw2 = dL_dyPred * dyPred_dz * dz_dw2
            dL_dw3 = dL_dyPred * dyPred_dz * dz_dw3
            dL_dw4 = dL_dyPred * dyPred_dz * dz_dw4
            dL_dw5 = dL_dyPred * dyPred_dz * dz_dw5
            dL_db = dL_dyPred * dyPred_dz * dz_db

            # Update weights
            w1 -= learning_rate * dL_dw1
            w2 -= learning_rate * dL_dw2
            w3 -= learning_rate * dL_dw3
            w4 -= learning_rate * dL_dw4
            w5 -= learning_rate * dL_dw5
            b -= learning_rate * dL_db

        # Print loss for every 100 epochs
        if (epoch + 1) % 100 == 0:
            print(f"Epoch {epoch + 1}, Loss: {total_loss / len(training_data)}")
        
        # Early stopping if loss is sufficiently small
        if total_loss / len(training_data) < 1e-6:
            print(f"Loss threshold met at epoch {epoch + 1}.")
            break

    return total_loss / len(training_data)

# Main function
def main():
    global w1, w2, w3, w4, w5, b
    max_attempts = 10
    loss_threshold = 1e-6
    attempt = 0

    while attempt < max_attempts:
        print(f"\nAttempt {attempt + 1}: Initializing parameters...")
        w1, w2, w3, w4, w5, b = initialize_parameters()
        final_loss = train(1000)
        
        if final_loss < loss_threshold:
            print("Training successful.")
            break
        else:
            print(f"Training failed. Final loss: {final_loss}. Retrying with new parameters...")
        
        attempt += 1

    if attempt == max_attempts:
        print("Max attempts reached. Could not achieve target loss.")

    # Testing after training
    for i, example in enumerate(training_data):
        x1, x2, x3, x4, x5, y_true = example
        y_pred = predict(x1, x2, x3, x4, x5)
        print(f"Company: {company_names[i]}, Prediction: {'Price Increase' if y_pred > 0.5 else 'Price Decrease'}, True Value: {'Price Increase' if y_true == 1 else 'Price Decrease'}")

if __name__ == "__main__":
    main()
