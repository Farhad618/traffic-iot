/*
  ESP32 Audible Traffic System
  Uses microSD card Module
  Uses MAX98357 I2S Amplifier Module
  Uses ESP32-audioI2S Library - https://github.com/schreibfaul1/ESP32-audioI2S
*/

// Include required libraries
#include "Arduino.h"
#include "Audio.h"
#include "SD.h"
#include "FS.h"
 
// microSD Card Reader connections
#define SD_CS          5
#define SPI_MOSI      23 
#define SPI_MISO      19
#define SPI_SCK       18
 
// I2S Connections
#define I2S_DOUT      22
#define I2S_BCLK      26
#define I2S_LRC       25

// Traffic LED Connections
#define LED_RED       17
#define LED_YELLOW    16
#define LED_GREEN     4
 
 // Create Audio object
Audio audio;
 
void setup() {

    //led pin mode setup
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_YELLOW, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    
    // Set microSD Card CS as OUTPUT and set HIGH
    pinMode(SD_CS, OUTPUT);      
    digitalWrite(SD_CS, HIGH); 
    
    // Initialize SPI bus for microSD Card
    SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
    
    // Start Serial Port
    Serial.begin(115200);
    
    // Start microSD Card
    if(!SD.begin(SD_CS))
    {
      Serial.println("Error accessing microSD card!");
      while(true); 
    }
    
    // Setup I2S 
    audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    
    // Set Volume
    audio.setVolume(15);
    
    // Open music file
    // audio.connecttoFS(SD,"/GO.mp3");

    // initially all led are off
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_GREEN, LOW);


    audio.connecttoFS(SD,"/STOP.mp3");
    
      


}
 
void loop()
{
  audio.loop(); // loop function only contains this line, use audio_eof_mp3() function instead of it
  // delay(2000);
}

void audio_eof_mp3(const char *info)
{
  // put anything from the original loop function
  static int i=0;
    // audio.connecttoFS(SD,"/WAIT.mp3");

    // teraffic light on off setup / audio
    // for red led
    if(i==0){
      delay(500);
      digitalWrite(LED_GREEN, LOW);  
      digitalWrite(LED_RED, HIGH);
      delay(500);
      audio.connecttoFS(SD,"/STOP.mp3");
      // delay(2000);    
    }


    // for yellow
    if(i==1){
      delay(500);
      digitalWrite(LED_RED, LOW);  
      digitalWrite(LED_YELLOW, HIGH);
      delay(500);
      audio.connecttoFS(SD,"/WAIT.mp3");
      // delay(2000);    
    }


    // fo green
    if(i==2){
      delay(500);
      digitalWrite(LED_YELLOW, LOW);  
      digitalWrite(LED_GREEN, HIGH);
      delay(500);
      audio.connecttoFS(SD,"/GO.mp3");
      // delay(2000);    
    }


    i++;
    if(i==3) i=0;
}

