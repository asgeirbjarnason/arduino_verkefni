// -------------------------------------------------------------------------- //
//                               Static Data                                  //
// -------------------------------------------------------------------------- //

int current_num = 0;

// ------------------------------------
// Data for RGB LED.
const int red_pin = 11;
const int green_pin = 10;
const int blue_pin = 9;

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
// ------------------------------------


// ------------------------------------
// Data for pushbutton.
const int button_pin = 12;

boolean wait_state = false;
unsigned long wait_start = 0;
const unsigned long WAIT_THRESHOLD_TIME = 200;
// ------------------------------------


// ------------------------------------
// Data for 7 segment LED.

const int segment_count = 7;
const int segment_pins[] = { 0, 1, 2, 4, 5, 6, 7 };

const int digits[][8] = {
  {  LOW,  LOW,  LOW, HIGH,  LOW,  LOW,  LOW }, // 0
  { HIGH, HIGH,  LOW, HIGH, HIGH, HIGH,  LOW }, // 1
  {  LOW,  LOW, HIGH,  LOW, HIGH,  LOW,  LOW }, // 2
  { HIGH,  LOW,  LOW,  LOW, HIGH,  LOW,  LOW }, // 3
  { HIGH, HIGH,  LOW,  LOW,  LOW, HIGH,  LOW }, // 4
  { HIGH,  LOW,  LOW,  LOW,  LOW,  LOW, HIGH }, // 5
  {  LOW,  LOW,  LOW,  LOW,  LOW,  LOW, HIGH }, // 6
  { HIGH, HIGH,  LOW, HIGH, HIGH,  LOW,  LOW }, // 7
  {  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW }, // 8
  { HIGH, HIGH,  LOW,  LOW,  LOW,  LOW,  LOW }  // 9
};
// ------------------------------------




// -------------------------------------------------------------------------- //
//                           Function declarations                            //
// -------------------------------------------------------------------------- //

// ------------------------------------
// Functions for RGB LED.
void color(byte* c);
// ------------------------------------


// ------------------------------------
// Functions. for pushbutton.
boolean button_press(unsigned long now); // To poll the button, with a guard against reading too many button clicks.
void setup_button(int pin);
// ------------------------------------

// ------------------------------------
// Functions for 7 segment LED.
void setup_digit_display();
void draw_digit(int digit);
// ------------------------------------




// -------------------------------------------------------------------------- //
//                           Function definitions                             //
// -------------------------------------------------------------------------- //

// ------------------------------------
// Top level functions.
void setup() {
 setup_button(button_pin);
 setup_digit_display();
 color(colors[current_num]);
 draw_digit(current_num);
}

void loop() {
  unsigned long now = millis();
  
  if (button_press(now)) {
    current_num = (current_num+1) % 10;
    color(colors[current_num]);
    draw_digit(current_num);
  }
  
  delay(20);
}
// ------------------------------------


// ------------------------------------
// Functions for RGB LED.
void color(byte* c) {
  analogWrite(red_pin, c[0]);
  analogWrite(green_pin, c[1]);
  analogWrite(blue_pin, c[2]);
}
// ------------------------------------


// ------------------------------------
// Functions. for pushbutton.
void setup_button(int pin) { pinMode(pin, INPUT); }

boolean button_press(unsigned long now) {
  // Turn off the guard against multiple clicks when the threshold time has been reached.
  if (wait_state && (now - wait_start >= WAIT_THRESHOLD_TIME)) {
    wait_state = false;
  }
  
  // Only do the read if not in the wait state.
  if (!wait_state && digitalRead(button_pin) == HIGH) {
    wait_state = true; // Set the wait state up for the next invocation of this function.
    wait_start = now; // Ditto for the wait start time.
    return true;
  }
  return false;
}
// ------------------------------------


// ------------------------------------
// Functions for 7 segment LED.
void draw_digit(int digit) {
  //for (int i = 0; i < 8; i++) { digitalWrite(i, digits[digit][i]); }
  for (int i = 0; i < segment_count; i++) {
    digitalWrite(segment_pins[i], digits[digit][i]);
  }
}

void setup_digit_display() {
  for (int i = 0; i < segment_count; i++) {
    pinMode(segment_pins[i], OUTPUT);
    digitalWrite(segment_pins[i], HIGH);
  }
}
// ------------------------------------

