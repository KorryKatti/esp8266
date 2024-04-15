#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Airtel_anik_0287";
const char* password = "air84418";

ESP8266WebServer server(6969); // Run server on port 6969
bool ledStatus = false; // Initially, LED is off

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // Set built-in LED pin as output
  
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); // Print the IP address

  server.on("/", HTTP_GET, handleRoot);
  server.on("/toggleLED", HTTP_GET, toggleLED);

  server.begin();
  Serial.println("HTTP server started");

  // Start the LED blink task
  randomSeed(analogRead(0)); // Seed the random number generator
}

void loop() {
  server.handleClient();

  // Blink LED at random intervals
  int interval = random(500, 5000); // Generate a random delay between 500ms and 5000ms
  digitalWrite(LED_BUILTIN, HIGH); // Turn LED on
  delay(interval); // Wait for the randomly generated interval
  digitalWrite(LED_BUILTIN, LOW); // Turn LED off
  delay(100); // Wait for 100ms to stabilize
}

void handleRoot() {
  String ledStatusString = ledStatus ? "ON" : "OFF";
  server.send(200, "text/html",
              "<html><head><title>ESP8266 LED Blink</title></head><body>"
              "<h1>Real-time LED Blink</h1>"
              "<p>LED Status: <span id=\"ledStatus\">" + ledStatusString + "</span></p>"
              "<button onclick=\"toggleLED()\">Toggle LED</button>"
              "<script>"
              "function toggleLED() {"
              "  fetch('/toggleLED')"
              "    .then(response => response.text())"
              "    .then(data => {"
              "      document.getElementById('ledStatus').innerText = data;"
              "    });"
              "}"
              "</script>"
              "</body></html>");
}

void toggleLED() {
  ledStatus = !ledStatus; // Toggle LED status
  digitalWrite(LED_BUILTIN, ledStatus ? HIGH : LOW); // Turn LED on or off
  server.send(200, "text/plain", ledStatus ? "ON" : "OFF");
}
