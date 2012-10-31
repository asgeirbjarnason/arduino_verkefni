// Code to draw the digits 0-9 on a 7 segment led display.
//
// Presupposes that the led array is connected in the following way:
//
//    Pin on LED       Digital Pin on Arduino
//     0                0
//     1                1
//     2               nothing (see below)
//     3                2
//     4                3
//     5                4
//     6                5
//     7               nothing (see below)
//     8                6
//     9                7
//
//
//    pins 2 and 7 are connected to a few hundred ohm resisitors (we used 330 ohm) and into pin 8


const int digits[][8] = {
  {  LOW,  LOW,  LOW, HIGH, HIGH,  LOW,  LOW,  LOW }, // 0
  { HIGH, HIGH,  LOW, HIGH, HIGH, HIGH, HIGH,  LOW }, // 1
  {  LOW,  LOW, HIGH, HIGH,  LOW, HIGH,  LOW,  LOW }, // 2
  { HIGH,  LOW,  LOW, HIGH,  LOW, HIGH,  LOW,  LOW }, // 3
  { HIGH, HIGH,  LOW, HIGH,  LOW,  LOW, HIGH,  LOW }, // 4
  { HIGH,  LOW,  LOW, HIGH,  LOW,  LOW,  LOW, HIGH }, // 5
  {  LOW,  LOW,  LOW, HIGH,  LOW,  LOW,  LOW, HIGH }, // 6
  { HIGH, HIGH,  LOW, HIGH, HIGH, HIGH,  LOW,  LOW }, // 7
  {  LOW,  LOW,  LOW, HIGH,  LOW,  LOW,  LOW,  LOW }, // 8
  { HIGH, HIGH,  LOW, HIGH,  LOW,  LOW,  LOW,  LOW }  // 9
};

int currentDigit = 0;

void drawDigit(int digit) {
  for (int i = 0; i < 8; i++) { digitalWrite(i, digits[digit][i]); }
}

void setup_digitDisplay() {
  for (int i = 0; i < 9; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
}

void setup() {
  setup_digitDisplay();
}

void loop() {
  drawDigit(currentDigit);
  delay(300);
  currentDigit = (currentDigit+1) % 10;
}
