const int redpin = 11;
const int greenpin = 10;
const int bluepin = 9;

void setup() {
  
}

void loop() {
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) {
    analogWrite(redpin, fadeValue);
    delay(30);  
  }
  for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5) { 
    analogWrite(redpin, fadeValue); 
    delay(30);
  }
  
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) {
    analogWrite(greenpin, fadeValue);
    delay(30);  
  }
  for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5) { 
    analogWrite(greenpin, fadeValue); 
    delay(30);
  }
  
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) {
    analogWrite(bluepin, fadeValue);
    delay(30);  
  }
  for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5) { 
    analogWrite(bluepin, fadeValue); 
    delay(30);
  }
}
