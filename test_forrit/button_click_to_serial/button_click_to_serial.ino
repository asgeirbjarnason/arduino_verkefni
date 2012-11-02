// A small program that reads the button (on digital pin 12) and prints the it out to serial when it's pressed. There
// is a bit of logic to prevent to many button clicks.

const int buttonPin = 12;
boolean wait_state = false;
unsigned long wait_start = 0;
const unsigned long WAIT_THRESHOLD_TIME = 500;

boolean button_press(unsigned long now); // To poll the button, with a guard against reading too many button clicks.
void setup_button();

void setup() {
  setup_button(buttonPin);
  Serial.begin(9600);  
}

void loop(){
  unsigned long now = millis();
  
  if (button_press(now)) {
    Serial.println("Button press");
  }
  
  delay(20);
}


void setup_button(int pin) { pinMode(pin, INPUT); }

boolean button_press(unsigned long now) {
  // Turn off the guard against multiple clicks when the threshold time has been reached.
  if (wait_state && (now - wait_start >= WAIT_THRESHOLD_TIME)) {
    wait_state = false;
  }
  
  // Only do the read if not in the wait state.
  if (!wait_state && digitalRead(buttonPin) == HIGH) {
    wait_state = true; // Set the wait state up for the next invocation of this function.
    wait_start = now; // Ditto for the wait start time.
    return true;
  }
  return false;
}
