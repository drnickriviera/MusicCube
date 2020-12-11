#include "mp3_control.h"

SoftwareSerial MP3SoftwareSerial(11, 12); // RX, TX
static DFMiniMp3<SoftwareSerial, Mp3Notify> MP3(MP3SoftwareSerial);

void MP3_INIT(){
	MP3.begin();
	// Zwei Sekunden warten bis der DFPlayer Mini initialisiert ist
	delay(2000);
	Serial.print(2);
	MP3.setVolume(VolumeInit);
	MP3.setEq(DfMp3_Eq_Normal);
}

void START_NEW_TRACK()
{
	MP3.playRandomTrackFromAll();
}
