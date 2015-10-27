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
  EQUALIZER = 0x03,
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

struct FADE_PARAMS {
  uint16_t fadeTime;
  uint8_t brightness;
  BEAM beam;
};

struct LOOP_PARAMS {
  byte operations;
  uint16_t count;
};

struct EQUALIZER_PARAMS {
  byte saddr;
  byte eaddr;
};

struct OP {
  byte type;

  union {
    BEAM beam;
    uint16_t delayInMs;
    LOOP_PARAMS loopParams;
    EQUALIZER_PARAMS equalizerRange;
    FADE_PARAMS fadeParams;
  } params;
};


#define RIGHT_EAR_B1_SADDR 0
#define RIGHT_EAR_B1_EADDR 6
#define RIGHT_EAR_B2_SADDR 7
#define RIGHT_EAR_B2_EADDR 15
#define RIGHT_EAR_B3_SADDR 16
#define RIGHT_EAR_B3_EADDR 21
#define RIGHT_EAR_B4_SADDR 22
#define RIGHT_EAR_B4_EADDR 30
#define RIGHT_EAR_B5_SADDR 31
#define RIGHT_EAR_B5_EADDR 37

#define RIGHT_CHEEK_SADDR 38
#define RIGHT_CHEEK_EADDR 43

#define RIGHT_EYE_ADDR   44

#define FACE_B1_SADDR 45
#define FACE_B1_EADDR 51
#define FACE_B2_SADDR 52
#define FACE_B2_EADDR 58
#define FACE_B3_SADDR 59
#define FACE_B3_EADDR 65

#define LEFT_CHEEK_SADDR 66
#define LEFT_CHEEK_EADDR 71

#define LEFT_EYE_ADDR    72

#define LEFT_EAR_B1_SADDR 73
#define LEFT_EAR_B1_EADDR 79
#define LEFT_EAR_B2_SADDR 80
#define LEFT_EAR_B2_EADDR 88
#define LEFT_EAR_B3_SADDR 89
#define LEFT_EAR_B3_EADDR 94
#define LEFT_EAR_B4_SADDR 95
#define LEFT_EAR_B4_EADDR 103
#define LEFT_EAR_B5_SADDR 104
#define LEFT_EAR_B5_EADDR 110

#define MOUTH_UPPER_SADDR 111
#define MOUTH_UPPER_EADDR 129

#define MOUTH_LOWER_SADDR 130
#define MOUTH_LOWER_EADDR 147

#define MOUTH_SADDR MOUTH_UPPER_SADDR
#define MOUTH_EADDR MOUTH_LOWER_EADDR

const OP operations[] PROGMEM = {
  {DELAY, {.delayInMs = 110}},

  // Initial Beat until intro fade in - alternate eyes
 /* {LOOP, {.loopParams = {8, 16}}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {DELAY, {.delayInMs = 250}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 221}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {DELAY, {.delayInMs = 250}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 222}},*/

  // 15250ms is when the first chord starts
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}}, // Beat
  {FADEIN, {.fadeParams = {250, 0x7F, 6, 7, 0, 0xFF, 0}}}, //Fade first half
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}}, // Beat off
  {FADEIN, {.fadeParams = {221, 0xFF, 6, 7, 0, 0xFF, 0}}}, //Fade second half

  // Three more beats until 17127
  /*{LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {DELAY, {.delayInMs = 250}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 222}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {DELAY, {.delayInMs = 250}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 221}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {DELAY, {.delayInMs = 250}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 222}},*/
  
  // 17127 is when the second chord starts (diff 1877)

  // 17622 is when the third chord starts (diff 495)

  // 18630 is when the forth chord starts (diff 1008)

  // Start over

  // 22744 
  // 24621 
  // 25116
  // 26124 




  //30111 - starts beat fading
  // 
  
  {FINISHED, 0}
};
#define END_OF_OPERATIONS ((byte *)operations) + sizeof(operations)

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
  Serial.print("Ready ...");
}


