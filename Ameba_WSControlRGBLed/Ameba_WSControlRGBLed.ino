#include "Pinset.h"
#include <WiFi.h>

char ssid[] = "IOT";      // your network SSID (name)
char pass[] = "0123456789";     // your network password

uint8_t MacData[6];
IPAddress  Meip ,Megateway ,Mesubnet ;
String MacAddress ;
int status = WL_IDLE_STATUS;

#include "ws2812b.h"

ws2812b ledstrip = ws2812b(DIGITALPINNUMBER , NUM_LEDS);

byte RedValue = 0, GreenValue = 0, BlueValue = 0;
String ReadStr = "" ;
int delayval = 500; // delay for half a second
WiFiServer server(8080);
 char c ;
  int count = 0 ;
  boolean readok = false ;
  unsigned long strtime ;
  

void setup() {
  Serial.begin(9600) ;
   ledstrip.begin(); // This initializes the NeoPixel library.  
   DebugMsgln("Program Start Here") ;
    MacAddress = GetWifiMac() ; // get MacAddress
    ShowMac() ;       //Show Mac Address
    initializeWiFi();
      server.begin();
    printWifiData() ;
   
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
       Serial.println("Now Enter Listening Mode"); 
}



void loop() {
 
  WiFiClient client = server.available();
  readok = false ;
  if (client)
  {
    Serial.println("Now Someone Access WebServer");

    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected())
      {
          if (client.available())
          {
              Serial.println("something readrable");
            c = client.read();
            // give the web browser time to receive the data
            if (c == '@')
            {
                      Serial.println("read head happen");
                  ReadStr = ""  ;
                  strtime =   millis() ;
                  count = 0 ;
                    while(true)     // for enter read string
                    {
                      
                  if (client.available())
                       {
                            c = client.read();
                              if (c == '#')
                                  {
                                    readok = true ;
                                    break ;                                     
                                  }   //  read ending  symbol
                                  else
                                  {
                                    ReadStr.concat(c) ;
                                    Serial.println(ReadStr) ;
                                    count ++ ;
                                  }
                       }    //end of client.available() 

                                 if ((millis() - strtime ) > MaxReceiveWaitTime)
                                {
                                    readok = false ;
                                    break ;
                                }     //judge too long time to waiting
                                if (count > 15)
                                {
                                    readok = false ;
                                    break ;
                                }   //judge read too more char

                    }   //end of read command string


            }   //(c == '@')  judge read starting symbol
                  
          }   //(client.available())  some data incoming
    
        // close the connection:
        if (readok)
            {
              Serial.println("read string ok");
              Serial.println(ReadStr) ;
                if (DecodeString(ReadStr,&RedValue,&GreenValue,&BlueValue) )
                 {
                      DebugMsgln("Change RGB Led Color") ;
                      ChangeBulbColor(RedValue,GreenValue,BlueValue) ;
                 }
              readok = false ;
              ReadStr = "" ;
            }
       // Serial.println("client disonnected");
    }   //end of while (client.connected())

  }   //  end of  if (client)

       delay(800) ;
  
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
                    Serial.print("check string:(") ;
                    Serial.print(INPStr) ;
                         Serial.print(")\n") ;

      int i = 0 ;
      int strsize = INPStr.length();

                      *r = byte(INPStr.substring(i,i+3).toInt()) ;
                      *g = byte(INPStr.substring(i+3,i+3+3).toInt() ) ;
                      *b = byte(INPStr.substring(i+3+3,i+3+3+3).toInt() ) ;
                       Serial.print("convert into :(") ;
                        Serial.print(*r) ;
                         Serial.print("/") ;
                        Serial.print(*g) ;
                         Serial.print("/") ;
                        Serial.print(*b) ;
                         Serial.print(")\n") ;
                       return true ;

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

void ShowMac()
{
  
     Serial.print("MAC:");
     Serial.print(MacAddress);
     Serial.print("\n");

}




String GetWifiMac()
{
   String tt ;
    String t1,t2,t3,t4,t5,t6 ;
    WiFi.status();    //this method must be used for get MAC
  WiFi.macAddress(MacData);
  
  Serial.print("Mac:");
   Serial.print(MacData[0],HEX) ;
   Serial.print("/");
   Serial.print(MacData[1],HEX) ;
   Serial.print("/");
   Serial.print(MacData[2],HEX) ;
   Serial.print("/");
   Serial.print(MacData[3],HEX) ;
   Serial.print("/");
   Serial.print(MacData[4],HEX) ;
   Serial.print("/");
   Serial.print(MacData[5],HEX) ;
   Serial.print("~");
   
   t1 = print2HEX((int)MacData[0]);
   t2 = print2HEX((int)MacData[1]);
   t3 = print2HEX((int)MacData[2]);
   t4 = print2HEX((int)MacData[3]);
   t5 = print2HEX((int)MacData[4]);
   t6 = print2HEX((int)MacData[5]);
 tt = (t1+t2+t3+t4+t5+t6) ;
Serial.print(tt);
Serial.print("\n");
  
  return tt ;
}
String  print2HEX(int number) {
  String ttt ;
  if (number >= 0 && number < 16)
  {
    ttt = String("0") + String(number,HEX);
  }
  else
  {
      ttt = String(number,HEX);
  }
  return ttt ;
}





void printWifiData() 
{
  // print your WiFi shield's IP address:
  Meip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(Meip);
  Serial.print("\n");

  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  Serial.print(mac[5], HEX);
  Serial.print(":");
  Serial.print(mac[4], HEX);
  Serial.print(":");
  Serial.print(mac[3], HEX);
  Serial.print(":");
  Serial.print(mac[2], HEX);
  Serial.print(":");
  Serial.print(mac[1], HEX);
  Serial.print(":");
  Serial.println(mac[0], HEX);

  // print your subnet mask:
  Mesubnet = WiFi.subnetMask();
  Serial.print("NetMask: ");
  Serial.println(Mesubnet);

  // print your gateway address:
  Megateway = WiFi.gatewayIP();
  Serial.print("Gateway: ");
  Serial.println(Megateway);
}

void ShowInternetStatus()
{
    
        if (WiFi.status())
          {
               Meip = WiFi.localIP();
               Serial.print("Get IP is:");
               Serial.print(Meip);
               Serial.print("\n");
              
          }
          else
          {
                       Serial.print("DisConnected:");
                       Serial.print("\n");
          }

}

void initializeWiFi() {
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
  //   status = WiFi.begin(ssid);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.print("\n Success to connect AP:") ;
  Serial.print(ssid) ;
  Serial.print("\n") ;
  
}



