#include <tt.h>

#define NUM_BUTTONS_SUPPORTED_SDL 16
#define AXIS_MAX 32768

extern bool tt_quiet; //this activates/deactivates debug messages

struct controller
{
	tt_node *this_node;
	SDL_GameController *controller;
	SDL_Joystick *joy;
	SDL_JoystickID id;
	SDL_JoystickGUID guid;

	bool button_press[NUM_BUTTONS_SUPPORTED_SDL];
	bool button_down[NUM_BUTTONS_SUPPORTED_SDL];

	float l_stick_x;
	float l_stick_y;
	float r_stick_x;
	float r_stick_y;

} typedef controller;

//controllers
tt_node *c_list_start; //the begin of the list for the controllers



void tt_input_controller_update(SDL_Event event)
{
	switch(event.type)
	{
		case SDL_CONTROLLERDEVICEADDED:
		{
			tt_input_controller_add_new(event);
			break;
		}

		case SDL_CONTROLLERBUTTONDOWN:
		{
			tt_input_controller_button_down_update(event);
			break;
		}

		case SDL_CONTROLLERBUTTONUP:
		{
			tt_input_controller_button_up_update(event);
		}

		case SDL_CONTROLLERAXISMOTION:
		{
			tt_input_controller_axis_update(event);
		}
	}

}

int tt_input_controller_count()
{
	int i=0;
	tt_node *node=c_list_start;
	while(node)
	{
		i++;
		node=tt_list_next_node(node);
	}
	return i;
}

void tt_input_controller_add_new(SDL_Event event)
{
	if(!tt_quiet)
	{
		printf("adding new controller\n");
	}

	//adding new controller
	SDL_GameController *tmp_controller=SDL_GameControllerOpen(event.cdevice.which);
	if(tmp_controller)
	{
		if(!tt_quiet)
		{
			printf("%s found\n", SDL_GameControllerName(tmp_controller));
		}
		SDL_Joystick *tmp_joy= SDL_GameControllerGetJoystick(tmp_controller);
		int tmp_id=SDL_JoystickInstanceID(tmp_joy);
		printf("tmp_id %i\n", tmp_id); 

		//saving data into the list
		controller *new_controller=malloc(sizeof(controller));
		new_controller->this_node=tt_list_new_node(c_list_start);
		if(!c_list_start)
		{
			c_list_start=new_controller->this_node;
		}
		tt_list_node_set_data(new_controller->this_node, new_controller);

		new_controller->controller=tmp_controller;
		new_controller->joy=tmp_joy;
		new_controller->id=tmp_id;
		new_controller->guid=SDL_JoystickGetGUID(tmp_joy);

		char guid_str[1024];
		SDL_JoystickGetGUIDString(new_controller->guid, guid_str, sizeof(guid_str));
		printf("GUID_STR: %s\n", guid_str);

		printf("MAPPING: %s\n", SDL_GameControllerMapping(tmp_controller));

		//reset keys
		for(int i=0; i<NUM_BUTTONS_SUPPORTED_SDL; i++)
		{
			new_controller->button_press[i]=false;
			new_controller->button_down[i]=false;
		}

	}
	else
	{
		printf("[ERROR] couldn't add new controller\n");
	}

	if(!tt_quiet)
	{
		printf("current number of controller: %i\n", tt_input_controller_count());
	}
}

void tt_input_controller_button_down_update(SDL_Event event)
{
	//looking for the right controller
	tt_node *node=c_list_start;
	while(node)
	{
		controller *c_active=node->data;
		//getting the right combination of event and controller
		if(c_active && (event.cbutton.which==c_active->id))
		{
			//the -1 is necessary because we don't save the button invalid value of SDL
			// https://wiki.libsdl.org/SDL_GameControllerButton
			c_active->button_press[event.cbutton.button-1]=true;
			c_active->button_down[event.cbutton.button-1]=true;
			break;
		}

		//going to the next controller
		node=tt_list_next_node(node);
	}
}

