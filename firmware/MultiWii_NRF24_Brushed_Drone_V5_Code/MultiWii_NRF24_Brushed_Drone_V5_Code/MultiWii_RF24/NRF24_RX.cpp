
#include "Arduino.h"
#include "config.h"
#include "def.h"
#include "types.h"
#include "MultiWii.h"
#include <RF24.h>
#include "NRF24_RX.h"

#if defined(NRF24_RX)

int16_t nrf24_rcData[RC_CHANS];

// Single radio pipe address for the 2 nodes to communicate.
static const uint64_t pipe = 0xE8E8F0F0E1LL;  //Remember, SAME AS TRANSMITTER CODE

RF24 radio(7, 10); // CE, CSN

RF24Data MyData;
RF24AckPayload nrf24AckPayload;
extern RF24AckPayload nrf24AckPayload;

void resetRF24Data() 
{
  MyData.throttle = 0;
  MyData.yaw = 128;
  MyData.pitch = 128;
  MyData.roll = 128;

  //Same as the transmitter code
  MyData.AUX1 = 0;
  MyData.AUX2 = 0;
  MyData.switches = 0;
}

void resetRF24AckPayload() 
{
  nrf24AckPayload.lat = 0;
  nrf24AckPayload.lon = 0;
  nrf24AckPayload.heading = 0;
  nrf24AckPayload.pitch = 0;
  nrf24AckPayload.roll = 0;
  nrf24AckPayload.alt = 0;
  nrf24AckPayload.flags = 0;
}

void NRF24_Init() {

  resetRF24Data();
  resetRF24AckPayload();

  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  radio.setAutoAck(false);                    // Ensure autoACK is enabled
  //radio.enableAckPayload();

  radio.openReadingPipe(1,pipe);
  radio.startListening();  
}

void NRF24_Read_RC() {
  
  static unsigned long lastRecvTime = 0;

  nrf24AckPayload.lat = 35.62;
  nrf24AckPayload.lon = 139.68;
  nrf24AckPayload.heading = att.heading;
  nrf24AckPayload.pitch = att.angle[PITCH];
  nrf24AckPayload.roll = att.angle[ROLL];
  nrf24AckPayload.alt = alt.EstAlt;
  memcpy(&nrf24AckPayload.flags, &f, 1); // first byte of status flags
	
  unsigned long now = millis();
  while ( radio.available() ) {
    radio.writeAckPayload(1, &nrf24AckPayload, sizeof(RF24AckPayload));
    radio.read(&MyData, sizeof(RF24Data));
    lastRecvTime = now;
  }
  if ( now - lastRecvTime > 1000 ) {
    // signal lost?
    resetRF24Data();
  }
  
  nrf24_rcData[THROTTLE] =  map(MyData.throttle, 0, 255, 1000, 2000); //If your channels are inverted, reverse the map value. Example. From 1000 to 2000 ---> 2000 to 1000
  nrf24_rcData[ROLL] =      map(MyData.yaw,      0, 255, 2000, 1000);
  nrf24_rcData[PITCH] =     map(MyData.pitch,    0, 255, 1000, 2000);
  nrf24_rcData[YAW] =       map(MyData.roll,     0, 255, 2000, 1000);

  nrf24_rcData[AUX1] =       map(MyData.AUX1,     0, 1, 1000, 2000);
  nrf24_rcData[AUX2] =       map(MyData.AUX2,     0, 1, 1000, 2000);
  
}

#endif
