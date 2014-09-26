#include <Adafruit_NeoPixel.h>
#include <Bridge.h>
#include <HttpClient.h>

// pin met de neoPixels
#define PIN 10

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, PIN, NEO_GRB + NEO_KHZ800);

long start;
long timeout = 15000;

// de te gebruiken kleuren en sequentie
String command;
int red = 160;
int green = 160;
int blue = 160;
String sequence = "default";
int sequencespeed = 30;

int ledlight = 0;

void setup() {
  strip.begin();
  // alle pixels uit
  strip.show();

  Bridge.begin();
  
  start = millis();
}

void loop() {
  if ((millis() - timeout) > start) {
    HttpClient client;
    client.get("http://www.nerdland.be/api/arduino/hartje/random");
    
    while (client.available()) {
      command = client.readStringUntil('|');
      command.trim();
      red = command.toInt();
      command = client.readStringUntil('|');
      command.trim();
      green = command.toInt();
      command = client.readStringUntil('|');
      command.trim();
      blue = command.toInt();
      command = client.readStringUntil('|');
      command.trim();
      sequence = command;
      command = client.readStringUntil('|');
      command.trim();
      sequencespeed = command.toInt();
    }
    
    start = millis();
  }
  
  if (sequence == "blink") {
    theaterChase(strip.Color(red, green, blue), sequencespeed);
  } else if (sequence == "wipe") {
    colorWipe(strip.Color(red, green, blue), sequencespeed);
  } else if (sequence == "rainbow") {
    rainbowCycle(sequencespeed);
  } else {
    breath(red, green, blue, sequencespeed);
  }
}

// dim effectje
void breath(int red, int green, int blue, uint8_t wait) {
  int orig_red = red;
  int orig_green = green;
  int orig_blue = blue;
  
  while ((red > 0) || (green > 0) || (blue > 0)) {
    red = ((red - 3) >= 0) ? (red - 3) : 0;
    green = ((green - 3) >= 0) ? (green - 3) : 0;
    blue = ((blue - 3) >= 0) ? (blue - 3) : 0;
    for (uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(red, green, blue));
      strip.show();
    }
    delay(wait);
  }
  
  while ((red < orig_red) || (green < orig_green) || (blue < orig_blue)) {
    red = (red < orig_red) ? (red + 3) : orig_red;
    green = (green < orig_green) ? (green + 3) : orig_green;
    blue = (blue < orig_blue) ? (blue + 3) : orig_blue;
    for (uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(red, green, blue));
      strip.show();
    }
    delay(wait);
  } 
}

/*
 *  Onderstaande effecten zijn de example effecten van de NeoPixel library van Adafruit
 */
 
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  // alles een voor een aanzetten
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
  // alles een voor een uitzetten
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, 0);
      strip.show();
      delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
     
      delay(wait);
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

