#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

Adafruit_NeoPixel strip = Adafruit_NeoPixel(25, 2, NEO_GRB + NEO_KHZ800);

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
  // put your main code here, to run repeatedly:
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
      }
      strip.show();
      break;
    case 4:
      for(int i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, 255, 0, 03);
      }
      strip.show();
      break;      
  }

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

  if(digitalRead(lowBattPin) == LOW){
    strip.setBrightness(10);
    Serial.println("Low Battery");
    mode = 4;
  }else{
    strip.setBrightness(50);
    Serial.println("Battery OK");
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

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
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
