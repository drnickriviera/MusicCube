/***************************************
* Button  definitions                  *
***************************************/

#ifndef button_control_h
#define button_control_h
/***************************************/

#include "FirstInclude.h"

/* DEFINES */
typedef enum button_states_e {
	bear = 0,
	sheep,
	rabit,
	mouse,
	duck,
	dont_know
} button_states_t;

typedef enum button_action_e {
	selected = 0,
	toggle,
	toggle_cool_down,
	toggle_finished
} button_action_t;


extern button_states_t BUTTON;
extern button_states_t BUTTON_LL;
extern bool BUSY_PIN;
extern button_action_t BUTTON_TOGGLE;

/* GLOBAL VARIABLES */
#define Button_toggle()              (BUTTON_TOGGLE == toggle_finished)

/* set digital ports */
#define Bear_button_pin  2
#define Sheep_button_pin 3
#define Rabit_button_pin 4
#define Mouse_button_pin 5
#define Duck_button_pin  6

#define Busy_pin         7

/***************************************/
extern void INIT_BUTTON();
extern void BUTTON_READ();
extern void CHECK_BUSY_PIN();
#endif
