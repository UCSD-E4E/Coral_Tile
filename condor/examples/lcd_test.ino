// This was written in Arduino IDE to test out the LCD functionality. It works but it's very non-optimized, which could cause issues with flash usage.

#include <Wire.h>

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int j = 0; j < 999; j++){
    WriteLCD(((float) j)/10);
    delay(100);
  }
}

void WriteLCD(float x){

  
  // 0b--------, 0b----EDCP, 0b--------, 0b----GBAF, 0b--------
  byte one[10][5] = {
    {0b00000000, 0b00001110, 0b00000000, 0b00000111, 0b00000000}, // 0
    {0b00000000, 0b00000010, 0b00000000, 0b00000100, 0b00000000}, // 1
    {0b00000000, 0b00001100, 0b00000000, 0b00001110, 0b00000000}, // 2
    {0b00000000, 0b00000110, 0b00000000, 0b00001110, 0b00000000}, // 3 
    {0b00000000, 0b00000010, 0b00000000, 0b00001101, 0b00000000}, // 4
    {0b00000000, 0b00000110, 0b00000000, 0b00001011, 0b00000000}, // 5
    {0b00000000, 0b00001110, 0b00000000, 0b00001011, 0b00000000}, // 6 
    {0b00000000, 0b00000010, 0b00000000, 0b00000110, 0b00000000}, // 7
    {0b00000000, 0b00001110, 0b00000000, 0b00001111, 0b00000000}, // 8 
    {0b00000000, 0b00000110, 0b00000000, 0b00001111, 0b00000000}  // 9 
  };

  // 0bEDCP----, 0b--------, 0b--------, 0bGFAB----, 0b--------
  byte two[10][5] = {
    {0b11110000, 0b00000000, 0b00000000, 0b01110000, 0b00000000},
    {0b00110000, 0b00000000, 0b00000000, 0b00010000, 0b00000000},
    {0b11010000, 0b00000000, 0b00000000, 0b10110000, 0b00000000},
    {0b01110000, 0b00000000, 0b00000000, 0b10110000, 0b00000000},
    {0b00110000, 0b00000000, 0b00000000, 0b11010000, 0b00000000},
    {0b01110000, 0b00000000, 0b00000000, 0b11100000, 0b00000000},
    {0b11110000, 0b00000000, 0b00000000, 0b11100000, 0b00000000},
    {0b00110000, 0b00000000, 0b00000000, 0b00110000, 0b00000000},
    {0b11110000, 0b00000000, 0b00000000, 0b11110000, 0b00000000},
    {0b01110000, 0b00000000, 0b00000000, 0b11110000, 0b00000000}
  };

  // 0b----EDCP, 0b--------, 0b--------, 0b--------, 0b----GBAF
  byte three[10][5] = {
    {0b00001110, 0b00000000, 0b00000000, 0b00000000, 0b00000111},
    {0b00000010, 0b00000000, 0b00000000, 0b00000000, 0b00000100},
    {0b00001100, 0b00000000, 0b00000000, 0b00000000, 0b00001110},
    {0b00000110, 0b00000000, 0b00000000, 0b00000000, 0b00001110},
    {0b00000010, 0b00000000, 0b00000000, 0b00000000, 0b00001101},
    {0b00000110, 0b00000000, 0b00000000, 0b00000000, 0b00001011},
    {0b00001110, 0b00000000, 0b00000000, 0b00000000, 0b00001011},
    {0b00000010, 0b00000000, 0b00000000, 0b00000000, 0b00000110},
    {0b00001110, 0b00000000, 0b00000000, 0b00000000, 0b00001111},
    {0b00000110, 0b00000000, 0b00000000, 0b00000000, 0b00001111}
  };


  byte num = byte(0x00);

  int numOne = ((int) (x / 10)) % 10;
  int numTwo = ((int) (x)) % 10;
  int numThree = ((int) (x * 10)) % 10;
  
  Wire.beginTransmission(0x38); //0b0111000(0) write address for LCD IC. Read is 0b0111000(1)
  Wire.write(byte(0x00)); // Memory addresss starting at control 0x00
  Wire.write(byte(0x00)); // addr(0x00) 0x00 is for no reset
  Wire.write(byte(0b00010000)); // addr(0x01)
  Wire.write(byte(0b00001101)); // addr(0x02)
  Wire.write(byte(0b00000000)); // addr(0x03)

  for(int i = 0; i < 5; i++){
    num = one[numOne][i] | two[numTwo][i] | three[numThree][i];
    Wire.write(num);
  }
  
  Wire.endTransmission();
  
  
}
