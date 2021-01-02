#include "MusicCube.h"


/***************************************
* MusicCube state machine definitions    *
***************************************/
/* DEFINES */
typedef enum musiccube_states_e {
	SelectAlbum = 0,
	PlayAlbum
} musiccube_states_t;

musiccube_states_t MUSICCUBE_STATE = SelectAlbum;
musiccube_states_t MUSICCUBE_STATE_LL = SelectAlbum;

#define Set_cube_state(x)       (MUSICCUBE_STATE = (x))
#define Get_cube_state()         MUSICCUBE_STATE
#define Update_cube_state_ll()  (MUSICCUBE_STATE_LL = MUSICCUBE_STATE)
#define Get_cube_state_ll()      MUSICCUBE_STATE_LL

/***************************************/


void setup()
{

  Serial.begin(9600);
  /********************************
  * Init Button
  ********************************/
  INIT_BUTTON();

  /********************************
  * Init MP3
  ********************************/
  MP3_INIT();

  /* select album */
  Set_cube_state(SelectAlbum);
}


void INPUT_PROCESSING()
{
  // Check if a button has been pushed
  BUTTON_READ();
}

void STATE_MACHINE()
{
  static uint8_t count = 0;

  switch(Get_cube_state())
  {
  case SelectAlbum:
	  SELECT_ALBUM();
	  break;
  case PlayAlbum:
	  break;
  default:
    // Should never occur so restart
    Set_cube_state(SelectAlbum);
    //NOTIFICATION(Failed);
    break;
  }
}

void STATE_TRANSITIONS(){
	switch(Get_cube_state())
	  {
	  case SelectAlbum:
		  if(Album_selected())
		  {
			  Set_cube_state(PlayAlbum);
			  PLAY_ALBUM();
		  }
		  break;
	  case PlayAlbum:
		  if(Button_toggle())
		  {
			  PLAY_ALBUM();
		  }
		  break;
	  default:
		// Should never occur so restart
		Set_cube_state(SelectAlbum);
		break;
	  }
}

void loop()
{
  if((millis() - START_TIME) >= Task_length)
  {
    START_TIME = micros();

    INPUT_PROCESSING();

    STATE_MACHINE();

    STATE_TRANSITIONS();

    Update_cube_state_ll();
  }
}
