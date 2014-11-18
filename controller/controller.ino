/*************************************************** 
  This is a library for our I2C LED Backpacks

  Designed specifically to work with the Adafruit LED 7-Segment backpacks 
  ----> http://www.adafruit.com/products/881
  ----> http://www.adafruit.com/products/880
  ----> http://www.adafruit.com/products/879
  ----> http://www.adafruit.com/products/878

  These displays use I2C to communicate, 2 pins are required to 
  interface. There are multiple selectable I2C addresses. For backpacks
  with 2 Address Select pins: 0x70, 0x71, 0x72 or 0x73. For backpacks
  with 3 Address Select pins: 0x70 thru 0x77

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

// Enable one of these two #includes and comment out the other.
// Conditional #include doesn't work due to Arduino IDE shenanigans.
#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
//#include <TinyWireM.h> // Enable this line if using Adafruit Trinket, Gemma, etc.

#include "Adafruit_LEDBackpack.h"
// #include "Adafruit_GFX.h"

Adafruit_7segment matrix0 = Adafruit_7segment();
Adafruit_7segment matrix1 = Adafruit_7segment();
Adafruit_7segment matrix2 = Adafruit_7segment();
Adafruit_7segment matrix3 = Adafruit_7segment();


int display0 = 0;
int display1 = 0;
int display2 = 0;
int display3 = 0;

int joystickUp    = 0;
int joystickDown  = 0;
int joystickLeft  = 0;
int joystickRight = 0;

#define JOYSTICK_PIN_UP    8
#define JOYSTICK_PIN_DOWN  9
#define JOYSTICK_PIN_LEFT  10
#define JOYSTICK_PIN_RIGHT 11

int switch0 = 0;
int switch1 = 0;
int switch2 = 0;
int switch3 = 0;
int switch4 = 0;

#define SWITCH_PIN_0 3
#define SWITCH_PIN_1 4
#define SWITCH_PIN_2 5
#define SWITCH_PIN_3 6
#define SWITCH_PIN_4 7

#define MIN_BRIGHTNESS 0
#define CUR_BRIGHTNESS 4
#define MAX_BRIGHTNESS 15

void setup()
{
#ifndef __AVR_ATtiny85__
  Serial.begin(9600);
  Serial.println("7 Segment Backpack Test");
#endif

  matrix0.begin(0x70);
  setBrightness(&matrix0, CUR_BRIGHTNESS);

  matrix1.begin(0x71);
  setBrightness(&matrix1, CUR_BRIGHTNESS);

  matrix2.begin(0x72);
  setBrightness(&matrix2, CUR_BRIGHTNESS);

  matrix3.begin(0x73);
  setBrightness(&matrix3, CUR_BRIGHTNESS);

  // Set up Joystick
  pinMode(JOYSTICK_PIN_UP,    INPUT_PULLUP);
  pinMode(JOYSTICK_PIN_DOWN,  INPUT_PULLUP);
  pinMode(JOYSTICK_PIN_LEFT,  INPUT_PULLUP);
  pinMode(JOYSTICK_PIN_RIGHT, INPUT_PULLUP);

  // Set up Switches
  pinMode(SWITCH_PIN_0, INPUT_PULLUP);
  pinMode(SWITCH_PIN_1, INPUT_PULLUP);
  pinMode(SWITCH_PIN_2, INPUT_PULLUP);
  pinMode(SWITCH_PIN_3, INPUT_PULLUP);
  pinMode(SWITCH_PIN_4, INPUT_PULLUP);
}

void loop()
{
  boolean drawDots = true;

  for (int i = 0; i < 999; i++)
  {
	readJoystick();
	readSwitches();

	drawMatrix(&matrix1, encodeJoystick(), true);
    // drawMatrix(&matrix1, i + 1000, true);

    drawMatrix(&matrix0, i + 2000, true);
    drawMatrix(&matrix2, i + 4000, true);

    drawMatrix(&matrix3, encodeSwitches(), switch4);
    // drawMatrix(&matrix3, i + 3000, true);

	delay(50);
  }

  delay(500);
}

void drawMatrix(Adafruit_7segment* matrix, int number, boolean drawDots)
{
  // void writeDigitNum(uint8_t x, uint8_t num, boolean dot = false);
  // matrix.writeDigitNum(0, (counter / 1000), drawDots);

  matrix->print(number);
  matrix->drawColon(drawDots);
  matrix->writeDisplay();
}

void setBrightness(Adafruit_7segment* matrix, int brightness)
{
  matrix->setBrightness(brightness);
  matrix->writeDisplay();
}

void readJoystick()
{
  joystickUp    = digitalRead(JOYSTICK_PIN_UP);
  joystickDown  = digitalRead(JOYSTICK_PIN_DOWN);
  joystickLeft  = digitalRead(JOYSTICK_PIN_LEFT);
  joystickRight = digitalRead(JOYSTICK_PIN_RIGHT);
}

int encodeJoystick()
{
  int joystickValue = 1111;

  if (joystickUp > 0)
  {
    joystickValue += 7;
  }

  if (joystickDown > 0)
  {
    joystickValue += 70;
  }

  if (joystickLeft > 0)
  {
    joystickValue += 700;
  }

  if (joystickRight > 0)
  {
    joystickValue += 7000;
  }

  return joystickValue;
}

void readSwitches()
{
  switch0 = digitalRead(SWITCH_PIN_0);
  switch1 = digitalRead(SWITCH_PIN_1);
  switch2 = digitalRead(SWITCH_PIN_2);
  switch3 = digitalRead(SWITCH_PIN_3);
  switch4 = digitalRead(SWITCH_PIN_4);
}

int encodeSwitches()
{
  int switchValue = 1111;

  if (switch0 > 0)
  {
    switchValue += 7;
  }

  if (switch1 > 0)
  {
    switchValue += 70;
  }

  if (switch2 > 0)
  {
    switchValue += 700;
  }

  if (switch3 > 0)
  {
    switchValue += 7000;
  }

  return switchValue;
}
