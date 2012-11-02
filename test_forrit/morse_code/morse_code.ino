// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

const int DOT_TIME = 100;
const int DASH_TIME = DOT_TIME * 3;
const int INTRALETTER_WAITTIME = DOT_TIME;
const int INTERLETTER_WAITTIME = DOT_TIME * 2; // We will already have waited one DOT_TIME, because of the INTRALETTER_WAITTIME
const int INTERWORD_WAITTIME = DOT_TIME * 4; // See above for why this is not DOT_TIME * 7

char morse_text[] = "sos ";
char* morse_curr_pos = morse_text;

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
}

void off(int time) {
  digitalWrite(led, LOW);
  delay(time);
}

void cycle(int ontime, int offtime) {
  digitalWrite(led, HIGH);
  delay(ontime);
  digitalWrite(led, LOW);
  delay(offtime);
}

boolean dot(unsigned long start, unsigned long current) {
  if (current - start < DOT_TIME) {
    digitalWrite(led, HIGH); // I really shouldn't write again and again into the ping. Should make it sticky instead (but that's a problem for another time).
    return false;
  }
  if (current - start < DOT_TIME + INTRALETTER_WAITTIME) {
    digitalWrite(led, LOW);
    return false;
  }
  return true;
}

boolean dash(unsigned long start, unsigned long current) {
  if (current - start < DASH_TIME) {
    digitalWrite(led, HIGH); // I really shouldn't write again and again into the ping. Should make it sticky instead (but that's a problem for another time).
    return false;
  }
  if (current - start < DASH_TIME + INTRALETTER_WAITTIME) {
    digitalWrite(led, LOW);
    return false;
  }
  return true;
}

boolean interletter(unsigned long start, unsigned long current) {
  if (current - start < INTERLETTER_WAITTIME) {
    digitalWrite(led, LOW);
    return false;
  }
  return true;
}

boolean interword(unsigned long start, unsigned long current) {
  if (current - start < INTERWORD_WAITTIME) {
    digitalWrite(led, LOW);
    return false;
  }
  return true;
}

boolean (*tokens[5])(unsigned long, unsigned long);
int token_count = 0;

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

void morse_step() {
  static unsigned long last_start = 0;
  static int current_token = 0;
  
  if (!last_start) { last_start = millis(); }
  
  unsigned long now = millis();
  
  if (current_token < token_count) {
    if ((*tokens[current_token])(last_start, now)) {
      last_start = millis();
      ++current_token;
    }
  }
  else {
    morse_state_step();
    current_token = 0;
  }
}

// the loop routine runs over and over again forever:
void loop() {
  delay(30);
  morse_step();
}


