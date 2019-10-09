#include "SoftwareSerial.h" // Serial for Player
#include "DFRobotDFPlayerMini.h" // DFPlayer

SoftwareSerial SoftSerial(10, 11); // RX, TX
DFRobotDFPlayerMini DFPlayer; // Player

// Initialize player
void setupPlayer()
{
  SoftSerial.begin(9600);
  if (!DFPlayer.begin(SoftSerial))
  { // Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    //@todo flash led to indicate error condition
    while (true)
      ;
  }
  Serial.println(F("DFPlayer Mini online."));

  DFPlayer.setTimeOut(500); // Set serial communication time out 500ms
  DFPlayer.volume(25);      // Set volume value (0~30).
  DFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  DFPlayer.outputDevice(DFPLAYER_DEVICE_SD); // Set device we use SD as default
  //DFPlayer.play(1);
}
