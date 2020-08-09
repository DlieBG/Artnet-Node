#include <Ethernet.h>
#include <EthernetUdp.h>
#include <DmxSimple.h>

#define UDP_TX_PACKET_MAX_SIZE 530
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 0, 151);

EthernetUDP Udp;

//uint8_t dmx[512];

byte universe = 1;

void setup() 
{
  //Ethernet.begin(mac, ip);
  Ethernet.begin(mac);
  Udp.begin(6454);
  DmxSimple.usePin(3);
}

void loop() 
{
  int packetSize = Udp.parsePacket();
  if (packetSize) 
  {
    Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    if((byte)packetBuffer[14]==universe)
    {
      //for(int i=0; i<512; i++)
        //dmx[i]=(uint8_t)(byte)packetBuffer[18+i];
  
      for(int i=1; i<=512; i++)
        DmxSimple.write(i, (uint8_t)(byte)packetBuffer[18+i]);
        
      analogWrite(6, (uint8_t)(byte)packetBuffer[18]);
    }
  }
}
