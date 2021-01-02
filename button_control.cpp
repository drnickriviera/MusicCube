
#include "button_control.h"

button_states_t BUTTON;
button_states_t BUTTON_LL;
bool BUSY_PIN;
button_action_t BUTTON_TOGGLE;
uint8_t TOGGLE_COUNTER;

static void CHECK_FOR_BUTTON_TOGGLE();

void INIT_BUTTON()
{
	BUTTON = dont_know;
	BUTTON_LL = dont_know;

	BUSY_PIN = HIGH;

	BUTTON_TOGGLE = selected;
	TOGGLE_COUNTER = 0;

	// initialize digital inputs
	pinMode(Bear_button_pin, INPUT_PULLUP);
	pinMode(Sheep_button_pin, INPUT_PULLUP);
	pinMode(Rabit_button_pin, INPUT_PULLUP);
	pinMode(Mouse_button_pin, INPUT_PULLUP);
	pinMode(Duck_button_pin, INPUT_PULLUP);

	pinMode(Busy_pin, INPUT);
}

void BUTTON_READ()
{
  BUTTON_LL = BUTTON;
  if(digitalRead(Bear_button_pin) == LOW)
  {
	  BUTTON = bear;
  }
  else if (digitalRead(Sheep_button_pin) == LOW)
  {
	  BUTTON = sheep;
  }
  else if (digitalRead(Rabit_button_pin) == LOW)
  {
	  BUTTON = rabit;
  }
  else if (digitalRead(Mouse_button_pin) == LOW)
  {
  	  BUTTON = mouse;
  }
  else if (digitalRead(Duck_button_pin) == LOW)
  {
  	  BUTTON = duck;
  }
  else
  {
  	  BUTTON = dont_know;
  }
  CHECK_FOR_BUTTON_TOGGLE();

  Serial.print(BUTTON);
}

void CHECK_BUSY_PIN()
{
	BUSY_PIN = digitalRead(Busy_pin);
}

void CHECK_FOR_BUTTON_TOGGLE()
{

	if(BUTTON_TOGGLE == toggle_finished)
	{
		BUTTON_TOGGLE = selected;
	}

	if(BUTTON_TOGGLE == toggle_cool_down)
	{
		if(TOGGLE_COUNTER>0)
		{
			TOGGLE_COUNTER--;
		}
		else
		{
			BUTTON_TOGGLE = toggle_finished;
		}
	}

	if(BUTTON_TOGGLE == toggle)
	{
		if(TOGGLE_COUNTER>3)
		{
			BUTTON_TOGGLE = toggle_cool_down;
			TOGGLE_COUNTER = 50;
		}
	}

	if(BUTTON != BUTTON_LL && BUTTON_TOGGLE != toggle_cool_down)
	{
		BUTTON_TOGGLE = toggle;
		TOGGLE_COUNTER++;
	}
}
