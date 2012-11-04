const int LIGHT_THRESHOLD = 500;
const int photocell_pin = A0;
int photocell_reading;
const int green_pin = 10;
const int red_pin = 11;
const float twopi = 6.283185307f;
const float threehalfspi = 4.71238898;
const float cycle_length = 5.0f;
unsigned long start_time;

// Don't know the state of enums in arduino. The compiler doesn't complain when I make an enum, but when
// I try to use it the compiler starts to complain.
const int FELL_ASLEEP = 1;
const int ASLEEP = 2;
const int WOKE_UP = 4;
const int AWAKE = 8;

int last_sleep_state = AWAKE;

void setup() {
  Serial.begin(9600);
  
  pinMode(A0, INPUT);
  pinMode(10, OUTPUT);
  pinMode(11, INPUT);
  
  start_time = millis();
}

void loop() {
  photocell_reading = analogRead(photocell_pin);
  unsigned long now = millis();
  
  /*if (photocell_reading >= LIGHT_THRESHOLD) {
    pause_state(now, start_time);
  }
  else {
    run_state(now, start_time);
  }*/
  switch (sleep_status()) {
    case FELL_ASLEEP:
      Serial.println("Fell asleep.");
      start_time = now;
      // Deliberate fall through to next case.
    case ASLEEP:
      pause_state(now, start_time);
      break;
    case WOKE_UP:
      Serial.println("Woke up.");
      start_time = now;
      // Deliberate fall through to next case.
    case AWAKE:
      run_state(now, start_time);
      break;
  }
}

int sleep_status() {
  if (analogRead(photocell_pin) >= LIGHT_THRESHOLD) {
    if (last_sleep_state == FELL_ASLEEP || last_sleep_state == ASLEEP) {
      return last_sleep_state = ASLEEP;
    }
    return last_sleep_state = FELL_ASLEEP;
  }
  else if (last_sleep_state == WOKE_UP || last_sleep_state == AWAKE) {
    return last_sleep_state = AWAKE;
  }
  return last_sleep_state = WOKE_UP;
}

void pause_state(unsigned long now, unsigned long start_time) {
  byte intense = intensity(now, start_time);
  
  analogWrite(green_pin, 0);
  analogWrite(red_pin, intense);
}

void run_state(unsigned long now, unsigned long start_time) {
  byte intense = intensity(now, start_time);
  
  analogWrite(red_pin, 0);
  analogWrite(green_pin, intense);
}

float cycle_position(unsigned long now, unsigned long start_time) {
  float offset = float(now - start_time) / 1000;
  return offset / cycle_length * twopi + threehalfspi;
}

byte intensity(unsigned long now, unsigned long start_time) {
  float cycle_pos = cycle_position(now, start_time);
  float shifted_sin = float(sin(cycle_pos)) + 1;
  return byte(shifted_sin * 128.0f - 0.99f); // -0.99f instead of -1.0f to avoid negative overflow.
}
