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


// ------------------------------------
// Data for the morse code.
const int morse_pin = 13;

const int DOT_TIME = 100;
const int DASH_TIME = DOT_TIME * 3;
const int INTRALETTER_WAITTIME = DOT_TIME;
const int INTERLETTER_WAITTIME = DOT_TIME * 2; // We will already have waited one DOT_TIME, because of the INTRALETTER_WAITTIME
const int INTERWORD_WAITTIME = DOT_TIME * 4; // See above for why this is not DOT_TIME * 7

char morse_text[] = "We think we should get 12 for this assignment ";
char* morse_curr_pos = morse_text;

int morse_current_token = 0;
unsigned long morse_last_token_start;

boolean (*tokens[5])(unsigned long, unsigned long);
int token_count = 0;
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


// ------------------------------------
// Functions for the morse code.
void setup_morse(unsigned long now);

boolean dot(unsigned long start, unsigned long current);
boolean dash(unsigned long start, unsigned long current);
boolean interletter(unsigned long start, unsigned long current);
boolean interword(unsigned long start, unsigned long current);

// --autogen--
void morse_a() { token_count = 0; tokens[token_count++] = &dot; tokens[token_count++] = &dash; tokens[token_count++] = &interletter;};
void morse_b() { token_count = 0; tokens[token_count++] = &dash; tokens[token_count++] = &dot; tokens[token_count++] = &dot; tokens[token_count++] = &dot; tokens[token_count++] = &interletter;};
void morse_c() { token_count = 0; tokens[token_count++] = &dash; tokens[token_count++] = &dot; tokens[token_count++] = &dash; tokens[token_count++] = &dot; tokens[token_count++] = &interletter;};
void morse_d() { token_count = 0; tokens[token_count++] = &dash; tokens[token_count++] = &dot; tokens[token_count++] = &dot; tokens[token_count++] = &interletter;};
void morse_e() { token_count = 0; tokens[token_count++] = &dot; tokens[token_count++] = &interletter;};
void morse_f() { token_count = 0; tokens[token_count++] = &dot; tokens[token_count++] = &dot; tokens[token_count++] = &dash; tokens[token_count++] = &dot; tokens[token_count++] = &interletter;};
void morse_g() { token_count = 0; tokens[token_count++] = &dash; tokens[token_count++] = &dash; tokens[token_count++] = &dot; tokens[token_count++] = &interletter;};
void morse_h() { token_count = 0; tokens[token_count++] = &dot; tokens[token_count++] = &dot; tokens[token_count++] = &dot; tokens[token_count++] = &dot; tokens[token_count++] = &interletter;};
void morse_i() { token_count = 0; tokens[token_count++] = &dot; tokens[token_count++] = &dot; tokens[token_count++] = &interletter;};
void morse_j() { token_count = 0; tokens[token_count++] = &dot; tokens[token_count++] = &dash; tokens[token_count++] = &dash; tokens[token_count++] = &dash; tokens[token_count++] = &interletter;};
void morse_k() { token_count = 0; tokens[token_count++] = &dash; tokens[token_count++] = &dot; tokens[token_count++] = &dash; tokens[token_count++] = &interletter;};
void morse_l() { token_count = 0; tokens[token_count++] = &dot; tokens[token_count++] = &dash; tokens[token_count++] = &dot; tokens[token_count++] = &dot; tokens[token_count++] = &interletter;};
void morse_m() { token_count = 0; tokens[token_count++] = &dash; tokens[token_count++] = &dash; tokens[token_count++] = &interletter;};
void morse_n() { token_count = 0; tokens[token_count++] = &dash; tokens[token_count++] = &dot; tokens[token_count++] = &interletter;};
void morse_o() { token_count = 0; tokens[token_count++] = &dash; tokens[token_count++] = &dash; tokens[token_count++] = &dash; tokens[token_count++] = &interletter;};
void morse_p() { token_count = 0; tokens[token_count++] = &dot; tokens[token_count++] = &dash; tokens[token_count++] = &dash; tokens[token_count++] = &dot; tokens[token_count++] = &interletter;};
void morse_q() { token_count = 0; tokens[token_count++] = &dash; tokens[token_count++] = &dash; tokens[token_count++] = &dot; tokens[token_count++] = &dash; tokens[token_count++] = &interletter;};
void morse_r() { token_count = 0; tokens[token_count++] = &dot; tokens[token_count++] = &dash; tokens[token_count++] = &dot; tokens[token_count++] = &interletter;};
void morse_s() { token_count = 0; tokens[token_count++] = &dot; tokens[token_count++] = &dot; tokens[token_count++] = &dot; tokens[token_count++] = &interletter;};
void morse_t() { token_count = 0; tokens[token_count++] = &dash; tokens[token_count++] = &interletter;};
void morse_u() { token_count = 0; tokens[token_count++] = &dot; tokens[token_count++] = &dot; tokens[token_count++] = &dash; tokens[token_count++] = &interletter;};
void morse_v() { token_count = 0; tokens[token_count++] = &dot; tokens[token_count++] = &dot; tokens[token_count++] = &dot; tokens[token_count++] = &dash; tokens[token_count++] = &interletter;};
void morse_w() { token_count = 0; tokens[token_count++] = &dot; tokens[token_count++] = &dash; tokens[token_count++] = &dash; tokens[token_count++] = &interletter;};
void morse_x() { token_count = 0; tokens[token_count++] = &dash; tokens[token_count++] = &dot; tokens[token_count++] = &dot; tokens[token_count++] = &dash; tokens[token_count++] = &interletter;};
void morse_y() { token_count = 0; tokens[token_count++] = &dash; tokens[token_count++] = &dot; tokens[token_count++] = &dash; tokens[token_count++] = &dash; tokens[token_count++] = &interletter;};
void morse_z() { token_count = 0; tokens[token_count++] = &dash; tokens[token_count++] = &dash; tokens[token_count++] = &dot; tokens[token_count++] = &dot; tokens[token_count++] = &interletter;};


