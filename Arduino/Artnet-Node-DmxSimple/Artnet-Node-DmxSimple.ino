#include <Ethernet.h>
#include <EthernetUdp.h>
#include <DmxSimple.h>
#include <EEPROM.h>

#define UDP_TX_PACKET_MAX_SIZE 530
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

EthernetUDP Udp;

byte universe = 1;
int stopper = 0;

void setup() 
{
  Serial.begin(9600);
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("Start");
  
  setupEEPROM();
  
  Udp.begin(6454);
  DmxSimple.usePin(3);
}

void loop() 
{
  receiveArtnet();
  receiveSerial();
}

void setupEEPROM()
{
  universe = (byte)EEPROM.read(0);
  Serial.print("Universum: ");
  Serial.println(universe);
  
  if(EEPROM.read(1)==1)//dhcp
    Ethernet.begin(mac);
  else
  {
    IPAddress ip(EEPROM.read(2), EEPROM.read(3), EEPROM.read(4), EEPROM.read(5));
    Ethernet.begin(mac, ip);
  }
  Serial.print("IP Addresse: ");
  Serial.println(Ethernet.localIP());

  stopper = EEPROM.read(6);
  Serial.print("Mode: ");
  Serial.println(stopper);
}

void receiveArtnet()
{
  int packetSize = Udp.parsePacket();
  if (packetSize) 
  {
    Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    if((byte)packetBuffer[14]==universe)
    {  
      if(stopper == 0)
      {
        //Raw
        for(int i=0; i<512; i++)
          DmxSimple.write(i+1, (uint8_t)(byte)packetBuffer[18+i]);
        analogWrite(6, (uint8_t)(byte)packetBuffer[18]);
      }
      else
      {
        if((uint8_t)(byte)packetBuffer[17+stopper]!=0||(uint8_t)(byte)packetBuffer[18+stopper]!=100)
        {
          //Break durch ETC Trick
          
        }
        else
        {
          //Ausgabe mit ETC Trick
          for(int i=0; i<512; i++)
            DmxSimple.write(i+1, (uint8_t)(byte)packetBuffer[18+i]);
          analogWrite(6, (uint8_t)(byte)packetBuffer[18]);
        }
      }
      
    }
  }
}

void receiveSerial()
{
  if(Serial.available())
  {
    String serial = Serial.readString();
    if(serial[0]=='u')//universe change
    {
      serial.remove(0,1);
      universe=(byte)serial.toInt();
      EEPROM.write(0, universe);
      Serial.println("Universum geändert!");
    }
    
    if(serial[0]=='i')//ip change
    {
      serial.remove(0,1);
      if(serial[0]=='d')
      {
        EEPROM.write(1, 1);
        Serial.println("DHCP aktiviert!");
      }
      else
      {
        EEPROM.write(1, 0);
        EEPROM.write(2, split(serial, '.', 0).toInt());
        EEPROM.write(3, split(serial, '.', 1).toInt());
        EEPROM.write(4, split(serial, '.', 2).toInt());
        EEPROM.write(5, split(serial, '.', 3).toInt());
        Serial.println("IP geändert!");
      }
    }

    if(serial[0]=='e')//ETC Trick
    {
      serial.remove(0,1);
      stopper = serial.toInt();
      EEPROM.write(6, stopper);
      Serial.println("ETC Trick aktiviert!");
    }
  }
}

String split(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}
