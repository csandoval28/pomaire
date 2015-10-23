/*
 This code is for the gateway which recieves data as a string from different nodes(see "GettingStartedWDustSensorPipes_String.ino") via different 
 pipes using nRF24L01+ as the transciever and sends values to a database "pomaire" via GPRS using 
 Adafruit Fona SIM800L.  Note:  this library is different than that used from adafruit 
 download page and github.  this library works with Adafruit_FONA_Library-Master.zip in Google docs Factoria_Concepcion.

 
Libraries:
RF24-master--> example--> GettingStarted. 
AdafruitFonaLibrary-Master--> example-->FonaTest

// See website for nRF24L01+ code referance:
//http://maniacbug.github.io/RF24/classRF24.html#aa7e8523f86f9f8f20c274e0c89a5fd45

by Carlos Sandoval:cell(+1 720 9377819),email-carlos.sandoval@colorado.edu
and Tomas Pacheco(+56 99919887) 
last revised on 8/18/2015
  

****************************************************************************************************
* This is an example for our Adafruit FONA Cellular Module

  Designed specifically to work with the Adafruit FONA 
  ----> http://www.adafruit.com/products/1946
  ----> http://www.adafruit.com/products/1963

  These displays use TTL Serial to communicate, 2 pins are required to 
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ***************************************************

 
THIS CODE IS STILL IN PROGRESS!

Open up the serial console on the Arduino at 115200 baud to interact with FONA

Note that if you need to set a GPRS APN, username, and password scroll down to
the commented section below at the end of the setup() function.


  
*/



#include <SoftwareSerial.h>
#include "Adafruit_FONA.h"


#define FONA_RX 2
#define FONA_TX 3
#define FONA_RST 4

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"


// Set up nRF24L01 radio on SPI bus plus pins 9 & 10 
RF24 radio(9,10);


// Radio pipe addresses for the 4 nodes to communicate.
const uint64_t pipes[4] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL,0xF0F0F0F0AA,0xF0F0F0F066};


typedef enum { role_ping_out = 1, role_pong_back } role_e;
const char* role_friendly_name[] = { "invalid", "Ping out", "Pong back"};
role_e role = role_pong_back; // sets to reading mode


char replybuffer[255]; // don't know what this is for.

SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
Adafruit_FONA fona = Adafruit_FONA(&fonaSS, FONA_RST);

uint8_t readline(char *buff, uint8_t maxbuff, uint16_t timeout = 0);

void setup() {
  Serial.begin(57600);
  Serial.println(F("Inicializando...."));
  

  
  // See if the FONA is responding, note: fona is on different serial.
  if (! fona.begin(4800)) { 
    Serial.println(F("Couldn't find FONA"));
    while (1);
  }
  Serial.println(F("FONA is OK"));

  // Print SIM card IMEI number.
  char imei[15] = {0}; // MUST use a 16 character buffer for IMEI!
  uint8_t imeiLen = fona.getIMEI(imei);
  if (imeiLen > 0) {
    Serial.print("SIM card IMEI: "); Serial.println(imei);
  }

  
  fona.setGPRSNetworkSettings(F("bam.entelpcs.cl"), F(""), F(""));


// turn on fona


fona.enableGPRS(true);
 delay(5000);
  printf_begin();
  
 radio.begin();

  // optionally, increase the delay between retries & # of retries
  radio.setRetries(15,15);

  // optionally, reduce the payload size.  seems to
  // improve reliability
  //radio.setPayloadSize(8);

  //
  // Open pipes to other nodes for communication
  //

  // This simple sketch opens two pipes for these two nodes to communicate
  // back and forth.
  // Open 'our' pipe for writing
  // Open the 'other' pipe for reading, in position #1 (we can have up to 5 pipes open for reading)

  //if ( role == role_ping_out )
  {

  
  //Open a pipe for reading. what is important to change is uint64_t address to recieve from 
  // seperate nodes. 

     //eg.) void   openReadingPipe (uint8_t number, uint64_t address)
  
    //note: pipes[3] references 0xF0F0F0F0AA see above
    
    //radio.openWritingPipe(pipes[0]);
    radio.openReadingPipe(1,pipes[1]);
    radio.openReadingPipe(2,pipes[2]);
    radio.openReadingPipe(3,pipes[3]);



    
  }
  //else
  {
    //radio.openWritingPipe(pipes[1]);
    //radio.openReadingPipe(1,pipes[0]);
  }

  //
  // Start listening
  //

  radio.startListening();

  //
  // Dump the configuration of the rf unit for debugging
  //

  radio.printDetails();

 

}


