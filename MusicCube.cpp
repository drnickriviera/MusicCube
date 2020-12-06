#include "MusicCube.h"


/***************************************
* MusicCube state machine definitions    *
***************************************/
/* DEFINES */
typedef enum musiccube_states_e {
	WaitForNewInput = 0,
	StartNewSong
} musiccube_states_t;

musiccube_states_t MUSICCUBE_STATE = WaitForNewInput;
musiccube_states_t MUSICCUBE_STATE_LL = WaitForNewInput;

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

  /* init state machine */
  Set_cube_state(WaitForNewInput);
}


void INPUT_PROCESSING()
{
  // Check if a button has been pushed
  BUTTON_READ();
}

void STATE_MACHINE()
{
  switch(Get_cube_state())
  {
  case WaitForNewInput:
	  break;
  case StartNewSong:
	  START_NEW_TRACK();
	  break;
  default:
    // Should never occur so restart
    Set_cube_state(WaitForNewInput);
    //NOTIFICATION(Failed);
    break;
  }
}

void STATE_TRANSITIONS(){

	switch(Get_cube_state())
	  {
	  case WaitForNewInput:
		  if(Is_button_repressed())
		  {
			  Set_cube_state(StartNewSong);
		  }
		  break;
	  case StartNewSong:
		  break;
	  default:
		// Should never occur so restart
		Set_cube_state(WaitForNewInput);
		break;
	  }
}

void loop()
{
  if((micros() - START_TIME) >= Task_length)
  {
    START_TIME = micros();

    INPUT_PROCESSING();

    STATE_TRANSITIONS();

    STATE_MACHINE();

    Update_cube_state_ll();
  }
}
