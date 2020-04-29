#include <Ethernet.h>
#include <SPI.h>

const int pinIn = 2;
const int pinOut = 3;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 1, 123 }; //Het IP adres voor de Arduino (zelf kiezen)
byte server[] = { 192, 168, 1, 2 }; //Het IP adres van de server
int port = 9000;

EthernetClient client;

void setup()
{
  Ethernet.begin(mac, ip);
  Serial.begin(9600);
}

void loop()
{
  if (!client.connected()) 
  {
    //Probeer een verbinding te maken met de server.
    client.connect(server, port);
  }
  else
  {
    //We zijn verbonden.
    //Stuur iets naar de server.
    bool statusPinIn = digitalRead(pinIn);
    client.print("pinIn:");
    client.println(statusPinIn);

    //Wacht 1000ms op een antwoord van de server.
    delay(1000);
    
    //Lees het antwoord van de server.
    String content = "";
    char character;
    while (client.available()) 
    {
      character = Serial.read();
      content.concat(character);
      delay(20);
    }
    content.replace("\r","");
    content.replace("\n","");
    content.trim();
    
    if (content == "abc") 
    {
      digitalWrite(pinOut, HIGH);
    }
    
  }
}