void loop() {

 
 // Become the primary receiver (pong back)
    
      role = role_pong_back;
      
     radio.openReadingPipe(2,pipes[2]);
      radio.openReadingPipe(3,pipes[3]);


  
  
  //
  // Ping out role.  Repeatedly send the current time
  //

 
  //
  // Pong back role.  Receive each packet, dump it out, and send it back
  //

    // if there is data ready
    if ( radio.available() )
    {
      
      // Dump the payloads until we've gotten everything
      
      int data_str[32];
      bool done = false;
      while (!done)
      {
   //********************* Fetch the payload*******************************
   //and see if this was the last one.
        done = radio.read( &data_str, sizeof(data_str) );

        printf("Got payload %s...\n",data_str);

    
 //***************************** Post data to SERVER***********************************
      uint16_t statuscode;
      int16_t length;
   
  
 char url1[] = "pymecontrol.cl/littledevices";

  char url3[] = "/pomaire.php?";
 
  int lurl = strlen(url1) + strlen(url3) ;
  
 
  
 char url[lurl];// define url as character, perhaps a buffer, with length of "lurl"
  
  
//uncomment if need to send float number:
   //float to string this converts the dust density to a string.  this is needed becuase Due to some performance 
  //reasons %f is not included in the Arduino's implementation of sprintf()
 // char str_dustDensity[10];
  //dtostrf(dustDensity, 4, 2,str_dustDensity);  //4 is mininum width, 3 is precision; float value is copied onto buff
// in sprintf would insert str_dustDensity where data_str is. 
   
   sprintf(url,"%s%s%s",url1,url3,data_str);

  
  
// this takes number 23 and converts it to string don't know why this is here

   int value=23;
   
  char data2[get_int_len(value)+1];
  
  
//itoa function converts integer into null-terminated string. 
//It can convert negative numbers too. The standard definition of itoa function is give below:-
 
//char* itoa(int num, char* buffer, int base) 

  
  itoa(value,data2,10);
  
  
  
  int ldata = strlen(data2);

  char data[ldata];
  sprintf(data,"%s",data2);
  //Serial.println(data);

  Serial.print(F("http://"));
  Serial.println(url);
  Serial.print(data);

   Serial.println(F("****"));
   if (!fona.HTTP_POST_start(url, F("application/json"), (uint8_t *) data, strlen(data), &statuscode, (uint16_t *)&length)) {
     Serial.println("Failed!");
   }
       fona.HTTP_POST_end();
    
    delay(5000);
//    /*****************************************/
//      



	delay(20);
      }

    
      radio.startListening();
    }
  
  
  
  
  // flush input
  flushSerial();
  while (fona.available()) {
    Serial.write(fona.read());
  }
  
  

}

void flushSerial() {
    while (Serial.available()) 
    Serial.read();
}

char readBlocking() {
  while (!Serial.available());
  return Serial.read();
}
uint16_t readnumber() {
  uint16_t x = 0;
  char c;
  while (! isdigit(c = readBlocking())) {
    //Serial.print(c);
  }
  Serial.print(c);
  x = c - '0';
  while (isdigit(c = readBlocking())) {
    Serial.print(c);
    x *= 10;
    x += c - '0';
  }
  return x;
}
  
uint8_t readline(char *buff, uint8_t maxbuff, uint16_t timeout) {
  uint16_t buffidx = 0;
  boolean timeoutvalid = true;
  if (timeout == 0) timeoutvalid = false;
  
  while (true) {
    if (buffidx > maxbuff) {
      //Serial.println(F("SPACE"));
      break;
    }

    while(Serial.available()) {
      char c =  Serial.read();

      //Serial.print(c, HEX); Serial.print("#"); Serial.println(c);

      if (c == '\r') continue;
      if (c == 0xA) {
        if (buffidx == 0)   // the first 0x0A is ignored
          continue;
        
        timeout = 0;         // the second 0x0A is the end of the line
        timeoutvalid = true;
        break;
      }
      buff[buffidx] = c;
      buffidx++;
    }
    
    if (timeoutvalid && timeout == 0) {
      //Serial.println(F("TIMEOUT"));
      break;
    }
    delay(1);
  }
  buff[buffidx] = 0;  // null term
  return buffidx;
}

int get_int_len (int value){
  int l=1;
  while(value>9){ l++; value/=10; }
  return l;
}
