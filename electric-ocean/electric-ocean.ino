#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

#include <OctoWS2811.h>

#define  USE_OCTOWS2811
#include <FastLED.h>

#include <Statistic.h>

#include "coordinateSerial.h"
#define NUM_STRIPS 8
CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];
CRGB leds2[NUM_STRIPS * NUM_LEDS_PER_STRIP];
CRGB leds3[NUM_STRIPS * NUM_LEDS_PER_STRIP];

uint8_t brightness = 255;

// Mode Initiation Variables

//Color Initiation Variables
uint8_t hue, hue1, hue2;
CHSV color;
uint8_t masterBrightness = 30;

double speed;


#define teensyLEDPin 13
int led_state = 0;

elapsedMicros dt;
String message;

void setup()
{
  dt = 0;
  pinMode(teensyLEDPin, OUTPUT);

	//Set up Teensy Audio Board
  //audio_setup()

	Serial.begin(115200);
	Serial1.begin(115200); // for ESP communication


	LEDS.addLeds<OCTOWS2811>(leds, NUM_LEDS);
  digitalWrite(teensyLEDPin, HIGH); 
	FastLED.clear(true);
	delay(1000);

	// limit device power draw to 1A at 5v. 5 Watts.
	FastLED.setMaxPowerInVoltsAndMilliamps(5, 1000);
	LEDS.setBrightness(masterBrightness);


	Serial.println("Setup Complete!");
  Serial.printf("Took %lu microseconds.\n", (uint16_t)dt );
}

void loop()
{
	LEDS.setBrightness(masterBrightness);

	LEDS.show();
}
