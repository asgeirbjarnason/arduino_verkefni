const int redpin = 11;
const int greenpin = 10;
const int bluepin = 9;

const int buttonPin = 12;

boolean wait_state = false;
unsigned long wait_start = 0;
const unsigned long WAIT_THRESHOLD_TIME = 500;

int current_num = 0;

// The color combinations the assignment sheet told us were required, indexable to the right number.
byte colors[][3] = {
  {   0,   0,   0 }, // 0 --> light off
  { 255,   0,   0 }, // 1 --> red
  {   0, 255,   0 }, // 2 --> green
  { 255, 255,   0 }, // 3 --> red & green
  {   0,   0, 255 }, // 4 --> blue
  { 255,   0, 255 }, // 5 --> red & blue
  {   0, 255, 255 }, // 6 --> blue & green
  { 255, 255, 255 }, // 7 --> white (red, green & blue);
  {   0,   0,   0 }, // 8 --> light off
  {   0,   0,   0 }  // 9 --> light off
};

void color(byte* c);

boolean button_press(unsigned long now); // To poll the button, with a guard against reading too many button clicks.
void setup_button();

void setup() {
 setup_button(buttonPin);
 color(colors[0]);
}

void loop() {
  unsigned long now = millis();
  
  if (button_press(now)) {
    current_num = (current_num+1) % 10;
    color(colors[current_num]);
  }
  
  delay(20);
  
  /*for (int i = 0; i < 10; i++) { // Cycle through all the colors from the assignment sheet.
    color(colors[i]);
    delay(1000);
  }*/
}

void color(byte* c) {
  analogWrite(redpin, c[0]);
  analogWrite(greenpin, c[1]);
  analogWrite(bluepin, c[2]);
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
