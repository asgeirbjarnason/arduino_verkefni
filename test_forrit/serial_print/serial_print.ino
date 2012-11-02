void setup() {
  pinMode(buttonpin, INPUT); 
  Serial.begin(9600);
}

void loop() {
  Serial.println("Just a test");
  delay(1000);
}
