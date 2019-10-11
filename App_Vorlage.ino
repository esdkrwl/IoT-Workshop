/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP8266 chip.

  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right ESP8266 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
//Besonderheiten der FastLED Bibliothek im Zusammenspiel mit ESP8266
#define FASTLED_ALLOW_INTERRUPTS 0
#define FASTLED_ESP8266_RAW_PIN_ORDER

#include "FastLED.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//Pin, an welchem die LED angeschlossen ist, festlegen
#define DATA_PIN    D3
//Anzahl der angeschlossenen LEDs
#define NUM_LEDS    8
//LED Array mit NUM_LEDS Elementen
CRGB leds[NUM_LEDS];


// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "3c5a5c6001d6487e9ba05d64411b0c2d";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Lernlabor-Gast";
char pass[] = "Prometheus@DDI";

//Initialwerte für die LED
int r = 255;
int g = 0;
int b = 0;
int buttonState = 0;

//An/Aus Schalter
BLYNK_WRITE(V0){
  Blynk.setProperty(V1, "onLabel", "AN");
  Blynk.setProperty(V1, "offLabel", "AUS");
  buttonState = param.asInt(); 

    if (buttonState){
      for (int i = 0; i < NUM_LEDS; i++){
        leds[i].red = r;
        leds[i].green = g;
        leds[i].blue = b;
    }
    FastLED.show();
 }

  else{
    for (int i = 0; i < NUM_LEDS; i++){
      leds[i].red = 0;
      leds[i].green = 0;
      leds[i].blue = 0;
     } 
     FastLED.show(); 
  }
}

// Farbauswahl
BLYNK_WRITE(V1)
{
  r = param[0].asInt();
  g = param[1].asInt();
  b = param[2].asInt();
 
  if (buttonState){
    for (int i = 0; i < NUM_LEDS; i++){
      leds[i].red = r;
      leds[i].green = g;
      leds[i].blue = b;
    }
   FastLED.show();
  }
}

BLYNK_CONNECTED() {
  Blynk.syncVirtual(V0);
  Blynk.syncVirtual(V1);
}

void setup()
{
  //warte 3 Sekunden bevor es los geht
  delay(3000);
  Serial.begin(115200);
  //Init
  FastLED.addLeds<WS2811,DATA_PIN,GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //Setze Helligkeit der LEDs auf 50 von max 255
  FastLED.setBrightness(50);
  //maximalen Strom auf 500 mA beschränken
  FastLED.setMaxPowerInVoltsAndMilliamps(5,500);

  Blynk.begin(auth, ssid, pass, "iot.informatik.uni-oldenburg.de", 8080);
}

void loop()
{
  Blynk.run();
}

