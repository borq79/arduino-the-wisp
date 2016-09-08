#include <Adafruit_NeoPixel.h>


#define PRIMARY_PIN 4
#define NUM_PIXEL 150

#define INIT_SONG_OFFSET 110

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
  WAIT = 0x01,
  LOOP = 0x02,
  LED = 0x03,
  //EQUALIZER = 0x04,
  //FADE = 0x05,
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
    uint32_t waitUntilMs;
    LOOP_PARAMS loopParams;
    //EQUALIZER_PARAMS equalizerParams;
    //FADE_PARAMS fadeParams;
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
  
  // L - s110 l478 (but this will start as soon as the first beat hits, so don't delay 110ms)
   {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 320}},
  
  // R - s578 l471
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 320}},
  
  // L - s1049 l466
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 320}},
  
  // R - s1515 l470
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 320}},
  
  // L - s1985 l471
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 320}},
  
  // R - s2456 l468
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 320}},
  
  // L - s2924 l466
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 320}},
  
  // R - s3390 l472
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 320}},
  
  // L - 3862 l466
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 320}},
  
  // R - 4326 l474
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 320}},
  
  // L - 4800 l466
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 320}},
  
  // R - 5265 l472
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 320}},
  
  // L - 5737 l466
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 320}},
  
  // R - 6203 l472
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 320}},
  
  // L - 6675 
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 320}},
  
  // R - 7141
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 320}},
  
  // L - 7611  (17th beat)
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 250}},
  
  // R - 8078
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 250}},
  
  // L - 8548
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 250}},
  
  // R - 9016
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 320}},
  
  // L - 9486
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 320}},
  
  // R - 9956
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 320}},

  // L - 10426
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 320}},
  
  // R - 10894
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 320}},
  
  // L - 11364
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 320}},
  
  // R - 11828
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 320}},

  // 12300
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 320}},

  // 12531 - Slight noise starts to fade in

  // R - 12766
   {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 320}},
 
  // L - 13236
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 320}},
  
  // R - 13704
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 320}},
  
  // L - 14174
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 320}},

  // R - 14640
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {DELAY, {.delayInMs = 320}},

  
  // L - 15113
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {LED, {.beam = {FACE_SADDR, FACE_EADDR, 0, 0xFF, 0}}}, //First Chord
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  //{WAIT, {.waitUntilMs = 15577}},
  {DELAY, {.delayInMs = 314}},

  // R - 15577
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  //{WAIT, {.waitUntilMs = 16045}},
  {DELAY, {.delayInMs = 300}},
  
  // L - 16045
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
 // {WAIT, {.waitUntilMs = 16515}},
 {DELAY, {.delayInMs = 300}},


  // R - 16515
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  //{WAIT, {.waitUntilMs = 16991}},
  {DELAY, {.delayInMs = 300}},

  
  // L - 16991
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {LED, {.beam = {FACE_SADDR, FACE_EADDR, 0x9F, 0x0E, 0xD2}}}, //Second chord
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  //{WAIT, {.waitUntilMs = 17452}},
   {DELAY, {.delayInMs = 300}},

  // R - 17452 
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {LED, {.beam = {FACE_SADDR, FACE_EADDR, 0x08, 0x48, 0xA1}}}, //Third chord
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  //{WAIT, {.waitUntilMs = 17924}},
  {DELAY, {.delayInMs = 300}},
  
  // L - 17924
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
 // {WAIT, {.waitUntilMs = 18393}},
 {DELAY, {.delayInMs = 300}},
  
  // R - 18393
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {LED, {.beam = {FACE_SADDR, FACE_EADDR, 0xA1, 0x08, 0x17}}}, //Fourth chord
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  //{WAIT, {.waitUntilMs = 18865}},
  {DELAY, {.delayInMs = 300}},
  
  // L - 18865
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
 // {WAIT, {.waitUntilMs = 19330}},
 {DELAY, {.delayInMs = 300}},
  
  // R - 19330
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  //{WAIT, {.waitUntilMs = 19801}},
  {DELAY, {.delayInMs = 300}},
  
  // L - 19801
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
 // {WAIT, {.waitUntilMs = 20270}},
  {DELAY, {.delayInMs = 300}},

  // R - 20270
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  //{WAIT, {.waitUntilMs = 20735}},
  {DELAY, {.delayInMs = 300}},
  
  // L - 20735
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
 // {WAIT, {.waitUntilMs = 21203}},
 {DELAY, {.delayInMs = 300}},

  // R - 21203
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  //{WAIT, {.waitUntilMs = 21677}},
  {DELAY, {.delayInMs = 300}},
  
  // L - 21677
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  
  //{WAIT, {.waitUntilMs = 22137}},
  {DELAY, {.delayInMs = 300}},

  // R - 22137
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {FACE_SADDR, FACE_EADDR, 0, 0xFF, 0}}}, //First Chord
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  
  //{WAIT, {.waitUntilMs = 22613}},
  {DELAY, {.delayInMs = 300}},
  
  // L - 22613
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  //{WAIT, {.waitUntilMs = 23079}},
  {DELAY, {.delayInMs = 300}},

  // R - 23079
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
 // {WAIT, {.waitUntilMs = 23550}},
 {DELAY, {.delayInMs = 300}},
  
  // L - 23550
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
 // {WAIT, {.waitUntilMs = 24020}},
 {DELAY, {.delayInMs = 300}},
  
  // R - 24020
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {LED, {.beam = {FACE_SADDR, FACE_EADDR, 0x9F, 0x0E, 0xD2}}}, // Second chord
  //{WAIT, {.waitUntilMs = 24489}},
  {DELAY, {.delayInMs = 300}},
  
  // L - 24489
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  //{WAIT, {.waitUntilMs = 24952}},
  {DELAY, {.delayInMs = 300}},

  // R - 24952
  {LED, {.beam = {FACE_SADDR, FACE_EADDR, 0x08, 0x48, 0xA1}}}, // third chord
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}}, 
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  //{WAIT, {.waitUntilMs = 25422}},
  {DELAY, {.delayInMs = 300}},
  
  // L - 25422
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  //{WAIT, {.waitUntilMs = 25886}},
  {DELAY, {.delayInMs = 300}},

  // R - 25886
  {LED, {.beam = {FACE_SADDR, FACE_EADDR, 0xA1, 0x08, 0x17}}}, // Fourth chord
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  //{WAIT, {.waitUntilMs = 26358}},
  {DELAY, {.delayInMs = 300}},
  
  // L - 26358
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  //{WAIT, {.waitUntilMs = 26824}},
  {DELAY, {.delayInMs = 300}},

  // R - 26824
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  //{WAIT, {.waitUntilMs = 27297}},
  {DELAY, {.delayInMs = 300}},
  
  // L - 27297
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  //{WAIT, {.waitUntilMs = 27764}},
  {DELAY, {.delayInMs = 300}},

  // R - 27764
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
 // {WAIT, {.waitUntilMs = 28237}},
 {DELAY, {.delayInMs = 300}},
  
  // L - 28237
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
 // {WAIT, {.waitUntilMs = 28700}},
 {DELAY, {.delayInMs = 300}},

  // R - 28700
  
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {FACE_SADDR, FACE_EADDR, 0x9F, 0x0E, 0xD2}}}, // chord changes up
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  //{WAIT, {.waitUntilMs = 29175}},
  {DELAY, {.delayInMs = 300}},
  
  // L - 29175
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  //{WAIT, {.waitUntilMs = 29642}},
  {DELAY, {.delayInMs = 300}},

  // R - 29642
  
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {FACE_SADDR, FACE_EADDR, 0, 0xFF, 0}}}, // chord drops to start over
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
 // {WAIT, {.waitUntilMs = 30108}},
 {DELAY, {.delayInMs = 300}},
  
  // L - 30108 - First beat of the alternating fade out beat
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
 // {WAIT, {.waitUntilMs = 30575}},
 {DELAY, {.delayInMs = 300}},

  // R - 30575
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xDB}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
 // {WAIT, {.waitUntilMs = 31047}},
 {DELAY, {.delayInMs = 300}},
  
  // L - 31047
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xB7, 0, 0}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
 // {WAIT, {.waitUntilMs = 31513}},
 {DELAY, {.delayInMs = 300}},

  // R - 31513
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0x93}}},
  
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {FACE_SADDR, FACE_EADDR, 0x9F, 0x0E, 0xD2}}}, // Second chord
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
 // {WAIT, {.waitUntilMs = 31986}},
 {DELAY, {.delayInMs = 300}},
  
  // L - 31986
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0x6F, 0, 0}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
 // {WAIT, {.waitUntilMs = 32452}},
 {DELAY, {.delayInMs = 300}},

  // R - 32452
  
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0x4B}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {FACE_SADDR, FACE_EADDR, 0x08, 0x48, 0xA1}}}, // third chord
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  //{WAIT, {.waitUntilMs = 32918}},
  {DELAY, {.delayInMs = 300}},
  
  // L - 32918
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0x27, 0, 0}}},
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  // Beat faded out -- 33393

  {DELAY, {.delayInMs = 320}},
  {LED, {.beam = {FACE_SADDR, FACE_EADDR, 0xA1, 0x08, 0x17}}}, // Fourth chord

  //{WAIT, {.waitUntilMs = 37150}},
  {DELAY, {.delayInMs = 4000}},
  {LED, {.beam = {FACE_SADDR, FACE_EADDR, 0, 0xFF, 0}}}, // First chord

  //{WAIT, {.waitUntilMs = 39100}},
  {DELAY, {.delayInMs = 1950}},
  {LED, {.beam = {FACE_SADDR, FACE_EADDR, 0x9F, 0x0E, 0xD2}}}, // second chord

  //{WAIT, {.waitUntilMs = 39850}},
  {DELAY, {.delayInMs = 750}},
  {LED, {.beam = {FACE_SADDR, FACE_EADDR, 0x08, 0x48, 0xA1}}}, // third chord

  //{WAIT, {.waitUntilMs = 40750}},
  {DELAY, {.delayInMs = 900}},
  {LED, {.beam = {FACE_SADDR, FACE_EADDR, 0xA1, 0x08, 0x17}}}, // Fourth chord

  {DELAY, {.delayInMs = 3700}},
  //{WAIT, {.waitUntilMs = 44140}},
  {LED, {.beam = {MOUTH_SADDR, MOUTH_EADDR, 0xFF, 0xD7, 0x00}}}, // Quick blast to start the next segment
  {DELAY, {.delayInMs = 100}},
  {LED, {.beam = {MOUTH_SADDR, MOUTH_EADDR, 0, 0, 0}}},

  // Start Beat with Ears - on blue
  //{WAIT, {.waitUntilMs = 44700}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xEC, 0x25, 0xCF}}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0xEC, 0x25, 0xCF}}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0xEC, 0x25, 0xCF}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0xEC, 0x25, 0xCF}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xEC, 0x25, 0xCF}}},

