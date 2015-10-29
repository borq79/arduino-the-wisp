#include <Adafruit_NeoPixel.h>


#define PRIMARY_PIN 4
#define NUM_PIXEL 150

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
  FADE = 0x04,
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
  uint8_t sbrightness;
  uint8_t ebrightness;
  BEAM beam;
};

struct LOOP_PARAMS {
  byte operations;
  uint16_t count;
};

struct EQUALIZER_PARAMS {
  uint16_t duration;
};

struct OP {
  byte type;

  union {
    BEAM beam;
    uint16_t delayInMs;
    LOOP_PARAMS loopParams;
    EQUALIZER_PARAMS equalizerParams;
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
#define RIGHT_EAR_SADDR RIGHT_EAR_B1_SADDR
#define RIGHT_EAR_EADDR RIGHT_EAR_B5_EADDR

#define RIGHT_CHEEK_SADDR 38
#define RIGHT_CHEEK_EADDR 43

#define RIGHT_EYE_ADDR   44

#define FACE_B1_SADDR 45
#define FACE_B1_EADDR 51
#define FACE_B2_SADDR 52
#define FACE_B2_EADDR 58
#define FACE_B3_SADDR 59
#define FACE_B3_EADDR 65
#define FACE_SADDR FACE_B1_SADDR
#define FACE_EADDR FACE_B3_EADDR

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
#define LEFT_EAR_SADDR LEFT_EAR_B1_SADDR
#define LEFT_EAR_EADDR LEFT_EAR_B5_EADDR

#define MOUTH_UPPER_SADDR 111
#define MOUTH_UPPER_EADDR 129

#define MOUTH_LOWER_SADDR 130
#define MOUTH_LOWER_EADDR 147

#define MOUTH_SADDR MOUTH_UPPER_SADDR
#define MOUTH_EADDR MOUTH_LOWER_EADDR

#define ENTIRE_HEAD_SADDR RIGHT_EAR_B1_SADDR
#define ENTIRE_HEAD_EADDR MOUTH_LOWER_EADDR

// TODO - Things to help size
// Allow nested loops
// Allow Functions or Gotos, 
// Allow variables

const OP operations[] PROGMEM = {
  //{DELAY, {.delayInMs = 110}},


  {LED, {.beam = {ENTIRE_HEAD_SADDR, ENTIRE_HEAD_EADDR, 0x00, 0xFF, 0x00}}},
  {DELAY, {.delayInMs = 6000}},

  // Single notes
  
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 497}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 497}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 497}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 497}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 497}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 497}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 497}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 497}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 497}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},

  {FINISHED, 0},
  /*{LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {LED, {.beam = {LEFT_EAR_SADDR, LEFT_EAR_EADDR, 0xFF, 0x66, 0x00}}},
  {LED, {.beam = {RIGHT_EAR_SADDR, RIGHT_EAR_EADDR, 0xFF, 0x66, 0x00}}},*/
  

  // Over 500 ms wipe across face
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 75}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 75}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0xFF, 0x00, 0xFF}}},

  {DELAY, {.delayInMs = 50}},

  /*{LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {LED, {.beam = {LEFT_EAR_SADDR, LEFT_EAR_EADDR, 0, 0, 0}}},
  {LED, {.beam = {RIGHT_EAR_SADDR, RIGHT_EAR_EADDR, 0, 0, 0}}},*/

