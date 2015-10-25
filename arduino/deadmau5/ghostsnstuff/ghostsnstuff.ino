#include <Adafruit_NeoPixel.h>


#define PRIMARY_PIN 4
#define NUM_PIXEL 25

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXEL, PRIMARY_PIN, NEO_GRB + NEO_KHZ800);

enum OP_TYPE {
  DELAY = 0x00,
  LOOP = 0x01,
  LED = 0x02,
  EQIZR = 0x03,
  FADEIN = 0x04,
  FADEOUT = 0x05,
  FINISHED = 0xFF
};

struct BEAM {
  byte saddr;
  byte eaddr;
  byte r;
  byte g;
  byte b;
};

struct LOOP_PARAMS {
  byte operations;
  uint16_t count;
};

struct EQUALIZER {
  byte saddr;
  byte eaddr;
};

struct OP {
  byte type;

  union {
    BEAM beam;
    uint16_t delayInMs;
    LOOP_PARAMS loopParams;
    EQUALIZER equalizerRange;
  } params;
};


const OP operations[] PROGMEM = {
  /*{LOOP, {.loopParams = {1, 10}}},*/
  {DELAY, {.delayInMs = 109}},

  /*// Initial Beat - alternate eyes
  {LED, 0, 2, 0xFF, 0, 0},
  {DELAY, 250},
  {LED, 0, 2, 0, 0, 0},
  {DELAY, 216},
  {LED, 3, 5, 0, 0, 0xFF},
  {DELAY, 250},
  {LED, 3, 5, 0, 0, 0},
  {DELAY, 216},
  {LOOP, 8, 10},*/
  {FINISHED, 0}
};
#define END_OF_OPERATIONS ((byte *)operations) + sizeof(operations)

/*
 * const byte operations[] PROGMEM = {
  DELAY, 109,

  // Initial Beat - alternate eyes
  LED, 0, 2, 0xFF, 0, 0,
  DELAY, 250,
  LED, 0, 2, 0, 0, 0,
  DELAY, 216,
  LED, 3, 5, 0, 0, 0xFF,
  DELAY, 250,
  LED, 3, 5, 0, 0, 0,
  DELAY, 216,
  LOOP, 8, 10,
  FINISHED, 0
};
#define END_OF_OPERATIONS = (operations + sizeof(operations))

 */

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
  Serial.print("Ready ...");
}

/*enum OP_TYPE {
  DELAY = 0x00,
  LOOP = 0x01,
  LED = 0x02,
  EQIZR = 0x03,
  FADEIN = 0x04,
  FADEOUT = 0x05,
  FINISHED = 0xFF
}*/

void loop() {
  uint32_t tickDrift = millis();

  byte *mainOperationPC = (byte*)&operations[0];
  OP op;
  do {
    LOOP_PARAMS loopParams = {1, 1};
    
    byte mainOperationType = FINISHED;

    // Get the operation Type 
    memcpy_P(&mainOperationType, mainOperationPC, 1);
    Serial.print("Main Operation Type: "); Serial.println(mainOperationType);
    
    if (mainOperationType == LOOP) {
      memcpy_P(&loopParams, mainOperationPC + 1, sizeof(loopParams));
      Serial.print("Loop operations: "); Serial.println(loopParams.operations);
      Serial.print("Loop back count: "); Serial.println(loopParams.count);

      // Adjust program counter
      mainOperationPC += sizeof(OP);
    } else if (mainOperationType == FINISHED) {
      Serial.println("Shutting Down");
      delay(10000);
      exit(0);
    }

    
    byte *loopOperationsPC;
    
    for(uint16_t i = 0; i < loopParams.count; i++) {
      Serial.print("Loop Iteration: "); Serial.println(i);
      loopOperationsPC = mainOperationPC;
      byte *endOfLoopPC = loopOperationsPC + (loopParams.operations * sizeof(OP));
    
      do {
        byte operationType = FINISHED;
  
        // Get the operation Type 
        memcpy_P(&operationType, loopOperationsPC, 1);
        Serial.print("Operation Type: "); Serial.println(operationType);

        byte *operationStructOffset = loopOperationsPC + 1;
      
        switch(operationType) {
          case DELAY: {
            uint16_t delayInMs = 0;
            memcpy_P(&delayInMs, operationStructOffset, sizeof(uint16_t));
            Serial.print("Delay: "); Serial.println(delayInMs);
            
            delay(delayInMs);
            break;
          }
          case LOOP:
          case FINISHED:
          default:
            Serial.print("Invalid Loop Command: "); Serial.println(operationType);
            delay(10000);
            exit(0);
            break;
        }
    
        loopOperationsPC += sizeof(OP);
      } while (loopOperationsPC < endOfLoopPC);

      Serial.println("Done with loop code block, looping back");
    }

    mainOperationPC = loopOperationsPC;

    // Reset loop params
    loopParams.count = loopParams.operations = 1;
    
//strip.setPixelColor(j, op.r, op.g, op.b); 
    //strip.show();
  } while (mainOperationPC < END_OF_OPERATIONS);

  Serial.println("Shutting Down");
  delay(10000);
  exit(0);
}

