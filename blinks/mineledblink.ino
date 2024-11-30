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