//  {DELAY, {.delayInMs = 50}},

  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0x02, 0x7F, 0xF2}}},
  {DELAY, {.delayInMs = 75}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x02, 0x7F, 0xF2}}},
  
  {DELAY, {.delayInMs = 71}},

  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x02, 0x7F, 0xF2}}},
  {DELAY, {.delayInMs = 75}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0x02, 0x7F, 0xF2}}},
  {DELAY, {.delayInMs = 75}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0x02, 0x7F, 0xF2}}},

  {DELAY, {.delayInMs = 50}},

  /*{LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {LED, {.beam = {LEFT_EAR_SADDR, LEFT_EAR_EADDR, 0, 0, 0}}},
  {LED, {.beam = {RIGHT_EAR_SADDR, RIGHT_EAR_EADDR, 0, 0, 0}}},*/

 // {DELAY, {.delayInMs = 50}},

  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0x02, 0x7F, 0xF2}}},
  {DELAY, {.delayInMs = 75}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0x02, 0x7F, 0xF2}}},
  
  {DELAY, {.delayInMs = 71}},

  // Shake mouth for 300 ms
  {LED, {.beam = {MOUTH_SADDR, MOUTH_EADDR, 0x00, 0xFF, 0x00}}},
  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {MOUTH_SADDR, MOUTH_EADDR, 0x00, 0x00, 0x00}}},
  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {MOUTH_SADDR, MOUTH_EADDR, 0x00, 0xFF, 0x00}}},
  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {MOUTH_SADDR, MOUTH_EADDR, 0x00, 0x00, 0x00}}},
  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {MOUTH_SADDR, MOUTH_EADDR, 0x00, 0xFF, 0x00}}},
  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {MOUTH_SADDR, MOUTH_EADDR, 0x00, 0x00, 0x00}}},
  {DELAY, {.delayInMs = 50}},
  

  {FINISHED, 0},

  /*{LOOP, {.loopParams = {20, 2}}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {LED, {.beam = {LEFT_EAR_SADDR, LEFT_EAR_EADDR, 0xFF, 0x66, 0x00}}},
  {LED, {.beam = {RIGHT_EAR_SADDR, RIGHT_EAR_EADDR, 0xFF, 0x66, 0x00}}},
  {DELAY, {.delayInMs = 250}},
  
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {LED, {.beam = {LEFT_EAR_SADDR, LEFT_EAR_EADDR, 0, 0, 0}}},
  {LED, {.beam = {RIGHT_EAR_SADDR, RIGHT_EAR_EADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 221}},

  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {LED, {.beam = {LEFT_EAR_SADDR, LEFT_EAR_EADDR, 0xFF, 0x00, 0xFF}}},
  {LED, {.beam = {RIGHT_EAR_SADDR, RIGHT_EAR_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 250}},
  
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {LED, {.beam = {LEFT_EAR_SADDR, LEFT_EAR_EADDR, 0, 0, 0}}},
  {LED, {.beam = {RIGHT_EAR_SADDR, RIGHT_EAR_EADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 221}},


  // dun dun dun part
  {LOOP, {.loopParams = {20, 2}}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {LED, {.beam = {LEFT_EAR_SADDR, LEFT_EAR_EADDR, 0xFF, 0x66, 0x00}}},
  {LED, {.beam = {RIGHT_EAR_SADDR, RIGHT_EAR_EADDR, 0xFF, 0x66, 0x00}}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},

  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {DELAY, {.delayInMs = 50}},
  LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},
  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {DELAY, {.delayInMs = 100}},
  
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {LED, {.beam = {LEFT_EAR_SADDR, LEFT_EAR_EADDR, 0, 0, 0}}},
  {LED, {.beam = {RIGHT_EAR_SADDR, RIGHT_EAR_EADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 221}},*/





  

  // Initial Beat until intro fade in - alternate eyes
  {LOOP, {.loopParams = {8, 15}}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {DELAY, {.delayInMs = 250}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 221}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {DELAY, {.delayInMs = 250}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 221}},

  // One more left before chords start
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {DELAY, {.delayInMs = 250}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 221}},

  // Beat and start first chord
  {LOOP, {.loopParams = {68, 4}}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {LED, {.beam = {FACE_SADDR, FACE_EADDR, 0, 0xFF, 0}}}, //Fade first half
  {DELAY, {.delayInMs = 250}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 221}},
  
  // 15250ms / 22744 is when the first chord starts - Turn middle face green (5 commands)
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}}, // Beat
  {DELAY, {.delayInMs = 250}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}}, // Beat off
  {DELAY, {.delayInMs = 221}},

  // Three more beats until 17127 / 24621 (12 commands)
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {DELAY, {.delayInMs = 250}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 221}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {DELAY, {.delayInMs = 250}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 221}},

  // Beat and start second chord
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {LED, {.beam = {FACE_SADDR, FACE_EADDR, 0x9F, 0x0E, 0xD2}}}, //Fade first half
  {DELAY, {.delayInMs = 250}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 221}},
  
  // 17127 / 24621 is when the second chord starts (diff 1877) - Turn middle face purple (7 commands)
  // Beat and start third chord
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {LED, {.beam = {FACE_SADDR, FACE_EADDR, 0x08, 0x48, 0xA1}}}, //Fade first half
  {DELAY, {.delayInMs = 250}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 221}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {DELAY, {.delayInMs = 250}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 221}},
  
  // 17622 / 25116 is when the third chord starts (diff 495) - turn middle face blue-ish (10 commands)

  

  // Beat and start forth chord
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {LED, {.beam = {FACE_SADDR, FACE_EADDR, 0xA1, 0x08, 0x17}}}, //Fade first half
  {DELAY, {.delayInMs = 250}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 221}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {DELAY, {.delayInMs = 250}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 221}},
 

  // For 4114 more MS just beat - do 4 more pairs to complete the loop (32 commands)
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {DELAY, {.delayInMs = 250}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 221}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {DELAY, {.delayInMs = 250}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 221}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {DELAY, {.delayInMs = 250}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 221}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {DELAY, {.delayInMs = 250}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 221}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {DELAY, {.delayInMs = 250}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 221}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {DELAY, {.delayInMs = 250}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 221}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {DELAY, {.delayInMs = 250}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 221}},
  // Loop back to the start of the chord progression

  // 342 left - starting with left beat
  /*{LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {DELAY, {.delayInMs = 250}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 221}},*/

  //30053 - brings the chord up
  //30108 - starts the same chords with alternating beats
  // Beat fades over 4 pairs while chord progresses 2x

  //{DELAY, {.delayInMs = 12279}},
  
  // Louder beat with ears starts at 44780
  {LOOP, {.loopParams = {20, 16}}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {LED, {.beam = {LEFT_EAR_SADDR, LEFT_EAR_EADDR, 0xFF, 0x66, 0x00}}},
  {LED, {.beam = {RIGHT_EAR_SADDR, RIGHT_EAR_EADDR, 0xFF, 0x66, 0x00}}},
  {DELAY, {.delayInMs = 250}},
  
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {LED, {.beam = {LEFT_EAR_SADDR, LEFT_EAR_EADDR, 0, 0, 0}}},
  {LED, {.beam = {RIGHT_EAR_SADDR, RIGHT_EAR_EADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 221}},

  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {LED, {.beam = {LEFT_EAR_SADDR, LEFT_EAR_EADDR, 0xFF, 0x00, 0xFF}}},
  {LED, {.beam = {RIGHT_EAR_SADDR, RIGHT_EAR_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 250}},
  
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {LED, {.beam = {LEFT_EAR_SADDR, LEFT_EAR_EADDR, 0, 0, 0}}},
  {LED, {.beam = {RIGHT_EAR_SADDR, RIGHT_EAR_EADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 221}},
  
   

   // 2022 ms of middle face and cheeks lit up
   // 46967 for 1846 is the start of the middle part (dunt da dun da da dun) - beat cheeks 5 times, then then face outside 2x, then middle once
   // Then brighten the entire face middle purple
   // Then wipe from left to right over the face orange, then from right to left blue
   // On the zap part, alternate the colors on the mouth - green
   // There is a double note chord in the middle and then it can loop 4 times

   // Then the single note blasts start at 75327
   // 75327 - middle note
   // 75570 - low note
   // 76052 - high middle note
   // 76517 - low note
   // 76975 - middle note
   // 77451 - low note
   // 77916 - high middle note
   // 78409 - high note
   // 78850 it starts over

  // Beat with ears going
  /*{LOOP, {.loopParams = {12, 16}}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {EQUALIZER, {.equalizerParams = {200}}},
  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {EQUALIZER, {.equalizerParams = {200}}},
  {DELAY, {.delayInMs = 21}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {EQUALIZER, {.equalizerParams = {200}}},
  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {EQUALIZER, {.equalizerParams = {200}}},
  {DELAY, {.delayInMs = 22}},*/

  
  {FINISHED, 0}
};
#define END_OF_OPERATIONS ((byte *)operations) + sizeof(operations)

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
  Serial.println("Waiting for song to start ...");

 /* pinMode(A0, INPUT);
  uint16_t val = 0;
  do {
    val = analogRead(A0);
    Serial.println(val);
  } while (val == 0);*/

  delay(5000);
  Serial.println("Starting!");
  
}
  
void loop() {
  

       
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

      /*uint32_t currentExitTime = millis();
      Serial.print("Loop Start: "); Serial.println(currentExitTime - startTime);*/
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
//ledTime[ledi++] = millis();
            for(uint16_t addr = beamParams.saddr; addr <= beamParams.eaddr; addr++) {
              strip.setPixelColor(addr, beamParams.r, beamParams.g, beamParams.b); 
            }
            strip.show();
            break;
          }
          case EQUALIZER: {
            EQUALIZER_PARAMS equalizerParams;
            memcpy_P(&equalizerParams, operationStructOffset, sizeof(EQUALIZER_PARAMS));
            //Serial.print("EQUAL Duration "); Serial.println(equalizerParams.duration);

            uint16_t timeToLeaveOn = 80;
            uint16_t timeToBlank = 25;
            uint16_t durationMinusOnTime = equalizerParams.duration - timeToLeaveOn - timeToBlank;
            uint16_t durationPerSegment = durationMinusOnTime / 6;
            uint16_t roundingError = durationMinusOnTime - (durationPerSegment * 6);
            //Serial.print("Duration Per Segment: "); Serial.println(durationPerSegment);
            //Serial.print("Rounding Error: "); Serial.println(roundingError);

            // First level Green
            strip.setPixelColor(RIGHT_EAR_B1_SADDR, 0x00, 0xFF, 0x00);
            strip.setPixelColor(RIGHT_EAR_B2_EADDR, 0x00, 0xFF, 0x00);
            strip.setPixelColor(RIGHT_EAR_B3_EADDR, 0x00, 0xFF, 0x00);
            strip.setPixelColor(RIGHT_EAR_B4_SADDR, 0x00, 0xFF, 0x00);
            strip.setPixelColor(RIGHT_EAR_B5_EADDR, 0x00, 0xFF, 0x00);

            strip.setPixelColor(LEFT_EAR_B1_SADDR, 0x00, 0xFF, 0x00);
            strip.setPixelColor(LEFT_EAR_B2_EADDR, 0x00, 0xFF, 0x00);
            strip.setPixelColor(LEFT_EAR_B3_EADDR, 0x00, 0xFF, 0x00);
            strip.setPixelColor(LEFT_EAR_B4_SADDR, 0x00, 0xFF, 0x00);
            strip.setPixelColor(LEFT_EAR_B5_EADDR, 0x00, 0xFF, 0x00);            
            strip.show();
            delay(durationPerSegment);


            // Second level Green
            strip.setPixelColor(RIGHT_EAR_B1_SADDR+1, 0x00, 0xFF, 0x00);
            strip.setPixelColor(RIGHT_EAR_B2_EADDR-1, 0x00, 0xFF, 0x00);
            strip.setPixelColor(RIGHT_EAR_B2_EADDR-2, 0x00, 0xFF, 0x00);
            strip.setPixelColor(RIGHT_EAR_B3_EADDR-1, 0x00, 0xFF, 0x00);
            strip.setPixelColor(RIGHT_EAR_B4_SADDR+1, 0x00, 0xFF, 0x00);
            strip.setPixelColor(RIGHT_EAR_B4_SADDR+2, 0x00, 0xFF, 0x00);
            strip.setPixelColor(RIGHT_EAR_B5_EADDR-1, 0x00, 0xFF, 0x00);

            strip.setPixelColor(LEFT_EAR_B1_SADDR+1, 0x00, 0xFF, 0x00);
            strip.setPixelColor(LEFT_EAR_B2_EADDR-1, 0x00, 0xFF, 0x00);
            strip.setPixelColor(LEFT_EAR_B2_EADDR-2, 0x00, 0xFF, 0x00);
            strip.setPixelColor(LEFT_EAR_B3_EADDR-1, 0x00, 0xFF, 0x00);
            strip.setPixelColor(LEFT_EAR_B4_SADDR+1, 0x00, 0xFF, 0x00);
            strip.setPixelColor(LEFT_EAR_B4_SADDR+2, 0x00, 0xFF, 0x00);
            strip.setPixelColor(LEFT_EAR_B5_EADDR-1, 0x00, 0xFF, 0x00);            
            strip.show();
            delay(durationPerSegment);


            // Third level Green
            strip.setPixelColor(RIGHT_EAR_B1_SADDR+2, 0x00, 0xFF, 0x00);
            strip.setPixelColor(RIGHT_EAR_B2_EADDR-3, 0x00, 0xFF, 0x00);
            strip.setPixelColor(RIGHT_EAR_B3_EADDR-2, 0x00, 0xFF, 0x00);
            strip.setPixelColor(RIGHT_EAR_B4_SADDR+3, 0x00, 0xFF, 0x00);
            strip.setPixelColor(RIGHT_EAR_B5_EADDR-2, 0x00, 0xFF, 0x00);

            strip.setPixelColor(LEFT_EAR_B1_SADDR+2, 0x00, 0xFF, 0x00);
            strip.setPixelColor(LEFT_EAR_B2_EADDR-3, 0x00, 0xFF, 0x00);
            strip.setPixelColor(LEFT_EAR_B3_EADDR-2, 0x00, 0xFF, 0x00);
            strip.setPixelColor(LEFT_EAR_B4_SADDR+3, 0x00, 0xFF, 0x00);
            strip.setPixelColor(LEFT_EAR_B5_EADDR-2, 0x00, 0xFF, 0x00);            
            strip.show();
            delay(durationPerSegment);

            // First level Yellow
            strip.setPixelColor(RIGHT_EAR_B1_SADDR+3, 0xFF, 0xFF, 0x00);
            strip.setPixelColor(RIGHT_EAR_B2_EADDR-4, 0xFF, 0xFF, 0x00);
            strip.setPixelColor(RIGHT_EAR_B3_EADDR-3, 0xFF, 0xFF, 0x00);
            strip.setPixelColor(RIGHT_EAR_B4_SADDR+4, 0xFF, 0xFF, 0x00);
            strip.setPixelColor(RIGHT_EAR_B5_EADDR-3, 0xFF, 0xFF, 0x00);

            strip.setPixelColor(LEFT_EAR_B1_SADDR+3, 0x0FF, 0xFF, 0x00);
            strip.setPixelColor(LEFT_EAR_B2_EADDR-4, 0xFF, 0xFF, 0x00);
            strip.setPixelColor(LEFT_EAR_B3_EADDR-3, 0xFF, 0xFF, 0x00);
            strip.setPixelColor(LEFT_EAR_B4_SADDR+4, 0xFF, 0xFF, 0x00);
            strip.setPixelColor(LEFT_EAR_B5_EADDR-3, 0xFF, 0xFF, 0x00);            
            strip.show();
            delay(durationPerSegment);

            // Second level Yellow
            strip.setPixelColor(RIGHT_EAR_B1_SADDR+4, 0xFF, 0xFF, 0x00);
            strip.setPixelColor(RIGHT_EAR_B1_SADDR+5, 0xFF, 0xFF, 0x00);
            strip.setPixelColor(RIGHT_EAR_B2_EADDR-5, 0xFF, 0xFF, 0x00);
            strip.setPixelColor(RIGHT_EAR_B2_EADDR-6, 0xFF, 0xFF, 0x00);
            strip.setPixelColor(RIGHT_EAR_B3_EADDR-4, 0xFF, 0xFF, 0x00);
            strip.setPixelColor(RIGHT_EAR_B4_SADDR+5, 0xFF, 0xFF, 0x00);
            strip.setPixelColor(RIGHT_EAR_B4_SADDR+6, 0xFF, 0xFF, 0x00);
            strip.setPixelColor(RIGHT_EAR_B5_EADDR-4, 0xFF, 0xFF, 0x00);
            strip.setPixelColor(RIGHT_EAR_B5_EADDR-5, 0xFF, 0xFF, 0x00);

            strip.setPixelColor(LEFT_EAR_B1_SADDR+4, 0xFF, 0xFF, 0x00);
            strip.setPixelColor(LEFT_EAR_B1_SADDR+5, 0xFF, 0xFF, 0x00);
            strip.setPixelColor(LEFT_EAR_B2_EADDR-5, 0xFF, 0xFF, 0x00);
            strip.setPixelColor(LEFT_EAR_B2_EADDR-6, 0xFF, 0xFF, 0x00);
            strip.setPixelColor(LEFT_EAR_B3_EADDR-4, 0xFF, 0xFF, 0x00);
            strip.setPixelColor(LEFT_EAR_B4_SADDR+5, 0xFF, 0xFF, 0x00);
            strip.setPixelColor(LEFT_EAR_B4_SADDR+6, 0xFF, 0xFF, 0x00);
            strip.setPixelColor(LEFT_EAR_B5_EADDR-4, 0xFF, 0xFF, 0x00);    
            strip.setPixelColor(LEFT_EAR_B5_EADDR-5, 0xFF, 0xFF, 0x00);            
            strip.show();
            delay(durationPerSegment);

            // First level Red
            strip.setPixelColor(RIGHT_EAR_B1_SADDR+6, 0xFF, 0x0, 0x00);
            strip.setPixelColor(RIGHT_EAR_B2_EADDR-7, 0xFF, 0x00, 0x00);
            strip.setPixelColor(RIGHT_EAR_B2_EADDR-8, 0xFF, 0x00, 0x00);
            strip.setPixelColor(RIGHT_EAR_B3_EADDR-5, 0xFF, 0x00, 0x00);
            strip.setPixelColor(RIGHT_EAR_B4_SADDR+7, 0xFF, 0x00, 0x00);
            strip.setPixelColor(RIGHT_EAR_B4_SADDR+8, 0xFF, 0x00, 0x00);
            strip.setPixelColor(RIGHT_EAR_B5_EADDR-6, 0xFF, 0x00, 0x00);

            strip.setPixelColor(LEFT_EAR_B1_SADDR+6, 0xFF, 0x0, 0x00);
            strip.setPixelColor(LEFT_EAR_B2_EADDR-7, 0xFF, 0x00, 0x00);
            strip.setPixelColor(LEFT_EAR_B2_EADDR-8, 0xFF, 0x00, 0x00);
            strip.setPixelColor(LEFT_EAR_B3_EADDR+5, 0xFF, 0x00, 0x00);
            strip.setPixelColor(LEFT_EAR_B4_SADDR+7, 0xFF, 0x00, 0x00);
            strip.setPixelColor(LEFT_EAR_B4_SADDR+8, 0xFF, 0x00, 0x00);
            strip.setPixelColor(LEFT_EAR_B5_EADDR-6, 0xFF, 0x00, 0x00);            
            strip.show();
            delay(durationPerSegment);

            delay(roundingError + timeToLeaveOn);

            for(byte addr = RIGHT_EAR_SADDR; addr <= RIGHT_EAR_EADDR; addr++) {
              strip.setPixelColor(addr, 0x00, 0x00, 0x00);
            }

            for(byte addr = LEFT_EAR_SADDR; addr <= LEFT_EAR_EADDR; addr++) {
              strip.setPixelColor(addr, 0x00, 0x00, 0x00);
            }
            strip.show();

            delay(timeToBlank);
            // 1 = 7 (3, 3, 1)
            // 2 = 9 (4, 3, 2)
            // 3 = 6 (3, 2, 1)
            // 4 = 9 (4, 3, 2)
            // 5 = 7 (3, 3, 1)
            
            /*Serial.print("EQUAL Intensity "); Serial.println(equalizerParams.intensity);
            Serial.print("EQUAL Start: "); Serial.println(equalizerParams.saddr);
            Serial.print("EQUAL End: "); Serial.println(equalizerParams.eaddr);

            byte numOfLeds = equalizerParams.eaddr - equalizerParams.saddr;

            if (numOfLeds < 3) {
                Serial.println("The number of LEDs in the Equalizer must be at least 3");
                exit(-1);
            }

            uint16_t durationPerLed = equalizerParams.duration / numOfLeds;
            uint16_t roundingError = equalizerParams.duration - (durationPerLed * numOfLeds);

            Serial.print("Duration Per LED: "); Serial.println(durationPerLed);
            Serial.print("Rounding Error: "); Serial.println(roundingError);

            // Green is bottom 50%
            // Yellow is Middle - Top 33.33%
            // Red is top 16.67%
            byte numOfRed = numOfLeds / 6;
            if (numOfRed <= 0) {
                numOfRed = 1;
            }
    
            byte numOfYellow = numOfLeds / 3;
            if (numOfYellow <= 0) {
                numOfYellow = 1;
            }
    
            byte numOfGreen = numOfLeds / 2;
            if (numOfGreen <= 0) {
                numOfGreen = 1;
            }

            byte leftOver = numOfLeds - (numOfGreen + numOfRed + numOfYellow);
            numOfGreen += leftOver;

            Serial.print("Num of Green: "); Serial.println(numOfGreen);
            Serial.print("Num of Yellow: "); Serial.println(numOfYellow);
            Serial.print("Num of Red: "); Serial.println(numOfRed);
            
            byte addrOffset = equalizerParams.saddr;
            byte addrEnd = equalizerParams.saddr + numOfGreen - 1;
            

            for(byte addr = addrOffset; addr <= addrEnd; addr++) {
              strip.setPixelColor(addr, 0x00, 0xFF, 0x00);
              strip.show();
              delay(durationPerLed);
            }

            addrOffset += numOfGreen;
            addrEnd += numOfYellow;

            for(byte addr = addrOffset; addr <= addrEnd; addr++) {
              strip.setPixelColor(addr, 0xFF, 0xFF, 0x00);
              strip.show();
              delay(durationPerLed);
            }
            addrOffset += numOfYellow; addrEnd += numOfRed;

            for(byte addr = addrOffset; addr <= addrEnd; addr++) {
              strip.setPixelColor(addr, 0xFF, 0x00, 0x00);
              strip.show();
              delay(durationPerLed);
            }

            delay(roundingError);*/
            break;
          }
          case FADE: {
            FADE_PARAMS fadeParams;
            memcpy_P(&fadeParams, operationStructOffset, sizeof(FADE_PARAMS));
            /*Serial.print("FADE IN Duration: "); Serial.println(fadeParams.fadeTime);
            Serial.print("FADE IN Brightness: "); Serial.println(fadeParams.brightness);
            Serial.print("FADE IN Start: "); Serial.println(fadeParams.beam.saddr);
            Serial.print("FADE IN End: "); Serial.println(fadeParams.beam.eaddr);
            Serial.print("FADE IN R: "); Serial.println(fadeParams.beam.r);
            Serial.print("FADE IN G: "); Serial.println(fadeParams.beam.g);
            Serial.print("FADE IN B: "); Serial.println(fadeParams.beam.b);*/


            byte stepIntervalInMs = 10;
            int16_t numberOfSteps = fadeParams.fadeTime / stepIntervalInMs;
            int16_t roundingErrorTime = fadeParams.fadeTime - (numberOfSteps * stepIntervalInMs);

            int16_t brightnessDelta = fadeParams.ebrightness - fadeParams.sbrightness;
            //Serial.print(brightnessDelta);
            int16_t brightnessStep = brightnessDelta / numberOfSteps;

            //Serial.print("Brightness will ramp from "); Serial.print(fadeParams.sbrightness); Serial.print(" to ");  Serial.print(fadeParams.ebrightness); Serial.print(" in ");  Serial.print(numberOfSteps); Serial.print(" steps with a brightness increment of "); Serial.println(brightnessStep);

            for(int16_t i = 1; i <= numberOfSteps; i++) {
              int16_t brightnessForStep = (brightnessStep * i) + (int16_t)fadeParams.sbrightness;
              //Serial.print("Step brightness: "); Serial.println(brightnessForStep);

              int16_t brightnessOffset = 255000 / brightnessForStep;
              //Serial.print("Step Offset: "); Serial.println(brightnessOffset);

              byte r = (((int32_t)fadeParams.beam.r) * 1000) / brightnessOffset;
              byte g = (((int32_t)fadeParams.beam.g) * 1000) / brightnessOffset;
              byte b = (((int32_t)fadeParams.beam.b) * 1000) / brightnessOffset;

              /*Serial.print("FADE IN STEP R: "); Serial.println(r);
              Serial.print("FADE IN STEP G: "); Serial.println(g);
              Serial.print("FADE IN STEP B: "); Serial.println(b);*/
              
              for(uint16_t addr = fadeParams.beam.saddr; addr <= fadeParams.beam.eaddr; addr++) {
                strip.setPixelColor(addr, r, g, b); 
              }
              strip.show();
            }

            // Account for any rounding errors and make sure the brightness matches the requested value at the requested time
            delay(roundingErrorTime);

            for(uint16_t addr = fadeParams.beam.saddr; addr <= fadeParams.beam.eaddr; addr++) {
              strip.setPixelColor(addr, fadeParams.beam.r, fadeParams.beam.g, fadeParams.beam.b); 
            }
            
            strip.show();
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


/*void setEqualizer(byte saddr, byte eaddr, byte level) {
  byte numOfLeds = eaddr - saddr;

  if (numOfLeds < 3) {
      Serial.println("The number of LEDs in the Equalizer must be at least 3");
      exit(-1);
  }

  // Green is bottom 50%
  // Yellow is Middle - Top 33.33%
  // Red is top 16.67%
  byte numOfRed = numOfLeds / 6;
  if (numOfRed <= 0) {
      numOfRed = 1;
  }

  byte numOfYellow = numOfLeds / 3;
  if (numOfYellow <= 0) {
      numOfYellow = 1;
  }

  byte numOfGreen = numOfLeds / 2;
  if (numOfGreen <= 0) {
      numOfGreen = 1;
  }

  byte leftOver = numOfLeds - (numOfGreen + numOfRed + numOfYellow);
  numOfGreen += leftOver;

  Serial.print("Num of Green: "); Serial.println(numOfGreen);
  Serial.print("Num of Yellow: "); Serial.println(numOfYellow);
  Serial.print("Num of Red: "); Serial.println(numOfRed);
  
  byte addrOffset = equalizerParams.saddr;
  byte addrEnd = equalizerParams.saddr + numOfGreen - 1;
  

  for(byte addr = addrOffset; addr <= addrEnd; addr++) {
    strip.setPixelColor(addr, 0x00, 0xFF, 0x00);
  }

  addrOffset += numOfGreen;
  addrEnd += numOfYellow;

  for(byte addr = addrOffset; addr <= addrEnd; addr++) {
    strip.setPixelColor(addr, 0xFF, 0xFF, 0x00);
    strip.show();
    delay(durationPerLed);
  }
  addrOffset += numOfYellow; addrEnd += numOfRed;

  for(byte addr = addrOffset; addr <= addrEnd; addr++) {
    strip.setPixelColor(addr, 0xFF, 0x00, 0x00);
    strip.show();
    delay(durationPerLed);
  }
}*/

