// here i will write what i understood by reading code , i am trying not to rely on a tutorial but study the code and understand it
// first off i am starting with blinks/two_sec_blinks.ino
/*=====================*/
void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // Set the built-in LED as an output
}
/*=====================*/
// void setup is run once when the arduino or microcontroller is powered on
// LED_BUILTIN is a constant that refers to the pin number connected to the built-in LED
//OUTPUT configures the pin to send signals
//So, this code simply prepares the pin connected to the built-in LED to be used as an output
/* our LEDBUILT IN is at pin 16 usually

pinMode(13, OUTPUT);  // Set pin 13 as an output pin
pinMode(7, INPUT);    // Set pin 7 as an input pin
pinMode(8, INPUT_PULLUP); // Set pin 8 as an input with an internal pull-up resistor

you see pinMode sets the pin outpout*/

/*==============================*/
void loop() {
  digitalWrite(LED_BUILTIN, LOW); // Turn the LED on (LOW is ON for ESP8266)
  delay(2000);                   // Wait for 2 seconds
  digitalWrite(LED_BUILTIN, HIGH); // Turn the LED off (HIGH is OFF for ESP8266)
  delay(2000);                    // Wait for 2 seconds
}
/*==============================*/
/*
now this one above is pretty obvious with the comments i dont think i need to explain anything here eeven to literal stupids
*/
/*
digitalWrite() is a function in Arduino used to set the state of a digital pin, either HIGH (on) or LOW (off)
*/

/*=====================================***************************************===============================================*/


/* === that concludes my study for the two second blink code ===*/
// random blink.ino study now
void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // Set the built-in LED as an output
  randomSeed(analogRead(A0));  // Initialize random seed (use A0 to introduce variability)
}
/*
randomSeed(analogRead(A0)); uses the value read from pin A0 (usually random noise from an unconnected pin) to initialize the random number generator. This ensures that the random numbers generated in the program are different each time it runs, making the results more unpredictable. Without this, the random() function would generate the same sequence of numbers every time the program starts.
*/

/*
If something is connected to A0, the value read will depend on the connected component (e.g., a sensor or voltage). This could make randomSeed(analogRead(A0)) less random because the value will become predictable, unlike when A0 is left unconnected and picks up noise.
*/

void loop() {
  int onTime = random(100, 2000); // Generate a random ON time between 100ms and 2000ms
  int offTime = random(100, 2000); // Generate a random OFF time between 100ms and 2000ms

  digitalWrite(LED_BUILTIN, LOW); // Turn the LED on (LOW is ON for ESP8266)
  delay(onTime);                 // Wait for the random ON time
  digitalWrite(LED_BUILTIN, HIGH); // Turn the LED off (HIGH is OFF for ESP8266)
  delay(offTime);                // Wait for the random OFF time
}

/*
int onTime = random(100, 2000);
Generates a random value between 100 and 2000 (milliseconds) and stores it in onTime.

int offTime = random(100, 2000);
Generates a random value between 100 and 2000 (milliseconds) and stores it in offTime.

digitalWrite(LED_BUILTIN, LOW);
Turns the built-in LED on (for ESP8266, LOW means the LED is on).

delay(onTime);
Pauses the program for the duration of onTime (random "on" time).

digitalWrite(LED_BUILTIN, HIGH);
Turns the built-in LED off (for ESP8266, HIGH means the LED is off).

delay(offTime);
Pauses the program for the duration of offTime (random "off" time).
*/

/*
random() is a built-in function in Arduino. It generates pseudo-random numbers.

delay() is also a built-in function in Arduino. It pauses the program for a specified amount of time in milliseconds.
*/

/* now i will write one more LED blink program by myself */

void setup(){
    pinMode(LED_BUILTIN,OUTPUT);
    randomSeed(analogRead(A0));
}

void loop(){
    int onTime = random(1,20000);
    int offTime = random(1,4000);

    digitalWrite(LED_BUILTIN,LOW);
    delay(onTime);

    digitalWrite(LED_BUILTIN,HIGH);
    delay(offTime);
    
}

/*
okay i admit i did nothing different than the random blink but i did this by myself and that says a lot
*/


/* i wish there is a brightness adjusted for LED , i think there is but that is for today its already 1 am and i am sleep deprived enough from the last day*/