#include <Adafruit_NeoPixel.h>


#define PIXEL_DATA_PIN 9
#define NUM_PIXEL      26

#define ON_DURATION            1500
#define BETWEEN_LETTER_PAUSE   1000
#define PARTY_MODE_ITERATIONS  (5 * 60000) / (ON_DURATION * 2)

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXEL, PIXEL_DATA_PIN, NEO_GRB + NEO_KHZ800);

struct COLOR {
  byte r;
  byte g;
  byte b;
};

#define RED    {0x7F, 0x00, 0x00} 
#define GREEN  {0x00, 0x7F, 0x00}
#define BLUE   {0x00, 0x00, 0x7F}
#define PURPLE {0x7F, 0x00, 0x7F}
#define ORANGE {0x7F, 0x52, 0x00}
#define WHITE  {0x7F, 0x7F, 0x7F}
#define YELLOW {0x79, 0x7A, 0x05}
#define INDIGO {0x20, 0x05, 0x7A}
#define TEAL   {0x66, 0xD2, 0xC5}
#define PINK   {0xD7, 0x7B, 0xAC}

struct LIGHT {
  byte addr;
  COLOR color;
};

#define BRIGHTNESS 0xDF

// Offset is the letter (e.g. A = 0, B = 1)
// Value is the LED address (e.g. 0 is the first light, 1 is the second, etc.)
// This allows you to map the address on the light strand to the letter - note the lights wrap
// at letter H in the movie, so while H is obviously after G, numerically in the strand it is not
// This strand map is for a shirt that starts at Z rather than A so that you can wire it up to exit
// at the bottom of the shirt
LIGHT PIN_LETTER_MAP [] = {{25,  RED},    // A
                           {24,  GREEN},  // B
                           {23,  BLUE},   // C
                           {22,  YELLOW}, // D
                           {21,  RED},    // E
                           {20,  GREEN},  // F
                           {19,  BLUE},   // G
                           {18,  YELLOW}, // H
                           {9,   YELLOW}, // I
                           {10,  BLUE},   // J
                           {11,  GREEN},  // K
                           {12,  RED},    // L
                           {13,  YELLOW}, // M
                           {14,  BLUE},   // N
                           {15,  GREEN},  // O
                           {16,  RED},    // P
                           {17,  YELLOW}, // Q
                           {8,   RED},    // R
                           {7,   GREEN},  // S
                           {6,   BLUE},   // T
                           {5,   YELLOW}, // U
                           {4,   RED},    // V
                           {3,   GREEN},  // W
                           {2,   BLUE},   // X
                           {1,   YELLOW}, // Y
                           {0,   RED}     // Z
  };

char* PHRASES[]={"Right Here", "Run", "Happy Halloween"};
#define NUM_PHRASES  (sizeof(PHRASES) / sizeof(char*))
#define SIZE_OF_MAP NUM_PIXEL
long phraseCounter = 0;

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  Serial.begin(9600);
    
  Serial.println("Starting - There are " + String(NUM_PHRASES) + " phrases");

  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));
}

void loop() {

  // Just go in order
  long phraseOffset = phraseCounter++;
  
  // Pick a phrase at random
  //long phraseOffset = random(0, NUM_PHRASES);

  // Alternatively pick a value from a potentiometer?
  //long phraseOffset = analogRead(1);

  char *phrase = PHRASES[phraseOffset];
  Serial.println("Starting phrase [" + String(phrase) + "]");
  
  while(*phrase != 0) {
    int letter = (int)*phrase;
    int letterIndex = (letter >= 65 && letter <= 90) ? (letter - 65) : ((letter >= 97 && letter <= 122) ? letter - 97 : -1);

    Serial.println("Light up letter " + String(letter) + " (" + String(letter) + ") at index " + String(letterIndex));

    if (letterIndex >= 0) {
      LIGHT light = PIN_LETTER_MAP[letterIndex];
      //Serial.println("Setting LED " + String(light.addr) + " to R/G/B: " + String(light.color.r & BRIGHTNESS) + "/" + String(light.color.g & BRIGHTNESS) + "/" + String(light.color.b & BRIGHTNESS));
      strip.setPixelColor(light.addr, (light.color.r & BRIGHTNESS), (light.color.g & BRIGHTNESS), (light.color.b & BRIGHTNESS));
      strip.show();
      delay(ON_DURATION);
      strip.setPixelColor(light.addr, 0);
      strip.show(); 
    }

    delay(BETWEEN_LETTER_PAUSE);
    phrase++;
  }


  if (phraseCounter == NUM_PHRASES) {
    phraseCounter = 0;
    enablePartyMode();
  } else {
    flashAllLights();
  }
}

void flashAllLights() {
  for(int i = 0; i < SIZE_OF_MAP; i++) {
    LIGHT light = PIN_LETTER_MAP[i];
    strip.setPixelColor(light.addr, (light.color.r & BRIGHTNESS), (light.color.g & BRIGHTNESS), (light.color.b & BRIGHTNESS));
  }
  
  strip.show();
  delay(ON_DURATION);

  for(int i = 0; i < SIZE_OF_MAP; i++) {
    strip.setPixelColor(i, 0);
  }
  strip.show();
  delay(BETWEEN_LETTER_PAUSE);
}

void enablePartyMode() {
  for(int t = 0; t < PARTY_MODE_ITERATIONS; t++) {
    // How many lights to turn on
    int numOfLights = (int)random(0, NUM_PIXEL);
  
    for(int i = 0; i < numOfLights; i++) {
      int lightToEnable = (int)random(0, NUM_PIXEL);
      LIGHT light = PIN_LETTER_MAP[lightToEnable];
      strip.setPixelColor(light.addr, (light.color.r & BRIGHTNESS), (light.color.g & BRIGHTNESS), (light.color.b & BRIGHTNESS));
    }
    
    strip.show();
    delay(ON_DURATION);
  
    for(int i = 0; i < SIZE_OF_MAP; i++) {
      strip.setPixelColor(i, 0);
    }
    strip.show();
    delay(BETWEEN_LETTER_PAUSE);
  }
}

void turnOnAllLights() {
  for(int i = 0; i < SIZE_OF_MAP; i++) {
    LIGHT light = PIN_LETTER_MAP[i];
    strip.setPixelColor(light.addr, (light.color.r & BRIGHTNESS), (light.color.g & BRIGHTNESS), (light.color.b & BRIGHTNESS));
  }
  
  strip.show();
}

