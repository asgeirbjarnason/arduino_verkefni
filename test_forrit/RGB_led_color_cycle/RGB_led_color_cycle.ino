const int redpin = 11;
const int greenpin = 10;
const int bluepin = 9;

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

void color(byte r, byte g, byte b); // Light up the RGB diode with the color values given.

// Utility function to make the code shorter. Allows us to pass in an array of color values instead
// of single values for each chanel.
void color(byte* c);

void setup() {
  
}

void loop() {
  for (int i = 0; i < 10; i++) { // Cycle through all the colors from the assignment sheet.
    color(colors[i]);
    delay(1000);
  }
}

void color(byte r, byte g, byte b) {
  analogWrite(redpin, r);
  analogWrite(greenpin, g);
  analogWrite(bluepin, b);
}

void color(byte* c) {
  analogWrite(redpin, c[0]);
  analogWrite(greenpin, c[1]);
  analogWrite(bluepin, c[2]);
}
