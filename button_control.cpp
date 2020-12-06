
#include "button_control.h"

button_states_t BUTTON;
button_states_t BUTTON_LL;

void INIT_BUTTON()
{
	BUTTON = unpressed;
	BUTTON_LL = unpressed;
}

void BUTTON_READ()
{
  BUTTON_LL = BUTTON;
  if(digitalRead(ButtonPin) == HIGH)
  {
	  BUTTON = pressed;
  }
  else
  {
	  BUTTON = unpressed;
  }

}