// blue
  {DELAY, {.delayInMs = 400}},  
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {LED, {.beam = {LEFT_EAR_SADDR, LEFT_EAR_EADDR, 0x00, 0x33, 0x66}}},
  {LED, {.beam = {RIGHT_EAR_SADDR, RIGHT_EAR_EADDR, 0x00, 0x33, 0x66}}},

  // ears and eyes off
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {LED, {.beam = {LEFT_EAR_SADDR, LEFT_EAR_EADDR, 0, 0, 0}}},
  {LED, {.beam = {RIGHT_EAR_SADDR, RIGHT_EAR_EADDR, 0, 0, 0}}},

  // ears and eyes on purple
  {DELAY, {.delayInMs = 320}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {LED, {.beam = {LEFT_EAR_SADDR, LEFT_EAR_EADDR, 0x4A, 0x14, 0x6F}}},
  {LED, {.beam = {RIGHT_EAR_SADDR, RIGHT_EAR_EADDR, 0x4A, 0x14, 0x6F}}},

  // ears and eyes off
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {LED, {.beam = {LEFT_EAR_SADDR, LEFT_EAR_EADDR, 0, 0, 0}}},
  {LED, {.beam = {RIGHT_EAR_SADDR, RIGHT_EAR_EADDR, 0, 0, 0}}},

  // blue
  {DELAY, {.delayInMs = 320}},  
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {LED, {.beam = {LEFT_EAR_SADDR, LEFT_EAR_EADDR, 0x00, 0x33, 0x66}}},
  {LED, {.beam = {RIGHT_EAR_SADDR, RIGHT_EAR_EADDR, 0x00, 0x33, 0x66}}},

  // ears and eyes off
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {LED, {.beam = {LEFT_EAR_SADDR, LEFT_EAR_EADDR, 0, 0, 0}}},
  {LED, {.beam = {RIGHT_EAR_SADDR, RIGHT_EAR_EADDR, 0, 0, 0}}},

  // purple
  {DELAY, {.delayInMs = 320}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {LED, {.beam = {LEFT_EAR_SADDR, LEFT_EAR_EADDR, 0x4A, 0x14, 0x6F}}},
  {LED, {.beam = {RIGHT_EAR_SADDR, RIGHT_EAR_EADDR, 0x4A, 0x14, 0x6F}}},

  // ears and eyes off
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {LED, {.beam = {LEFT_EAR_SADDR, LEFT_EAR_EADDR, 0, 0, 0}}},
  {LED, {.beam = {RIGHT_EAR_SADDR, RIGHT_EAR_EADDR, 0, 0, 0}}},


  {DELAY, {.delayInMs = 240}}, 
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},
   // blue - 5th beat
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {LED, {.beam = {LEFT_EAR_SADDR, LEFT_EAR_EADDR, 0x00, 0x33, 0x66}}},
  {LED, {.beam = {RIGHT_EAR_SADDR, RIGHT_EAR_EADDR, 0x00, 0x33, 0x66}}},
  

  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},



  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},

  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  // off 
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {LED, {.beam = {LEFT_EAR_SADDR, LEFT_EAR_EADDR, 0, 0, 0}}},
  {LED, {.beam = {RIGHT_EAR_SADDR, RIGHT_EAR_EADDR, 0, 0, 0}}},
  
  
  {DELAY, {.delayInMs = 100}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},
  
  
  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},

  
  
  {DELAY, {.delayInMs = 100}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},


  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},

   // purple - 6th
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {LED, {.beam = {LEFT_EAR_SADDR, LEFT_EAR_EADDR, 0x4A, 0x14, 0x6F}}},
  {LED, {.beam = {RIGHT_EAR_SADDR, RIGHT_EAR_EADDR, 0x4A, 0x14, 0x6F}}}, 
  

  {DELAY, {.delayInMs = 100}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},
   

  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},

      // off 
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {LED, {.beam = {LEFT_EAR_SADDR, LEFT_EAR_EADDR, 0, 0, 0}}},
  {LED, {.beam = {RIGHT_EAR_SADDR, RIGHT_EAR_EADDR, 0, 0, 0}}},

  {DELAY, {.delayInMs = 100}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0xFF, 0x00, 0xFF}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0xFF, 0x00, 0xFF}}},

  

  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0x00, 0x00, 0x00}}},

  {DELAY, {.delayInMs = 100}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0x00, 0xFF, 0x00}}},
    
 

  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0, 0, 0}}},

  // blue - 7th
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {LED, {.beam = {LEFT_EAR_SADDR, LEFT_EAR_EADDR, 0x00, 0x33, 0x66}}},
  {LED, {.beam = {RIGHT_EAR_SADDR, RIGHT_EAR_EADDR, 0x00, 0x33, 0x66}}},

  {DELAY, {.delayInMs = 100}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0xFF, 0x00, 0xFF}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0xFF, 0x00, 0xFF}}},
   

  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0x00, 0x00, 0x00}}},

  // off 
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {LED, {.beam = {LEFT_EAR_SADDR, LEFT_EAR_EADDR, 0, 0, 0}}},
  {LED, {.beam = {RIGHT_EAR_SADDR, RIGHT_EAR_EADDR, 0, 0, 0}}},

  {DELAY, {.delayInMs = 100}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},
 
  
  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0, 0x00, 0x00}}},

   
  // purple - 8th
  {DELAY, {.delayInMs = 170}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {LED, {.beam = {LEFT_EAR_SADDR, LEFT_EAR_EADDR, 0x4A, 0x14, 0x6F}}},
  {LED, {.beam = {RIGHT_EAR_SADDR, RIGHT_EAR_EADDR, 0x4A, 0x14, 0x6F}}},

  // off 
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {LED, {.beam = {LEFT_EAR_SADDR, LEFT_EAR_EADDR, 0, 0, 0}}},
  {LED, {.beam = {RIGHT_EAR_SADDR, RIGHT_EAR_EADDR, 0, 0, 0}}},

  
  {DELAY, {.delayInMs = 270}},
  

  //{DELAY, {.delayInMs = 50}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xEC, 0x25, 0xCF}}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0xEC, 0x25, 0xCF}}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0xEC, 0x25, 0xCF}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0xEC, 0x25, 0xCF}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xEC, 0x25, 0xCF}}},

{DELAY, {.delayInMs = 30}},
// blue - 9th
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {LED, {.beam = {LEFT_EAR_SADDR, LEFT_EAR_EADDR, 0x00, 0x33, 0x66}}},
  {LED, {.beam = {RIGHT_EAR_SADDR, RIGHT_EAR_EADDR, 0x00, 0x33, 0x66}}},

  

  // off 
  {DELAY, {.delayInMs = 120}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {LED, {.beam = {LEFT_EAR_SADDR, LEFT_EAR_EADDR, 0, 0, 0}}},
  {LED, {.beam = {RIGHT_EAR_SADDR, RIGHT_EAR_EADDR, 0, 0, 0}}},

  // purple - 8th
  {DELAY, {.delayInMs = 320}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0xFF}}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0xFF, 0, 0}}},
  {LED, {.beam = {LEFT_EAR_SADDR, LEFT_EAR_EADDR, 0x4A, 0x14, 0x6F}}},
  {LED, {.beam = {RIGHT_EAR_SADDR, RIGHT_EAR_EADDR, 0x4A, 0x14, 0x6F}}},

  // off 
  {DELAY, {.delayInMs = 150}},
  {LED, {.beam = {RIGHT_EYE_ADDR, RIGHT_EYE_ADDR, 0, 0, 0}}},
  {LED, {.beam = {LEFT_EYE_ADDR, LEFT_EYE_ADDR, 0, 0, 0}}},
  {LED, {.beam = {LEFT_EAR_SADDR, LEFT_EAR_EADDR, 0, 0, 0}}},
  {LED, {.beam = {RIGHT_EAR_SADDR, RIGHT_EAR_EADDR, 0, 0, 0}}},

  {DELAY, {.delayInMs = 120}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xFF, 0x00, 0}}},
  {DELAY, {.delayInMs = 75}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0xFF, 0x00, 0}}},
  {DELAY, {.delayInMs = 75}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0xFF, 0x00, 0}}},
  {DELAY, {.delayInMs = 75}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0xFF, 0x00, 0}}},
  {DELAY, {.delayInMs = 75}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0}}},

  {DELAY, {.delayInMs = 100}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0xFF, 0xFF}}},
  {DELAY, {.delayInMs = 75}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0x00, 0xFF, 0xFF}}},
  {DELAY, {.delayInMs = 75}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0x00, 0xFF, 0xFF}}},
  {DELAY, {.delayInMs = 75}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0x00, 0xFF, 0xFF}}},
  {DELAY, {.delayInMs = 75}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0x00, 0xFF, 0xFF}}},

  {DELAY, {.delayInMs = 100}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  
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
  

  {DELAY, {.delayInMs = 1000}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0, 0, 0xFF}}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0, 0, 0xFF}}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0, 0, 0xFF}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0, 0, 0xFF}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0, 0, 0xFF}}},

  {DELAY, {.delayInMs = 300}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0, 0xFF}}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR,  0xFF, 0, 0xFF}}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR,  0xFF, 0, 0xFF}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR,  0xFF, 0, 0xFF}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR,  0xFF, 0, 0xFF}}},

  {DELAY, {.delayInMs = 300}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xAA, 0xBB, 0xCC}}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0xAA, 0xBB, 0xCC}}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0xAA, 0xBB, 0xCC}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0xAA, 0xBB, 0xCC}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xAA, 0xBB, 0xCC}}},


  {DELAY, {.delayInMs = 1900}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},

  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},

  // cheeks on
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},

  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},

  // cheeks on
  {DELAY, {.delayInMs = 100}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},

  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},

  
  {DELAY, {.delayInMs = 100}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},

  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},

  {DELAY, {.delayInMs = 100}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},

  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},

  {DELAY, {.delayInMs = 100}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0xFF, 0x00, 0xFF}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0xFF, 0x00, 0xFF}}},

  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0x00, 0x00, 0x00}}},

  {DELAY, {.delayInMs = 100}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0x00, 0xFF, 0x00}}},

  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0, 0, 0}}},

  {DELAY, {.delayInMs = 100}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0xFF, 0x00, 0xFF}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0xFF, 0x00, 0xFF}}},

  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0x00, 0x00, 0x00}}},

  {DELAY, {.delayInMs = 100}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},

  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0, 0x00, 0x00}}},

  {DELAY, {.delayInMs = 500}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xEC, 0x25, 0xCF}}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0xEC, 0x25, 0xCF}}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0xEC, 0x25, 0xCF}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0xEC, 0x25, 0xCF}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xEC, 0x25, 0xCF}}},

  {DELAY, {.delayInMs = 800}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xFF, 0x00, 0}}},
  {DELAY, {.delayInMs = 75}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0xFF, 0x00, 0}}},
  {DELAY, {.delayInMs = 75}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0xFF, 0x00, 0}}},
  {DELAY, {.delayInMs = 75}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0xFF, 0x00, 0}}},
  {DELAY, {.delayInMs = 75}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0}}},

  {DELAY, {.delayInMs = 100}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0xFF, 0xFF}}},
  {DELAY, {.delayInMs = 75}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0x00, 0xFF, 0xFF}}},
  {DELAY, {.delayInMs = 75}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0x00, 0xFF, 0xFF}}},
  {DELAY, {.delayInMs = 75}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0x00, 0xFF, 0xFF}}},
  {DELAY, {.delayInMs = 75}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0x00, 0xFF, 0xFF}}},

  {DELAY, {.delayInMs = 100}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  
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
  
// next point to start 59122 in song - repeats again
  {DELAY, {.delayInMs = 1000}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0, 0, 0xFF}}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0, 0, 0xFF}}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0, 0, 0xFF}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0, 0, 0xFF}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0, 0, 0xFF}}},

  {DELAY, {.delayInMs = 300}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0, 0xFF}}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR,  0xFF, 0, 0xFF}}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR,  0xFF, 0, 0xFF}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR,  0xFF, 0, 0xFF}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR,  0xFF, 0, 0xFF}}},

  {DELAY, {.delayInMs = 300}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xAA, 0xBB, 0xCC}}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0xAA, 0xBB, 0xCC}}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0xAA, 0xBB, 0xCC}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0xAA, 0xBB, 0xCC}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xAA, 0xBB, 0xCC}}},


  {DELAY, {.delayInMs = 1900}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},

  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},

  // cheeks on
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},

  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},

  // cheeks on
  {DELAY, {.delayInMs = 100}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},

  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},

  
  {DELAY, {.delayInMs = 100}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},

  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},

  {DELAY, {.delayInMs = 100}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},

  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},

  {DELAY, {.delayInMs = 100}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0xFF, 0x00, 0xFF}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0xFF, 0x00, 0xFF}}},

  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0x00, 0x00, 0x00}}},

  {DELAY, {.delayInMs = 100}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0x00, 0xFF, 0x00}}},

  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0, 0, 0}}},

  {DELAY, {.delayInMs = 100}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0xFF, 0x00, 0xFF}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0xFF, 0x00, 0xFF}}},

  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0x00, 0x00, 0x00}}},

  {DELAY, {.delayInMs = 100}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},

  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0, 0x00, 0x00}}},

  {DELAY, {.delayInMs = 500}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xEC, 0x25, 0xCF}}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0xEC, 0x25, 0xCF}}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0xEC, 0x25, 0xCF}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0xEC, 0x25, 0xCF}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xEC, 0x25, 0xCF}}},

  {DELAY, {.delayInMs = 800}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xFF, 0x00, 0}}},
  {DELAY, {.delayInMs = 75}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0xFF, 0x00, 0}}},
  {DELAY, {.delayInMs = 75}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0xFF, 0x00, 0}}},
  {DELAY, {.delayInMs = 75}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0xFF, 0x00, 0}}},
  {DELAY, {.delayInMs = 75}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0}}},

  {DELAY, {.delayInMs = 100}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0xFF, 0xFF}}},
  {DELAY, {.delayInMs = 75}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0x00, 0xFF, 0xFF}}},
  {DELAY, {.delayInMs = 75}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0x00, 0xFF, 0xFF}}},
  {DELAY, {.delayInMs = 75}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0x00, 0xFF, 0xFF}}},
  {DELAY, {.delayInMs = 75}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0x00, 0xFF, 0xFF}}},

  {DELAY, {.delayInMs = 100}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  
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

  // again

  {DELAY, {.delayInMs = 1000}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0, 0, 0xFF}}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0, 0, 0xFF}}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0, 0, 0xFF}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0, 0, 0xFF}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0, 0, 0xFF}}},

  {DELAY, {.delayInMs = 300}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0, 0xFF}}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR,  0xFF, 0, 0xFF}}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR,  0xFF, 0, 0xFF}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR,  0xFF, 0, 0xFF}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR,  0xFF, 0, 0xFF}}},

  {DELAY, {.delayInMs = 300}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xAA, 0xBB, 0xCC}}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0xAA, 0xBB, 0xCC}}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0xAA, 0xBB, 0xCC}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0xAA, 0xBB, 0xCC}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xAA, 0xBB, 0xCC}}},


  {DELAY, {.delayInMs = 1900}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},

  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},

  // cheeks on
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},

  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},

  // cheeks on
  {DELAY, {.delayInMs = 100}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},

  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},

  
  {DELAY, {.delayInMs = 100}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},

  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},

  {DELAY, {.delayInMs = 100}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},

  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},

  {DELAY, {.delayInMs = 100}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0xFF, 0x00, 0xFF}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0xFF, 0x00, 0xFF}}},

  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0x00, 0x00, 0x00}}},

  {DELAY, {.delayInMs = 100}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0x00, 0xFF, 0x00}}},

  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0, 0, 0}}},

  {DELAY, {.delayInMs = 100}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0xFF, 0x00, 0xFF}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0xFF, 0x00, 0xFF}}},

  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0x00, 0x00, 0x00}}},

  {DELAY, {.delayInMs = 100}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xFF, 0x00, 0x00}}},

  {DELAY, {.delayInMs = 50}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0, 0x00, 0x00}}},

  {DELAY, {.delayInMs = 500}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xEC, 0x25, 0xCF}}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0xEC, 0x25, 0xCF}}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0xEC, 0x25, 0xCF}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0xEC, 0x25, 0xCF}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xEC, 0x25, 0xCF}}},

  {DELAY, {.delayInMs = 800}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xFF, 0x00, 0}}},
  {DELAY, {.delayInMs = 75}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0xFF, 0x00, 0}}},
  {DELAY, {.delayInMs = 75}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0xFF, 0x00, 0}}},
  {DELAY, {.delayInMs = 75}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0xFF, 0x00, 0}}},
  {DELAY, {.delayInMs = 75}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0}}},

  {DELAY, {.delayInMs = 100}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0xFF, 0xFF}}},
  {DELAY, {.delayInMs = 75}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0x00, 0xFF, 0xFF}}},
  {DELAY, {.delayInMs = 75}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0x00, 0xFF, 0xFF}}},
  {DELAY, {.delayInMs = 75}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0x00, 0xFF, 0xFF}}},
  {DELAY, {.delayInMs = 75}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0x00, 0xFF, 0xFF}}},

  {DELAY, {.delayInMs = 100}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  
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

  {DELAY, {.delayInMs = 1000}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0, 0, 0xFF}}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0, 0, 0xFF}}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0, 0, 0xFF}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0, 0, 0xFF}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0, 0, 0xFF}}},


  // next spot 75063
  {DELAY, {.delayInMs = 1000}},
   {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0, 0, 0}}},
  {LED, {.beam = {FACE_B1_SADDR, FACE_B1_EADDR, 0, 0, 0}}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0, 0, 0}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0, 0, 0}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0, 0, 0}}},

  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 450}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 450}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 450}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 450}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 450}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 450}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 450}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 450}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},

