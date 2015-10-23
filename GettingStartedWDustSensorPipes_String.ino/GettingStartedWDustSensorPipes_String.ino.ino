/*
 This code sends dust sensor data to a gateway(see "FONA_GPRS_VARIABLE_RF_Carlos_Pipes_String")
 as a string using nRF24LO1+.  The node also utilizes a sleep time to conserve energy  and for 
 each node the user must change the pipe address being used. 

Utilizes RF24-master--> examle GettingStarted.

 
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

/**
 * Example for Getting Started with nRF24L01+ radios. 
 *
 * This is an example of how to use the RF24 class.  Write this sketch to two 
 * different nodes.  Put one of the nodes into 'transmit' mode by connecting 
 * with the serial monitor and sending a 'T'.  The ping node sends the current 
 * time to the pong node, which responds by sending the value back.  The ping 
 * node can then see how long the whole cycle took.
 */

#include <SPI.h>
#include <Sleep_n0m1.h>

Sleep sleep;
unsigned long sleepTime; //how long you want the arduino to sleep



#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"


//Define Variables
int dustPin = A0;
int dustVal = 0;
int fan = 5; // digital pin 5
int ledPower=7; // digital pin 7
int delayTime=280;
int delayTime2=40;
float offTime=9680;

float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;
int dustDensity_temp=0;
 float temp=0;
     float hum=0;

     int node=2;


//
// Hardware configuration
//

// Set up nRF24L01 radio on SPI bus plus pins 9=rx & 10=tx 

RF24 radio(9,10);

//
// Topology
//

// Radio pipe addresses for the 2 nodes to communicate.
//const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes[4] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL,0xF0F0F0F0AA,0xF0F0F0F066};


//
// Role management
//
// Set up role.  This sketch uses the same software for all the nodes
// in this system.  Doing so greatly simplifies testing.  
//

// The various roles supported by this sketch
typedef enum { role_ping_out = 1, role_pong_back } role_e;

// The debug-friendly names of those roles
const char* role_friendly_name[] = { "invalid", "Ping out", "Pong back"};

// The role of the current running sketch
// Note:  role_ping_out to avoid Trasnmmitting with 'T'.  This sets role to Transmitting  
//role-e role=role_pong_back;  // default Reading Mode
role_e role = role_ping_out; // Transmitting mode

void setup(void)
{



  
  // Print preamble
  //



// Sensor Set up
Serial.begin(115200);

 sleepTime = 5000; //set sleep time in ms, max sleep time is 49.7 days


pinMode(ledPower,OUTPUT);
pinMode(fan,OUTPUT);
pinMode(ledPower, OUTPUT);
 
  Serial.begin(57600);
  
  
  printf_begin();
  printf("\n\rRF24/examples/GettingStarted/\n\r");
  printf("ROLE: %s\n\r",role_friendly_name[role]);
  printf("*** PRESS 'T' to begin transmitting to the other node\n\r");

  //
  // Setup and configure rf radio
  //

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
    //radio.openWritingPipe(pipes[0]);
    radio.openReadingPipe(1,pipes[1]);
  }
  //else
  {
  
      radio.openWritingPipe(pipes[2]);// com 13
  
   // radio.openWritingPipe(pipes[3]); // com 16
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

void loop(void)
{
  //
  // Ping out role.  Repeatedly send the current time


  

  if (role == role_ping_out)
  {
    // First, stop listening so we can talk.
    radio.stopListening();


    
    // Take the time, and send it.  This will block until complete

 // *****************************First cycle*******************************
   digitalWrite(ledPower,LOW); // power on the LED
  delayMicroseconds(delayTime);
  
  voMeasured = analogRead(dustPin); // read the dust value
  
  delayMicroseconds(delayTime2);
  digitalWrite(ledPower,HIGH); // turn the LED off
  delayMicroseconds(offTime);
  delay(1000);
  
  //****************************Measuring cycle***************************
 
 
 // Fan controller 
 analogWrite(fan, 100);
  delay(2000);
  analogWrite(fan,0);
  delay(1000);
  
   digitalWrite(ledPower,LOW); // power on the LED
  delayMicroseconds(delayTime); 

   //Meausre dust 
float voMeasured = analogRead(dustPin);
  
  delayMicroseconds(delayTime2);
  digitalWrite(ledPower,HIGH); // turn the LED off
  delayMicroseconds(offTime);
  
  // 0 - 5V mapped to 0 - 1023 integer values
  // recover voltage
  float calcVoltage = voMeasured * (5.00 / 1024.00);
  
  // linear eqaution taken from http://www.howmuchsnow.com/arduino/airquality/
  // Chris Nafis (c) 2012
  float dustDensity = (0.17 * calcVoltage - 0.1)*1000;

// Multiply by 100 because cant send float numbers as of yet
// Will later divide by 100 to get original number back.

//dustDensity_temp=dustDensity*100;
  
  Serial.print("Senal(0-1023): ");
 Serial.print(voMeasured);
  
  Serial.print(" - Voltaje: ");
  Serial.println(calcVoltage);  

   Serial.print(" - Densidad de polvo (ug/m3): ");
  Serial.println(dustDensity); // unit: ug/m3


 
 
 //*********************Send Data********************************8
    
    // Take the time, and send it.  This will block until complete
   
    // convert data to string
    char str_dustDensity[5];
  dtostrf(dustDensity,4,1,str_dustDensity);  //4 is mininum width, 3 is precision; float value is copied onto buff

//char vo_str[5];
  //dtostrf(calcVoltage, 4, 2,vo_str);  //4 is mininum width, 3 is precision; float value is copied onto buff

char temp_str[4];
  dtostrf(temp,3,1,temp_str);  //4 is mininum width, 3 is precision; float value is copied onto buff

char hum_str[3];
  dtostrf(hum,3,1,hum_str);  //4 is mininum width, 3 is precision; float value is copied onto buff
char *node="id=1";

int ldata=strlen(str_dustDensity)+strlen(hum_str)+strlen(temp_str)+strlen(node); //strlen(vo_str)
char data_str[60];

sprintf(data_str,"%s&polvo=%s&temp=%s&hum=%s",node,str_dustDensity,temp_str,hum_str);

    printf("Now sending %s...",data_str);
    bool ok = radio.write( &data_str, sizeof(data_str) );
    
    
    if (ok)
      printf("ok...");
    else
      printf("failed.\n\r");

    // Now, continue listening
    radio.startListening();

    // Wait here until we get a response, or timeout (250ms) // here millis() is not the time being sent in example it is for timout purposes
    unsigned long started_waiting_at = millis();
    bool timeout = false;
    while ( ! radio.available() && ! timeout )
      if (millis() - started_waiting_at > 200 )
        timeout = true;

    // Describe the results
    if ( timeout )
    {
      printf("Failed, response timed out.\n\r");
    }
    else
    {
      // Grab the response, compare, and send to debugging spew
      char str_dustDensity;
      radio.read( &str_dustDensity, sizeof(char) );

      // Spew it
      printf("Got response %s, round-trip delay: %s\n\r",str_dustDensity,millis()-str_dustDensity);
    }

    // Try again 1s later
    delay(10000);
  }

  //********************************************************************************
  

  Serial.print("sleeping for ");
  Serial.println(sleepTime); 
  delay(100); //delay to allow serial to fully print before sleep
    
  sleep.pwrDownMode(); //set sleep mode
  sleep.sleepDelay(sleepTime); //sleep for: sleepTime

  
}
// vim:cin:ai:sts=2 sw=2 ft=cpp
