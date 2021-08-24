#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <DHT.h>;

//Constants
#define DHTPIN 7     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

int chk;
float hum1;  //Stores humidity value
float temp1; //Stores temperature value

RF24 radio(9, 10); // CE, CSN         
const byte address[6] = "00001";     //Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side.
int button_pin = 2;
boolean button_state = 0;
void setup() {

  
  Serial.begin(9600);
  dht.begin();
  
pinMode(button_pin, INPUT);
radio.begin();                  //Starting the Wireless communication
radio.openWritingPipe(address); //Setting the address where we will send the data
radio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
radio.stopListening();          //This sets the module as transmitter
}
void loop()
{


  //Read data and store it to variables hum and temp
   


const float temp =  dht.readTemperature();
const float hum = dht.readHumidity();
radio.write(&temp, sizeof(temp));                  //Sending the message to receiver

radio.write(&hum, sizeof(hum));  

}