// 78813

  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 450}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 450}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 450}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 450}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 450}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 450}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 450}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 450}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},


  // 82577
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 450}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 450}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 450}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 450}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 450}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 450}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 450}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 450}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},

  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 450}},
  {LED, {.beam = {FACE_B2_SADDR, FACE_B2_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 450}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 450}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 450}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 450}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 450}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 450}},
  {LED, {.beam = {FACE_B3_SADDR, FACE_B3_EADDR, 0x00, 0x00, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xFF, 0x00, 0xFF}}},
  {DELAY, {.delayInMs = 450}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0x00, 0x00, 0x00}}},

  // 90057
  {DELAY, {.delayInMs = 300}},
  {LED, {.beam = {FACE_SADDR, FACE_EADDR, 0, 0xFF, 0}}}, // First chord
  
  {DELAY, {.delayInMs = 1950}},
  {LED, {.beam = {FACE_SADDR, FACE_EADDR, 0x9F, 0x0E, 0xD2}}}, // second chord
  
  {DELAY, {.delayInMs = 750}},
  {LED, {.beam = {FACE_SADDR, FACE_EADDR, 0x08, 0x48, 0xA1}}}, // third chord

  {DELAY, {.delayInMs = 900}},
  {LED, {.beam = {FACE_SADDR, FACE_EADDR, 0xA1, 0x08, 0x17}}}, // Fourth chord

  {DELAY, {.delayInMs = 1500}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0xFF}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xFF, 0x00, 0xFF}}},

  {DELAY, {.delayInMs = 500}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0xFF, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0x00, 0xFF, 0x00}}},

  {DELAY, {.delayInMs = 1750}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0x00, 0, 0x00}}},
  {LED, {.beam = {FACE_SADDR, FACE_EADDR, 0, 0xFF, 0}}}, // First chord
  
  {DELAY, {.delayInMs = 1950}},
  {LED, {.beam = {FACE_SADDR, FACE_EADDR, 0x9F, 0x0E, 0xD2}}}, // second chord
  
  {DELAY, {.delayInMs = 750}},
  {LED, {.beam = {FACE_SADDR, FACE_EADDR, 0x08, 0x48, 0xA1}}}, // third chord

  {DELAY, {.delayInMs = 900}},
  {LED, {.beam = {FACE_SADDR, FACE_EADDR, 0xA1, 0x08, 0x17}}}, // Fourth chord

  {DELAY, {.delayInMs = 1500}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0xFF, 0x00, 0xFF}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0xFF, 0x00, 0xFF}}},

  {DELAY, {.delayInMs = 500}},
  {LED, {.beam = {RIGHT_CHEEK_SADDR, RIGHT_CHEEK_EADDR, 0x00, 0xFF, 0x00}}},
  {LED, {.beam = {LEFT_CHEEK_SADDR, LEFT_CHEEK_EADDR, 0x00, 0xFF, 0x00}}},


  {DELAY, {.delayInMs = 1500}},
  // 104550
  {LED, {.beam = {ENTIRE_HEAD_SADDR, ENTIRE_HEAD_EADDR, 0x00, 0x00, 0x00}}},
  {DELAY, {.delayInMs = 300}},
  {LED, {.beam = {ENTIRE_HEAD_SADDR, ENTIRE_HEAD_EADDR, 0x00, 0xFF, 0x00}}},

  // 112813
  {DELAY, {.delayInMs = 7500}},
  {LED, {.beam = {ENTIRE_HEAD_SADDR, ENTIRE_HEAD_EADDR, 0x00, 0, 0xFF}}},

