#include "mp3_control.h"

SoftwareSerial MP3SoftwareSerial(11, 12); // RX, TX
static DFMiniMp3<SoftwareSerial, Mp3Notify> MP3(MP3SoftwareSerial);

uint8_t CURRENT_FOLDER;
uint8_t CURRENT_TRACK;
uint16_t NUMBER_OF_TRACKS;
uint8_t SELECT_COUNTER;

#define Is_playing()      (BUSY_PIN == HIGH)

void MP3_INIT(){
	MP3.begin();
	// wait some time until player is started
	delay(1500);
	Serial.print(2);
	MP3.setVolume(VolumeInit);
	MP3.setEq(DfMp3_Eq_Normal);

	SELECT_COUNTER = 0;
}

void START_NEW_TRACK()
{
	MP3.playRandomTrackFromAll();
}

void SELECT_ALBUM()
{
	uint8_t folder = 0;

	if(BUTTON == BUTTON_LL)
	{
		switch(BUTTON)
		{
		case bear:
			folder = 1;
			break;
		case sheep:
			folder = 1;
			break;
		case rabit:
			folder = 1;
			break;
		case mouse:
			folder = 1;
			break;
		case duck:
			folder = 1;
			break;
		default:
			folder = 0;
			/* wait for album to be selected */
		}
		SELECT_COUNTER++;
	}
	else
	{
		SELECT_COUNTER = 0;
		folder = 0;
	}

	if(SELECT_COUNTER > 50 && folder > 0)
	{
		CURRENT_FOLDER = folder;
		NUMBER_OF_TRACKS = MP3.getFolderTrackCount(CURRENT_FOLDER);
		CURRENT_TRACK = 0;
	}
}

void PLAY_ALBUM()
{
	if(Album_selected())
	{
		CURRENT_TRACK++;
		if(CURRENT_TRACK>NUMBER_OF_TRACKS)
		{
			CURRENT_TRACK = 1;
		}
		MP3.playFolderTrack(CURRENT_FOLDER,CURRENT_TRACK);
	}
}