void tt_input_controller_button_up_update(SDL_Event event)
{
	//looking for the right controller
	tt_node *node=c_list_start;
	while(node)
	{
		controller *c_active=node->data;
		//getting the right combination of event and controller
		if(c_active && (event.cbutton.which==c_active->id))
		{
			//the -1 is necessary because we don't save the button invalid value of SDL
			// https://wiki.libsdl.org/SDL_GameControllerButton
			c_active->button_down[event.cbutton.button-1]=false;
			break;
		}

		//going to the next controller
		node=tt_list_next_node(node);
	}
}

void tt_input_controller_axis_update(SDL_Event event)
{
	//looking for the right controller
	tt_node *node=c_list_start;
	while(node)
	{
		controller *c_active=node->data;

		//the affected controller
		if(c_active && (event.caxis.which==c_active->id))
		{
			//setting the axis values
			if(event.caxis.axis==SDL_CONTROLLER_AXIS_LEFTX)
			{
				signed int value=event.caxis.value;
				c_active->l_stick_x=(float)value/AXIS_MAX;
			}
			if(event.caxis.axis==SDL_CONTROLLER_AXIS_LEFTY)
			{
				signed int value=event.caxis.value;
				c_active->l_stick_y=(float)value/AXIS_MAX;
			}
			if(event.caxis.axis==SDL_CONTROLLER_AXIS_RIGHTX)
			{
				signed int value=event.caxis.value;
				c_active->r_stick_x=(float)value/AXIS_MAX;
			}
			if(event.caxis.axis==SDL_CONTROLLER_AXIS_RIGHTY)
			{
				signed int value=event.caxis.value;
				c_active->r_stick_y=(float)value/AXIS_MAX;
			}
		}

		//next controller
		node=tt_list_next_node(node);
	}
}

void tt_input_controller_button_reset()
{
	//resetting all button arrays
	tt_node *node=c_list_start;
	while(node)
	{
		controller *c_active=node->data;
		for(int i=0; i<NUM_BUTTONS_SUPPORTED_SDL; i++)
		{
			c_active->button_press[i]=false;
		}

		node=tt_list_next_node(node);
	}
}

//a single button press
bool tt_input_controller_button_press(const unsigned char button)
{
	if(c_list_start)
	{
		tt_node *node=c_list_start;
		controller *c_active=node->data;
		return c_active->button_press[button-1];
	}
	else
	{
		return false;
	}
}

//button can be down continuosly
bool tt_input_controller_button_down(const unsigned char button)
{
	if(c_list_start)
	{
		tt_node *node=c_list_start;
		controller *c_active=node->data;
		return c_active->button_down[button-1];
	}
	else
	{
		return false;
	}
}

void tt_input_controller_axis_state(
	float *l_stick_x_out,
	float *l_stick_y_out,
	float *r_stick_x_out,
	float *r_stick_y_out)
{
	if(c_list_start)
	{
		tt_node *node=c_list_start;
		controller *c_active=node->data;
		
		*l_stick_x_out=c_active->l_stick_x;
		*l_stick_y_out=c_active->l_stick_y;

		*r_stick_x_out=c_active->r_stick_x;
		*r_stick_y_out=c_active->r_stick_y;		
	}
	else
	{
		*l_stick_x_out=0;
		*l_stick_y_out=0;

		*r_stick_x_out=0;
		*r_stick_y_out=0;			
	}

}

void tt_input_controller_add_mappings()
{
	int ret=0;
	ret=SDL_GameControllerAddMappingsFromFile("settings/controllermappings.txt");
	if(!tt_quiet)
	{
		printf("%i mappings added\n", ret);
	}
	if(ret==-1)
	{
		printf("[ERROR] controller mappings couldn't be added\n");
		printf("SDL2 error message: %s\n", SDL_GetError());
	}
}