// done
  {DELAY, {.delayInMs = 7500}},
  {LED, {.beam = {ENTIRE_HEAD_SADDR, ENTIRE_HEAD_EADDR, 0x00, 0, 0}}},
  {FINISHED, 0}
};
#define END_OF_OPERATIONS ((byte *)operations) + sizeof(operations)

static uint32_t startTime = 0;

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
  Serial.println("Waiting for song to start ...");

  pinMode(A0, INPUT);
  uint16_t val = 0;
  do {
    val = analogRead(A0);
   // Serial.println(val);
  } while (val <= 5);

  startTime = millis();

  //delay(5000);
 // Serial.println("Starting!");
  
  
}
  uint32_t drifter[100];
  uint16_t d = 0;
  
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
      Serial.print("Start party mode: "); Serial.println(currentExitTime);
 rainbow(20);
  rainbowCycle(20);
//      uint32_t prev = 0;
//for(uint8_t i = 0; i < d; i++){
//  uint32_t ts = (drifter[i] - startTime) + INIT_SONG_OFFSET;
//  Serial.print(ts); Serial.print(" "); Serial.println(drifter[i] - startTime - prev);
//  prev = ts;
//}
      delay(10000);
      exit(0);
    }

    
    byte *loopOperationsPC;
//    uint32_t one = 0;
//    uint32_t two = 0;
//    uint32_t three = 0;
    
    for(uint16_t i = 0; i < loopParams.count; i++) {
     // one = millis();
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
          case WAIT: {
            uint32_t waitUntilMs = 0;
            memcpy_P(&waitUntilMs, operationStructOffset, sizeof(uint32_t));
           // Serial.print("Delay: "); Serial.println(delayInMs);

            while (((millis() - startTime) + INIT_SONG_OFFSET) < waitUntilMs) {
              delay(1);
            }
            break;
          }
          case LED: {
           // two = millis();
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
            if (beamParams.saddr == FACE_SADDR) {
            drifter[d++] = millis();
            }
           // three = millis();

            //uint32_t n = millis();
            //Serial.println(" Time: " ); Serial.print(n - one); Serial.print(" "); Serial.print(two - one);Serial.print(" "); Serial.print(three - two); Serial.print(" "); Serial.print(n - three);
            
            break;
          }
//          case EQUALIZER: {
//            EQUALIZER_PARAMS equalizerParams;
//            memcpy_P(&equalizerParams, operationStructOffset, sizeof(EQUALIZER_PARAMS));
//            //Serial.print("EQUAL Duration "); Serial.println(equalizerParams.duration);
//
//            uint16_t timeToLeaveOn = 80;
//            uint16_t timeToBlank = 25;
//            uint16_t durationMinusOnTime = equalizerParams.duration - timeToLeaveOn - timeToBlank;
//            uint16_t durationPerSegment = durationMinusOnTime / 6;
//            uint16_t roundingError = durationMinusOnTime - (durationPerSegment * 6);
//            //Serial.print("Duration Per Segment: "); Serial.println(durationPerSegment);
//            //Serial.print("Rounding Error: "); Serial.println(roundingError);
//
//            // First level Green
//            strip.setPixelColor(RIGHT_EAR_B1_SADDR, 0x00, 0xFF, 0x00);
//            strip.setPixelColor(RIGHT_EAR_B2_EADDR, 0x00, 0xFF, 0x00);
//            strip.setPixelColor(RIGHT_EAR_B3_EADDR, 0x00, 0xFF, 0x00);
//            strip.setPixelColor(RIGHT_EAR_B4_SADDR, 0x00, 0xFF, 0x00);
//            strip.setPixelColor(RIGHT_EAR_B5_EADDR, 0x00, 0xFF, 0x00);
//
//            strip.setPixelColor(LEFT_EAR_B1_SADDR, 0x00, 0xFF, 0x00);
//            strip.setPixelColor(LEFT_EAR_B2_EADDR, 0x00, 0xFF, 0x00);
//            strip.setPixelColor(LEFT_EAR_B3_EADDR, 0x00, 0xFF, 0x00);
//            strip.setPixelColor(LEFT_EAR_B4_SADDR, 0x00, 0xFF, 0x00);
//            strip.setPixelColor(LEFT_EAR_B5_EADDR, 0x00, 0xFF, 0x00);            
//            strip.show();
//            delay(durationPerSegment);
//
//
//            // Second level Green
//            strip.setPixelColor(RIGHT_EAR_B1_SADDR+1, 0x00, 0xFF, 0x00);
//            strip.setPixelColor(RIGHT_EAR_B2_EADDR-1, 0x00, 0xFF, 0x00);
//            strip.setPixelColor(RIGHT_EAR_B2_EADDR-2, 0x00, 0xFF, 0x00);
//            strip.setPixelColor(RIGHT_EAR_B3_EADDR-1, 0x00, 0xFF, 0x00);
//            strip.setPixelColor(RIGHT_EAR_B4_SADDR+1, 0x00, 0xFF, 0x00);
//            strip.setPixelColor(RIGHT_EAR_B4_SADDR+2, 0x00, 0xFF, 0x00);
//            strip.setPixelColor(RIGHT_EAR_B5_EADDR-1, 0x00, 0xFF, 0x00);
//
//            strip.setPixelColor(LEFT_EAR_B1_SADDR+1, 0x00, 0xFF, 0x00);
//            strip.setPixelColor(LEFT_EAR_B2_EADDR-1, 0x00, 0xFF, 0x00);
//            strip.setPixelColor(LEFT_EAR_B2_EADDR-2, 0x00, 0xFF, 0x00);
//            strip.setPixelColor(LEFT_EAR_B3_EADDR-1, 0x00, 0xFF, 0x00);
//            strip.setPixelColor(LEFT_EAR_B4_SADDR+1, 0x00, 0xFF, 0x00);
//            strip.setPixelColor(LEFT_EAR_B4_SADDR+2, 0x00, 0xFF, 0x00);
//            strip.setPixelColor(LEFT_EAR_B5_EADDR-1, 0x00, 0xFF, 0x00);            
//            strip.show();
//            delay(durationPerSegment);
//
//
//            // Third level Green
//            strip.setPixelColor(RIGHT_EAR_B1_SADDR+2, 0x00, 0xFF, 0x00);
//            strip.setPixelColor(RIGHT_EAR_B2_EADDR-3, 0x00, 0xFF, 0x00);
//            strip.setPixelColor(RIGHT_EAR_B3_EADDR-2, 0x00, 0xFF, 0x00);
//            strip.setPixelColor(RIGHT_EAR_B4_SADDR+3, 0x00, 0xFF, 0x00);
//            strip.setPixelColor(RIGHT_EAR_B5_EADDR-2, 0x00, 0xFF, 0x00);
//
//            strip.setPixelColor(LEFT_EAR_B1_SADDR+2, 0x00, 0xFF, 0x00);
//            strip.setPixelColor(LEFT_EAR_B2_EADDR-3, 0x00, 0xFF, 0x00);
//            strip.setPixelColor(LEFT_EAR_B3_EADDR-2, 0x00, 0xFF, 0x00);
//            strip.setPixelColor(LEFT_EAR_B4_SADDR+3, 0x00, 0xFF, 0x00);
//            strip.setPixelColor(LEFT_EAR_B5_EADDR-2, 0x00, 0xFF, 0x00);            
//            strip.show();
//            delay(durationPerSegment);
//
//            // First level Yellow
//            strip.setPixelColor(RIGHT_EAR_B1_SADDR+3, 0xFF, 0xFF, 0x00);
//            strip.setPixelColor(RIGHT_EAR_B2_EADDR-4, 0xFF, 0xFF, 0x00);
//            strip.setPixelColor(RIGHT_EAR_B3_EADDR-3, 0xFF, 0xFF, 0x00);
//            strip.setPixelColor(RIGHT_EAR_B4_SADDR+4, 0xFF, 0xFF, 0x00);
//            strip.setPixelColor(RIGHT_EAR_B5_EADDR-3, 0xFF, 0xFF, 0x00);
//
//            strip.setPixelColor(LEFT_EAR_B1_SADDR+3, 0x0FF, 0xFF, 0x00);
//            strip.setPixelColor(LEFT_EAR_B2_EADDR-4, 0xFF, 0xFF, 0x00);
//            strip.setPixelColor(LEFT_EAR_B3_EADDR-3, 0xFF, 0xFF, 0x00);
//            strip.setPixelColor(LEFT_EAR_B4_SADDR+4, 0xFF, 0xFF, 0x00);
//            strip.setPixelColor(LEFT_EAR_B5_EADDR-3, 0xFF, 0xFF, 0x00);            
//            strip.show();
//            delay(durationPerSegment);
//
//            // Second level Yellow
//            strip.setPixelColor(RIGHT_EAR_B1_SADDR+4, 0xFF, 0xFF, 0x00);
//            strip.setPixelColor(RIGHT_EAR_B1_SADDR+5, 0xFF, 0xFF, 0x00);
//            strip.setPixelColor(RIGHT_EAR_B2_EADDR-5, 0xFF, 0xFF, 0x00);
//            strip.setPixelColor(RIGHT_EAR_B2_EADDR-6, 0xFF, 0xFF, 0x00);
//            strip.setPixelColor(RIGHT_EAR_B3_EADDR-4, 0xFF, 0xFF, 0x00);
//            strip.setPixelColor(RIGHT_EAR_B4_SADDR+5, 0xFF, 0xFF, 0x00);
//            strip.setPixelColor(RIGHT_EAR_B4_SADDR+6, 0xFF, 0xFF, 0x00);
//            strip.setPixelColor(RIGHT_EAR_B5_EADDR-4, 0xFF, 0xFF, 0x00);
//            strip.setPixelColor(RIGHT_EAR_B5_EADDR-5, 0xFF, 0xFF, 0x00);
//
//            strip.setPixelColor(LEFT_EAR_B1_SADDR+4, 0xFF, 0xFF, 0x00);
//            strip.setPixelColor(LEFT_EAR_B1_SADDR+5, 0xFF, 0xFF, 0x00);
//            strip.setPixelColor(LEFT_EAR_B2_EADDR-5, 0xFF, 0xFF, 0x00);
//            strip.setPixelColor(LEFT_EAR_B2_EADDR-6, 0xFF, 0xFF, 0x00);
//            strip.setPixelColor(LEFT_EAR_B3_EADDR-4, 0xFF, 0xFF, 0x00);
//            strip.setPixelColor(LEFT_EAR_B4_SADDR+5, 0xFF, 0xFF, 0x00);
//            strip.setPixelColor(LEFT_EAR_B4_SADDR+6, 0xFF, 0xFF, 0x00);
//            strip.setPixelColor(LEFT_EAR_B5_EADDR-4, 0xFF, 0xFF, 0x00);    
//            strip.setPixelColor(LEFT_EAR_B5_EADDR-5, 0xFF, 0xFF, 0x00);            
//            strip.show();
//            delay(durationPerSegment);
//
//            // First level Red
//            strip.setPixelColor(RIGHT_EAR_B1_SADDR+6, 0xFF, 0x0, 0x00);
//            strip.setPixelColor(RIGHT_EAR_B2_EADDR-7, 0xFF, 0x00, 0x00);
//            strip.setPixelColor(RIGHT_EAR_B2_EADDR-8, 0xFF, 0x00, 0x00);
//            strip.setPixelColor(RIGHT_EAR_B3_EADDR-5, 0xFF, 0x00, 0x00);
//            strip.setPixelColor(RIGHT_EAR_B4_SADDR+7, 0xFF, 0x00, 0x00);
//            strip.setPixelColor(RIGHT_EAR_B4_SADDR+8, 0xFF, 0x00, 0x00);
//            strip.setPixelColor(RIGHT_EAR_B5_EADDR-6, 0xFF, 0x00, 0x00);
//
//            strip.setPixelColor(LEFT_EAR_B1_SADDR+6, 0xFF, 0x0, 0x00);
//            strip.setPixelColor(LEFT_EAR_B2_EADDR-7, 0xFF, 0x00, 0x00);
//            strip.setPixelColor(LEFT_EAR_B2_EADDR-8, 0xFF, 0x00, 0x00);
//            strip.setPixelColor(LEFT_EAR_B3_EADDR+5, 0xFF, 0x00, 0x00);
//            strip.setPixelColor(LEFT_EAR_B4_SADDR+7, 0xFF, 0x00, 0x00);
//            strip.setPixelColor(LEFT_EAR_B4_SADDR+8, 0xFF, 0x00, 0x00);
//            strip.setPixelColor(LEFT_EAR_B5_EADDR-6, 0xFF, 0x00, 0x00);            
//            strip.show();
//            delay(durationPerSegment);
//
//            delay(roundingError + timeToLeaveOn);
//
//            for(byte addr = RIGHT_EAR_SADDR; addr <= RIGHT_EAR_EADDR; addr++) {
//              strip.setPixelColor(addr, 0x00, 0x00, 0x00);
//            }
//
//            for(byte addr = LEFT_EAR_SADDR; addr <= LEFT_EAR_EADDR; addr++) {
//              strip.setPixelColor(addr, 0x00, 0x00, 0x00);
//            }
//            strip.show();
//
//            delay(timeToBlank);
//            // 1 = 7 (3, 3, 1)
//            // 2 = 9 (4, 3, 2)
//            // 3 = 6 (3, 2, 1)
//            // 4 = 9 (4, 3, 2)
//            // 5 = 7 (3, 3, 1)
//            
//            /*Serial.print("EQUAL Intensity "); Serial.println(equalizerParams.intensity);
//            Serial.print("EQUAL Start: "); Serial.println(equalizerParams.saddr);
//            Serial.print("EQUAL End: "); Serial.println(equalizerParams.eaddr);
//
//            byte numOfLeds = equalizerParams.eaddr - equalizerParams.saddr;
//
//            if (numOfLeds < 3) {
//                Serial.println("The number of LEDs in the Equalizer must be at least 3");
//                exit(-1);
//            }
//
//            uint16_t durationPerLed = equalizerParams.duration / numOfLeds;
//            uint16_t roundingError = equalizerParams.duration - (durationPerLed * numOfLeds);
//
//            Serial.print("Duration Per LED: "); Serial.println(durationPerLed);
//            Serial.print("Rounding Error: "); Serial.println(roundingError);
//
//            // Green is bottom 50%
//            // Yellow is Middle - Top 33.33%
//            // Red is top 16.67%
//            byte numOfRed = numOfLeds / 6;
//            if (numOfRed <= 0) {
//                numOfRed = 1;
//            }
//    
//            byte numOfYellow = numOfLeds / 3;
//            if (numOfYellow <= 0) {
//                numOfYellow = 1;
//            }
//    
//            byte numOfGreen = numOfLeds / 2;
//            if (numOfGreen <= 0) {
//                numOfGreen = 1;
//            }
//
//            byte leftOver = numOfLeds - (numOfGreen + numOfRed + numOfYellow);
//            numOfGreen += leftOver;
//
//            Serial.print("Num of Green: "); Serial.println(numOfGreen);
//            Serial.print("Num of Yellow: "); Serial.println(numOfYellow);
//            Serial.print("Num of Red: "); Serial.println(numOfRed);
//            
//            byte addrOffset = equalizerParams.saddr;
//            byte addrEnd = equalizerParams.saddr + numOfGreen - 1;
//            
//
//            for(byte addr = addrOffset; addr <= addrEnd; addr++) {
//              strip.setPixelColor(addr, 0x00, 0xFF, 0x00);
//              strip.show();
//              delay(durationPerLed);
//            }
//
//            addrOffset += numOfGreen;
//            addrEnd += numOfYellow;
//
//            for(byte addr = addrOffset; addr <= addrEnd; addr++) {
//              strip.setPixelColor(addr, 0xFF, 0xFF, 0x00);
//              strip.show();
//              delay(durationPerLed);
//            }
//            addrOffset += numOfYellow; addrEnd += numOfRed;
//
//            for(byte addr = addrOffset; addr <= addrEnd; addr++) {
//              strip.setPixelColor(addr, 0xFF, 0x00, 0x00);
//              strip.show();
//              delay(durationPerLed);
//            }
//
//            delay(roundingError);*/
//            break;
//          }
//          case FADE: {
//            FADE_PARAMS fadeParams;
//            memcpy_P(&fadeParams, operationStructOffset, sizeof(FADE_PARAMS));
//            /*Serial.print("FADE IN Duration: "); Serial.println(fadeParams.fadeTime);
//            Serial.print("FADE IN Brightness: "); Serial.println(fadeParams.brightness);
//            Serial.print("FADE IN Start: "); Serial.println(fadeParams.beam.saddr);
//            Serial.print("FADE IN End: "); Serial.println(fadeParams.beam.eaddr);
//            Serial.print("FADE IN R: "); Serial.println(fadeParams.beam.r);
//            Serial.print("FADE IN G: "); Serial.println(fadeParams.beam.g);
//            Serial.print("FADE IN B: "); Serial.println(fadeParams.beam.b);*/
//
//
//            byte stepIntervalInMs = 10;
//            int16_t numberOfSteps = fadeParams.fadeTime / stepIntervalInMs;
//            int16_t roundingErrorTime = fadeParams.fadeTime - (numberOfSteps * stepIntervalInMs);
//
//            int16_t brightnessDelta = fadeParams.ebrightness - fadeParams.sbrightness;
//            //Serial.print(brightnessDelta);
//            int16_t brightnessStep = brightnessDelta / numberOfSteps;
//
//            //Serial.print("Brightness will ramp from "); Serial.print(fadeParams.sbrightness); Serial.print(" to ");  Serial.print(fadeParams.ebrightness); Serial.print(" in ");  Serial.print(numberOfSteps); Serial.print(" steps with a brightness increment of "); Serial.println(brightnessStep);
//
//            for(int16_t i = 1; i <= numberOfSteps; i++) {
//              int16_t brightnessForStep = (brightnessStep * i) + (int16_t)fadeParams.sbrightness;
//              //Serial.print("Step brightness: "); Serial.println(brightnessForStep);
//
//              int16_t brightnessOffset = 255000 / brightnessForStep;
//              //Serial.print("Step Offset: "); Serial.println(brightnessOffset);
//
//              byte r = (((int32_t)fadeParams.beam.r) * 1000) / brightnessOffset;
//              byte g = (((int32_t)fadeParams.beam.g) * 1000) / brightnessOffset;
//              byte b = (((int32_t)fadeParams.beam.b) * 1000) / brightnessOffset;
//
//              /*Serial.print("FADE IN STEP R: "); Serial.println(r);
//              Serial.print("FADE IN STEP G: "); Serial.println(g);
//              Serial.print("FADE IN STEP B: "); Serial.println(b);*/
//              
//              for(uint16_t addr = fadeParams.beam.saddr; addr <= fadeParams.beam.eaddr; addr++) {
//                strip.setPixelColor(addr, r, g, b); 
//              }
//              strip.show();
//            }
//
//            // Account for any rounding errors and make sure the brightness matches the requested value at the requested time
//            delay(roundingErrorTime);
//
//            for(uint16_t addr = fadeParams.beam.saddr; addr <= fadeParams.beam.eaddr; addr++) {
//              strip.setPixelColor(addr, fadeParams.beam.r, fadeParams.beam.g, fadeParams.beam.b); 
//            }
//            
//            strip.show();
//            break;
//          }
         
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


// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
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

