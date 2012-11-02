
//boolean clicked = false;
const int buttonpin = 12;

int buttonstate = 0;

void setup() {
  pinMode(buttonpin, INPUT); 
}

void loop() {
  buttonstate = digitalRead(buttonpin);
  
  if (buttonstate == HIGH) {
    Serial.println("Button pressed");
  }
}