void (*alphabet[])() = { &morse_a, &morse_b, &morse_c, &morse_d, &morse_e, &morse_f, &morse_g, &morse_h, &morse_i, &morse_j, &morse_k, &morse_l, &morse_m, &morse_n, &morse_o, &morse_p, &morse_q, &morse_r, &morse_s, &morse_t, &morse_u, &morse_v, &morse_w, &morse_x, &morse_y, &morse_z };
// --autogen--

void morse_interword();

boolean char2index(char& c);
void morse_state_step();
void morse_step(unsigned long now);
// ------------------------------------



// -------------------------------------------------------------------------- //
//                           Function definitions                             //
// -------------------------------------------------------------------------- //

// ------------------------------------
// Top level functions.
void setup() {
 unsigned long now = millis();
 setup_morse(now);
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
  
  morse_step(now);
  
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


// ------------------------------------
// Functions for the morse code.
void setup_morse(unsigned long now) {
  pinMode(morse_pin, OUTPUT);
  morse_last_token_start = now;
}

boolean dot(unsigned long start, unsigned long current) {
  if (current - start < DOT_TIME) {
    digitalWrite(morse_pin, HIGH); // I really shouldn't write again and again into the ping. Should make it sticky instead (but that's a problem for another time).
    return false;
  }
  if (current - start < DOT_TIME + INTRALETTER_WAITTIME) {
    digitalWrite(morse_pin, LOW);
    return false;
  }
  return true;
}

boolean dash(unsigned long start, unsigned long current) {
  if (current - start < DASH_TIME) {
    digitalWrite(morse_pin, HIGH); // I really shouldn't write again and again into the ping. Should make it sticky instead (but that's a problem for another time).
    return false;
  }
  if (current - start < DASH_TIME + INTRALETTER_WAITTIME) {
    digitalWrite(morse_pin, LOW);
    return false;
  }
  return true;
}

boolean interletter(unsigned long start, unsigned long current) {
  if (current - start < INTERLETTER_WAITTIME) {
    digitalWrite(morse_pin, LOW);
    return false;
  }
  return true;
}

boolean interword(unsigned long start, unsigned long current) {
  if (current - start < INTERWORD_WAITTIME) {
    digitalWrite(morse_pin, LOW);
    return false;
  }
  return true;
}

void morse_interword() { token_count = 0; tokens[token_count++] = &interword; };

boolean char2index(char& c) {
  if (c >= 'a' && c <= 'z') { c -= 'a' - 'A'; } // If the letter is in the lowercase range, we will translate it to lowercase.
  if (!(c >= 'A' && c <= 'Z')) { return false; } // If it isn't in lowercase now, then it isn't a letter.
  c -= 'A'; // A is the zeroth index in the func array.
  return true;
}

void morse_state_step() {
  if (*morse_curr_pos != 0) {
    char c = *morse_curr_pos;
    if (char2index(c)) {
      ((*alphabet[c]))();
    }
    else {
      morse_interword();
    }
    ++morse_curr_pos;
  }
  else {
    morse_curr_pos = morse_text;
    morse_interword();
  }
}

void morse_step(unsigned long now) {
  if (morse_current_token < token_count) {
    if ((*tokens[morse_current_token])(morse_last_token_start, now)) {
      morse_last_token_start = now;
      ++morse_current_token;
    }
  }
  else {
    morse_state_step();
    morse_current_token = 0;
  }
}
// ------------------------------------
