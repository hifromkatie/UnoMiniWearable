#include <Adafruit_NeoPixel.h>

//small or large
//#define NEOCOUNT 25
#define NEOCOUNT 41

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NEOCOUNT, 2, NEO_GRB + NEO_KHZ800);

int lowBattPin = 4;
int mode = 0;

void setup() {
  strip.begin();
  strip.setBrightness(50);
  strip.show();

  pinMode(lowBattPin, INPUT_PULLUP);

  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  
  Serial.begin(9600);
}

void loop() {

  if(digitalRead(lowBattPin) == LOW){
    strip.setBrightness(5);
    Serial.println("Low Battery");
    mode = 4;
  }else{
    strip.setBrightness(50);
    Serial.println("Battery OK");
    if (digitalRead (8) == LOW){
      mode = 1;
      Serial.println("Mode 1");
    }else if (digitalRead (9) == LOW){
      mode = 2;
      Serial.println("Mode 2");
    }else if (digitalRead (10) == LOW){
      mode = 3;
      Serial.println("Mode 3");
    }else{
      mode = 0;
      Serial.println("Mode 0");
    }
  } 
  
  switch (mode){
    case 0:
      rainbow(20);
      break;
    case 1:
      rainbowCycle(20);
      break;
    case 2:
      for(int i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, 255/2, 0, 255/2);
      }
      strip.show();
      break;
    case 3:
      for(int i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, 255, 255, 255);
        strip.setBrightness(100);
      }
      strip.show();
      break;
    case 4:
      for(int i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, 255, 0, 0);
      }
      strip.show();
      break;      
  }



  
     
}


void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
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


uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
