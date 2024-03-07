#include <LiquidCrystal.h>

void printAlphabet();
void printToLCD(int i, int j, char &character);

struct {
  int rs = A0;
  int rw = A1;
  int enable = A2;
  int d4 = A3;
  int d5 = A5;
  int d6 = 4;
  int d7 = 5;
} pins;

LiquidCrystal lcd(pins.rs, pins.rw, pins.enable, pins.d4, pins.d5, pins.d6, pins.d7);

void setup() {
  // put your setup code here, to run once:
  lcd.begin(20,4);

  printAlphabet();
}

void loop() {
  // put your main code here, to run repeatedly:
}

void printToLCD(int i, int j, char &character) {
  lcd.clear();
  lcd.setCursor(i, j);
  lcd.print(character);
  character++;
  if (character > 90) {
    character = 65;
  }
  delay(200);
}

void printAlphabet() {
  bool goForward = true;
  char character = 65;

  while(true) {
    int rowIndex = 0;
    for (int i = 0; i < 20; i++) {
      printToLCD(i, rowIndex, character);
    }
    for (rowIndex++; rowIndex < 3; rowIndex++) {
      printToLCD(19, rowIndex, character);
    }
    for (int i = 19; i >= 0; i--) {
      printToLCD(i, rowIndex, character);
    }
    for (rowIndex--; rowIndex > 0; rowIndex--) {
      printToLCD(0, rowIndex, character);
    }
  }
}