void loop() {
  uint32_t tickDrift = millis();

  byte *mainOperationPC = (byte*)&operations[0];
  OP op;
  do {
    LOOP_PARAMS loopParams = {1, 1};
    
    byte mainOperationType = FINISHED;

    // Get the operation Type 
    memcpy_P(&mainOperationType, mainOperationPC, 1);
    //Serial.print("Main Operation Type: "); Serial.println(mainOperationType);
    
    if (mainOperationType == LOOP) {
      memcpy_P(&loopParams, mainOperationPC + 1, sizeof(loopParams));
      /*Serial.print("Loop operations: "); Serial.println(loopParams.operations);
      Serial.print("Loop back count: "); Serial.println(loopParams.count);*/

      // Adjust program counter
      mainOperationPC += sizeof(OP);
    } else if (mainOperationType == FINISHED) {
      uint32_t currentExitTime = millis();
      Serial.print("Shutting Down: "); Serial.println(currentExitTime);
      delay(10000);
      exit(0);
    }

    
    byte *loopOperationsPC;
    
    for(uint16_t i = 0; i < loopParams.count; i++) {
     // Serial.print("Loop Iteration: "); Serial.println(i);
      loopOperationsPC = mainOperationPC;
      byte *endOfLoopPC = loopOperationsPC + (loopParams.operations * sizeof(OP));
    
      do {
        byte operationType = FINISHED;
  
        // Get the operation Type 
        memcpy_P(&operationType, loopOperationsPC, 1);
        //Serial.print("Operation Type: "); Serial.println(operationType);

        byte *operationStructOffset = loopOperationsPC + 1;
      
        switch(operationType) {
          case DELAY: {
            uint16_t delayInMs = 0;
            memcpy_P(&delayInMs, operationStructOffset, sizeof(uint16_t));
           // Serial.print("Delay: "); Serial.println(delayInMs);
            
            delay(delayInMs);
            break;
          }
          case LED: {
            BEAM beamParams;
            memcpy_P(&beamParams, operationStructOffset, sizeof(BEAM));
            /*Serial.print("BEAM Start: "); Serial.println(beamParams.saddr);
            Serial.print("BEAM End: "); Serial.println(beamParams.eaddr);
            Serial.print("BEAM R: "); Serial.println(beamParams.r);
            Serial.print("BEAM G: "); Serial.println(beamParams.g);
            Serial.print("BEAM B: "); Serial.println(beamParams.b);*/

            for(uint16_t addr = beamParams.saddr; addr <= beamParams.eaddr; addr++) {
              strip.setPixelColor(addr, beamParams.r, beamParams.g, beamParams.b); 
            }
            strip.show();
            break;
          }
          case EQUALIZER: {
            EQUALIZER_PARAMS equalizerParams;
            memcpy_P(&equalizerParams, operationStructOffset, sizeof(EQUALIZER_PARAMS));
            Serial.print("EQUAL Start: "); Serial.println(equalizerParams.saddr);
            Serial.print("EQUAL End: "); Serial.println(equalizerParams.eaddr);
            break;
          }
          case FADEIN: {
            FADE_PARAMS fadeParams;
            memcpy_P(&fadeParams, operationStructOffset, sizeof(FADE_PARAMS));
            /*Serial.print("FADE IN Duration: "); Serial.println(fadeParams.fadeTime);
            Serial.print("FADE IN Brightness: "); Serial.println(fadeParams.brightness);
            Serial.print("FADE IN Start: "); Serial.println(fadeParams.beam.saddr);
            Serial.print("FADE IN End: "); Serial.println(fadeParams.beam.eaddr);
            Serial.print("FADE IN R: "); Serial.println(fadeParams.beam.r);
            Serial.print("FADE IN G: "); Serial.println(fadeParams.beam.g);
            Serial.print("FADE IN B: "); Serial.println(fadeParams.beam.b);*/
            delay(fadeParams.fadeTime);
            break;
          }
          case FADEOUT: {
            FADE_PARAMS fadeParams;
            memcpy_P(&fadeParams, operationStructOffset, sizeof(FADE_PARAMS));
            Serial.print("FADE OUT Duration: "); Serial.println(fadeParams.fadeTime);
            Serial.print("FADE OUT Start: "); Serial.println(fadeParams.beam.saddr);
            Serial.print("FADE OUT End: "); Serial.println(fadeParams.beam.eaddr);
            Serial.print("FADE OUT R: "); Serial.println(fadeParams.beam.r);
            Serial.print("FADE OUT G: "); Serial.println(fadeParams.beam.g);
            Serial.print("FADE OUT B: "); Serial.println(fadeParams.beam.b);
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

      //Serial.println("Done with loop code block, looping back");
    }

    mainOperationPC = loopOperationsPC;

    // Reset loop params
    loopParams.count = loopParams.operations = 1;
    

  } while (mainOperationPC < END_OF_OPERATIONS);

  uint32_t currentExitTime = millis();
  Serial.print("Shutting Down: "); Serial.println(currentExitTime);
  delay(10000);
  exit(0);
}

