/*
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
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

//
// Hardware configuration
//

// Set up nRF24L01 radio on SPI bus plus pins 9 & 10 

RF24 radio(9,10);

//
// Topology
//

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
role_e role = role_pong_back;

void setup(void)
{
  //
  // Print preamble
  //

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
  //radio.setPayloadSize(4);

  //
  // Open pipes to other nodes for communication
  //

  // This simple sketch opens two pipes for these two nodes to communicate
  // back and forth.
  // Open 'our' pipe for writing
  // Open the 'other' pipe for reading, in position #1 (we can have up to 5 pipes open for reading)

  //if ( role == role_ping_out )
  {
    
    
    //void   openReadingPipe (uint8_t number, uint64_t address)
  //Open a pipe for reading. 
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

void loop(void)
{

        // Become the primary receiver (pong back)
//      role = role_pong_back;
      //radio.openWritingPipe(pipes[1]);
     // note this opens reading pipe. intitially (1,pipes(1)) is opened
     // this is not enough to start reading
      
  //    radio.openReadingPipe(2,pipes[2]);
    //  radio.openReadingPipe(3,pipes[3]);

  
  
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
      char dustDensity_temp;
      bool done = false;
      bool yes = false;
      int node1;
      while (!done)
      {
        // Fetch the payload, and see if this was the last one.
        done = radio.read( &dustDensity_temp, sizeof(char) );

        delay(1000);
       

        // Spew it
        printf(" Got payload %s...\n",dustDensity_temp);
        //printf(" Got payload %d...\n",node1);
         Serial.print(node1);
         

	// Delay just a little bit to let the other unit
	
  delay(20);
	
	// make the transition to receiver


float time_actual;

//time_actual=dustDensity_temp/100.00;
   

Serial.print("time_actual=");

Serial.println(dustDensity_temp);


//char str_dustDensity[10];
  //dtostrf(time_actual, 4, 2,str_dustDensity);  //4 is mininum width, 3 is precision; float value is copied onto buff

    printf("Now sending %s...",dustDensity_temp);
 

  
      }

      // First, stop listening so we can talk
      radio.stopListening();

      // Send the final one back.
      radio.write( &dustDensity_temp, sizeof(int) );
      printf("Sent response.\n\r");

      // Now, resume listening so we catch the next packets.
      radio.startListening();
    }
  }

  //
      


// vim:cin:ai:sts=2 sw=2 ft=cpp
