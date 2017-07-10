// Which pin on the Arduino is connected to the NeoPixels?

#define DIGITALPINNUMBER  10
#define NUM_LEDS  16

// How many NeoPixels are attached to the Arduino?


#define _Debug 1
#define TestLed 1
#include <String.h>
#define CheckColorDelayTime 500
#define initDelayTime 2000
#define CommandDelay 100
int CheckColor[][3] = {
                          {255 , 255,255} ,
                          {255 , 0,0} ,
                          {0 , 255,0} ,
                          {0 , 0,255} ,
                          {255 , 128,64} ,
                          {255 , 255,0} ,
                          {0 , 255,255} ,
                          {255 , 0,255} ,
                          {255 , 255,255} ,
                          {255 , 128,0} ,
                          {255 , 128,128} ,
                          {128 , 255,255} ,
                          {128 , 128,192} ,
                          {0 , 128,255} ,
                          {255 , 0,128} ,
                          {128 , 64,64} ,
                          {0 , 0,0} } ;
                     
                          



