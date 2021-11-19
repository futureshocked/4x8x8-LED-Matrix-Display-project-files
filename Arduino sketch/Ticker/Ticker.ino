#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

int pinCS = 10; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
int numberOfHorizontalDisplays = 4;
int numberOfVerticalDisplays = 1;

byte button_1 = 5;
byte button_2 = 4;

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

String tape = "Arduino";
int wait = 20; // In milliseconds

int spacer = 1;
int width = 5 + spacer; // The font width is 5 pixels

int intensity = 7;

void setup() {
  pinMode(button_1, INPUT);
  pinMode(button_2, INPUT);
  matrix.setIntensity(intensity); // Use a value between 0 and 15 for brightness
}

void loop() {

  for ( int i = 0 ; i < width * tape.length() + matrix.width() - 1 - spacer; i++ ) {

    matrix.fillScreen(LOW);

    int letter = i / width;
    int x = (matrix.width() - 1) - i % width;
    int y = (matrix.height() - 8) / 2; // center the text vertically

    while ( x + width - spacer >= 0 && letter >= 0 ) {
      if ( letter < tape.length() ) {
        matrix.drawChar(x, y, tape[letter], HIGH, LOW, 1);
      }

      letter--;
      x -= width;
    }

    matrix.write(); // Send bitmap to display

    if (digitalRead(button_1) == HIGH)
    {
      Serial.println("HI");
      intensity = intensity + 1;
      if (intensity == 16)
        intensity = 15;
      matrix.setIntensity(intensity);
    }
    else
      Serial.println("LOW");

    if (digitalRead(button_2) == HIGH)
    {
      Serial.println("HI");
      intensity = intensity - 1;
      if (intensity == -1)
        intensity = 0;
      matrix.setIntensity(intensity);
    }
    else
      Serial.println("LOW");

    delay(wait);
  }
}
