/***************************************
* Button  definitions                  *
***************************************/

#ifndef button_control_h
#define button_control_h
/***************************************/

#include "FirstInclude.h"

/* DEFINES */
typedef enum button_states_e {
	unpressed = 0,
	pressed
} button_states_t;

extern button_states_t BUTTON;
extern button_states_t BUTTON_LL;

/* GLOBAL VARIABLES */
#define Is_button_pressed()          (BUTTON == pressed)
#define Is_button_repressed()        ((BUTTON == pressed) && (BUTTON_LL == unpressed))

/***************************************/
extern void INIT_BUTTON();
extern void BUTTON_READ();
#endif
