#include <Ethernet.h>
#include <EthernetUdp.h>
#include <DMXSerial.h>

#define UDP_TX_PACKET_MAX_SIZE 530
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 0, 151);

EthernetUDP Udp;

void setup() 
{
  DMXSerial.init(DMXController);
  //Ethernet.begin(mac, ip);
  Ethernet.begin(mac);
  Udp.begin(6454);
}

void loop() 
{
  int packetSize = Udp.parsePacket();
  if (packetSize) 
  {
    Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    
    analogWrite(6, (byte)packetBuffer[18]);
    DMXSerial.write(0, packetBuffer[18]);
  }
}
