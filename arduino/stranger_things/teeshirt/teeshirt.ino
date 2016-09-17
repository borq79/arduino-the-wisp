#include <Adafruit_NeoPixel.h>


#define PIXEL_DATA_PIN 1
#define NUM_PIXEL      50

#define ON_DURATION          2000
#define BETWEEN_LETTER_PAUSE 1500

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

#define BRIGHTNESS 0x1F

// Offset is the letter (e.g. A = 0, B = 1)
// Value is the LED address (e.g. 0 is the first light, 1 is the second, etc.)
// This allows you to map the address on the light strand to the letter - note the lights wrap
// at letter H in the movie, so while H is 
LIGHT PIN_LETTER_MAP[] = { {0,  WHITE},    // A
                           {1,  BLUE},     // B
                           {2,  PURPLE},   // C
                           {3,  TEAL},     // D
                           {4,  INDIGO},   // E
                           {5,  YELLOW},   // F
                           {6,  PINK},     // G
                           {7,  TEAL},     // H
                           {16, TEAL},     // I
                           {15, PURPLE},   // J
                           {14, TEAL},     // K
                           {13, WHITE},    // L
                           {12, YELLOW},   // M
                           {11, PINK},     // N
                           {10, PURPLE},   // O
                           {9,  WHITE},    // P
                           {8,  PINK},     // Q
                           {17, TEAL},     // R
                           {18, WHITE},    // S
                           {19, YELLOW},   // T
                           {20, BLUE},     // U
                           {21, PINK},     // V
                           {22, BLUE},     // W
                           {23, YELLOW},   // X
                           {24, PINK},     // Y
                           {25, PURPLE}    // Z
  };

char* PHRASES[]={"Right Here", "Run", "Happy Halloween"};
#define NUM_PHRASES  (sizeof(PHRASES) / sizeof(char*))
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
  long phraseOffset = (phraseCounter >= NUM_PHRASES) ? 0 : phraseCounter++;
  
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
}
