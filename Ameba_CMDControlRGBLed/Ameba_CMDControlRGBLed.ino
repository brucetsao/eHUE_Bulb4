#include "Pinset.h"

#include "ws2812b.h"

ws2812b ledstrip = ws2812b(DIGITALPINNUMBER , NUM_LEDS);

byte RedValue = 0, GreenValue = 0, BlueValue = 0;
String ReadStr = "" ;
int delayval = 500; // delay for half a second

void setup() {
  Serial.begin(9600) ;
   ledstrip.begin(); // This initializes the NeoPixel library.  
   DebugMsgln("Program Start Here") ;
  
          DebugMsgln("init LED") ;
      ChangeBulbColor(RedValue,GreenValue,BlueValue) ;
      DebugMsgln("Turn off LED") ;
      if (TestLed ==  1)
          {
               CheckLed() ;
                 DebugMsgln("Check LED") ;
                  ChangeBulbColor(RedValue,GreenValue,BlueValue) ;
                  DebugMsgln("Turn off LED") ;
          }
 

    
 
     delay(initDelayTime) ;   //wait 2 seconds
     
}



void loop() {
 
  if (Serial.available() >0)
  {
    ReadStr = Serial.readStringUntil(0x23) ;    // read char @
     //  Serial.read() ;
      Serial.print("ReadString is :(") ;
       Serial.print(ReadStr) ;
       Serial.print(")\n") ;
        if (DecodeString(ReadStr,&RedValue,&GreenValue,&BlueValue) )
           {
            Serial.println("Change RGB Led Color") ;
            ChangeBulbColor(RedValue,GreenValue,BlueValue) ;
           }
  }
  
}
void ChangeBulbColor(int r,int g,int b)
{
      // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
   for(int i=0;i<NUM_LEDS;i++)
   {
        // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
        ledstrip.setPixelColor(i,r,g,b);
        //pixels.setPixelColor(i, pixels.Color(r,g,b)); // Moderately bright green color.
      // delay(delayval); // Delay for a period of time (in milliseconds).
  }
         ledstrip.show(); // This sends the updated pixel color to the hardware.
 
}
boolean DecodeString(String INPStr, byte *r, byte *g , byte *b) 
{
                    Serial.print("check sgtring:(") ;
                    Serial.print(INPStr) ;
                         Serial.print(")\n") ;

      int i = 0 ;
      int strsize = INPStr.length();
      for(i = 0 ; i <strsize ;i++)
          {
                    Serial.print(i) ;
                    Serial.print(":(") ;
                         Serial.print(INPStr.substring(i,i+1)) ;
                    Serial.print(")\n") ;

              if (INPStr.substring(i,i+1) == "@")
                  {
                    Serial.print("find @ at :(") ;
                    Serial.print(i) ;
                         Serial.print("/") ;
                              Serial.print(strsize-i-1) ;
                         Serial.print("/") ;
                              Serial.print(INPStr.substring(i+1,strsize)) ;
                    Serial.print(")\n") ;
                      *r = byte(INPStr.substring(i+1,i+1+3).toInt()) ;
                      *g = byte(INPStr.substring(i+1+3,i+1+3+3).toInt() ) ;
                      *b = byte(INPStr.substring(i+1+3+3,i+1+3+3+3).toInt() ) ;
                       Serial.print("convert into :(") ;
                        Serial.print(*r) ;
                         Serial.print("/") ;
                        Serial.print(*g) ;
                         Serial.print("/") ;
                        Serial.print(*b) ;
                         Serial.print(")\n") ;
                            
                      return true ;
                  }
          }
    return false ;

}

void CheckLed()
{
     for(int i = 0 ; i <16; i++)
        {
              ChangeBulbColor(CheckColor[i][0],CheckColor[i][1],CheckColor[i][2]) ;
              delay(CheckColorDelayTime) ;
        }
}
void DebugMsg(String msg)
{
    if (_Debug != 0)
        {
          Serial.print(msg) ;
        }
   
}
void DebugMsgln(String msg)
{
    if (_Debug != 0)
        {
          Serial.println(msg) ;
        }
   
}




