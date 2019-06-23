#define IO_USERNAME    "DaanWalder"
#define IO_KEY         "dd31949ad6074be0964360594905063b"

#define WIFI_SSID       "Daan"
#define WIFI_PASS       "daanwalder"

#include "AdafruitIO_WiFi.h"
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

#include <ESP8266WiFi.h>
#include <AdafruitIO.h>
#include <Adafruit_MQTT.h>
#include <ArduinoHttpClient.h>


#define FASTLED_ESP8266_RAW_PIN_ORDER
#include "FastLED.h"
#define NUM_LEDS 6
#define led 4
#define COLOR_ORDER RGB
CRGB leds[NUM_LEDS];
int maxMessages = 30;
int red = 255;
int green = 0;
int blue = 153;
int sick = 0;


AdafruitIO_Feed *SMS= io.feed("SMS");
AdafruitIO_Feed *Email= io.feed("Email");
AdafruitIO_Feed *Power= io.feed("Power");

void setup() {
  Serial.begin(115200);
  Serial.print("Connecting to Adafruit IO");
  io.connect();
  
  SMS->onMessage(handleSMS);
  Email->onMessage(handleEmail);
  Power->onMessage(powerSwitch);

  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println(io.statusText());

  FastLED.addLeds<WS2811, led, GRB>(leds, NUM_LEDS);
  showLED();
}

void loop() {
  io.run();
  sickness();
}

void powerSwitch (AdafruitIO_Data *data){
  Serial.print("received <- ");
  int Power = data->toInt();
  Serial.print(Power);
  if (Power == 1){
    //Turn On
    red = 255;
    green = 0;
    blue = 153;
    sick = 0;
    FastLED.setBrightness(255);
  } 
  if (Power == 2){
    //Turn OFF
    FastLED.setBrightness(0); 
  }
  if(Power == 3){
    //Reset
    red = 255;
    green = 0;
    blue = 153;
    sick = 0;
 
  }
  showLED();
}

void handleSMS(AdafruitIO_Data *data) {
  Serial.print("received <- ");
  int SMS = data->toInt();
  if (SMS == 1  ){
    //SMS Mama
    red = red -42.5;
    green = green + 5;
    blue = blue +17;
    Serial.print("received <- ");
    Serial.println("SMS Daan Walder");
    delay(1000);
  }
  if (SMS == 2  ){
    //SMS Vriendin
    red = red +42.5;
    green = green - 5;
    blue = blue -17;
    Serial.print("received <- ");
    Serial.println("SMS Docent");
    delay(1000);
  } 
  showLED();
} 

void handleEmail(AdafruitIO_Data *data) {
  Serial.print("received <- ");
  int Email = data->toInt();
  if (Email == 1  ){
    //Email Werk
    red = red -42.5;
    green = green + 5;
    blue = blue +17;
    Serial.print("received <- ");
    Serial.println("Email School");
    delay(1000);
    }
  if (Email == 2  ){
    //Email School
    red = red -42.5;
    green = green + 5;
    blue = blue +17;
    Serial.print("received <- ");
    Serial.println("Email Werk");
    delay(1000);
    }
    showLED();
 }

 void showLED(){
    for(int x = 0; x < NUM_LEDS; x++){
    leds[x] = CRGB(red,green,blue);
    }
    FastLED.show();
  }
