#include <tt.h>

#define NUM_BUTTONS_SUPPORTED_SDL 16
#define AXIS_MAX 32768
#define CTL_AXIS_THRESHOLD 0.05 //mininum axis movement until it is registered

extern bool tt_quiet; //this activates/deactivates debug messages

struct controller
{
	T_node *this_node;
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
T_node *c_list_start=NULL; //the begin of the list for the controllers



void tt_input_controller_update(SDL_Event event)
{
	switch(event.type)
	{
		case SDL_CONTROLLERBUTTONDOWN:
		{
			tt_input_controller_button_down_update(event);
			break;
		}

		case SDL_CONTROLLERBUTTONUP:
		{
			tt_input_controller_button_up_update(event);
			break;
		}

		case SDL_CONTROLLERAXISMOTION:
		{
			tt_input_controller_axis_update(event);
			break;
		}

		case SDL_CONTROLLERDEVICEADDED:
		{
			tt_input_controller_add_new(event);
			break;
		}

		case SDL_CONTROLLERDEVICEREMOVED:
		{
			tt_input_controller_removed(event);
			break;
		}
	}

}

int tt_input_controller_count()
{
	int i=0;
	T_node *node=c_list_start;
	while(node)
	{
		i++;
		node=T_list_next_node(node);
	}
	return i;
}

void tt_input_controller_add_new(SDL_Event event)
{
	tt_log(TT_INFO, "adding new controller");

	//adding new controller
	SDL_GameController *tmp_controller=SDL_GameControllerOpen(event.cdevice.which);
	if(tmp_controller)
	{
		tt_log(TT_INFO, "%s found", SDL_GameControllerName(tmp_controller));
		SDL_Joystick *tmp_joy= SDL_GameControllerGetJoystick(tmp_controller);
		int tmp_id=SDL_JoystickInstanceID(tmp_joy);
		tt_log(TT_INFO, "tmp_id %i", tmp_id); 			

		//saving data into the list
		controller *new_controller=malloc(sizeof(controller));
		new_controller->this_node=T_list_new_node(c_list_start);
		if(!c_list_start)
		{
			c_list_start=new_controller->this_node;
		}
		T_list_node_set_data(new_controller->this_node, new_controller);

		new_controller->controller=tmp_controller;
		new_controller->joy=tmp_joy;
		new_controller->id=tmp_id;
		new_controller->guid=SDL_JoystickGetGUID(tmp_joy);

		char guid_str[1024];
		SDL_JoystickGetGUIDString(new_controller->guid, guid_str, sizeof(guid_str));
		tt_log(TT_INFO, "GUID_STR: %s", guid_str);
		tt_log(TT_INFO, "MAPPING: %s", SDL_GameControllerMapping(tmp_controller));

		//reset keys
		for(int i=0; i<NUM_BUTTONS_SUPPORTED_SDL; i++)
		{
			new_controller->button_press[i]=false;
			new_controller->button_down[i]=false;
		}
		//reset axes
		new_controller->l_stick_x=0;
		new_controller->l_stick_y=0;
		new_controller->r_stick_x=0;
		new_controller->r_stick_y=0;


	}
	else
	{
		tt_log(TT_ERROR, "couldn't add new controller");
	}

	tt_log(TT_INFO, "current number of controller: %i", tt_input_controller_count());
}

void tt_input_controller_removed(SDL_Event event)
{
	T_node *node=c_list_start;

	while(node)
	{
		controller *c_active=node->data;
		if(c_active && (c_active->id==event.cdevice.which))
		{
			bool is_beginning=false;
			if(node==c_list_start)
			{
				is_beginning=true;
			}
			//remove the controller
			free(c_active);
			T_list_destroy_node(&node);

			if(is_beginning)
			{
				c_list_start=node;
			}
			break;
		}

		//next controller
		node=T_list_next_node(node);
	}
}


void tt_input_controller_button_down_update(SDL_Event event)
{
	//looking for the right controller
	T_node *node=c_list_start;
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
		node=T_list_next_node(node);
	}
}

void tt_input_controller_button_up_update(SDL_Event event)
{
	//looking for the right controller
	T_node *node=c_list_start;
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
		node=T_list_next_node(node);
	}
}

void tt_input_controller_axis_update(SDL_Event event)
{
	//looking for the right controller
	T_node *node=c_list_start;
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

		//if axis movement is below a thresholed then set it to zero
		//some controllers are not properly calibrated (anymore)
		if(tt_math_f_abs(c_active->l_stick_x) < CTL_AXIS_THRESHOLD)
		{
			c_active->l_stick_x=0;
		}
		if(tt_math_f_abs(c_active->l_stick_y) < CTL_AXIS_THRESHOLD)
		{
			c_active->l_stick_y=0;
		}
		if(tt_math_f_abs(c_active->r_stick_x) < CTL_AXIS_THRESHOLD)
		{
			c_active->r_stick_x=0;
		}
		if(tt_math_f_abs(c_active->r_stick_y) < CTL_AXIS_THRESHOLD)
		{
			c_active->r_stick_y=0;
		}
		//next controller
		node=T_list_next_node(node);
	}
}

void tt_input_controller_button_reset()
{
	//resetting all button arrays
	T_node *node=c_list_start;
	while(node)
	{
		controller *c_active=node->data;
		for(int i=0; i<NUM_BUTTONS_SUPPORTED_SDL; i++)
		{
			c_active->button_press[i]=false;
		}

		node=T_list_next_node(node);
	}
}

//a single button press
bool tt_input_controller_button_press(const int ctl_number, const unsigned char button)
{
	int i_ctl=0;
	if(c_list_start)
	{
		T_node *node=c_list_start;
		while(node)
		{
			i_ctl++;
			controller *c_active=node->data;
			if(i_ctl==ctl_number)
			{
				return c_active->button_press[button-1];
			}

			//next controller
			node=T_list_next_node(node);			
		}
	}
	else
	{
		return false;
	}
}

//button can be down continuosly
bool tt_input_controller_button_down(const int ctl_number, const unsigned char button)
{
	int i_ctl=0;
	if(c_list_start)
	{
		T_node *node=c_list_start;
		while(node)
		{
			i_ctl++;
			controller *c_active=node->data;
			if(i_ctl==ctl_number)
			{
				return c_active->button_down[button-1];
			}

			//next controller
			node=T_list_next_node(node);
		}
	}
	else
	{
		return false;
	}
}

void tt_input_controller_axis_state(
	const int ctl_number, 
	float *l_stick_x_out,
	float *l_stick_y_out,
	float *r_stick_x_out,
	float *r_stick_y_out)
{
	int i_ctl=0;
	if(c_list_start)
	{
		T_node *node=c_list_start;
		while(node)
		{
			i_ctl++;
			controller *c_active=node->data;
			
			if(i_ctl==ctl_number)
			{
				*l_stick_x_out=c_active->l_stick_x;
				*l_stick_y_out=c_active->l_stick_y;

				*r_stick_x_out=c_active->r_stick_x;
				*r_stick_y_out=c_active->r_stick_y;
				return;			
			}

			//next controller
			node=T_list_next_node(node);
		}
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
	tt_log(TT_INFO, "%i controller mappings added", ret);
	if(ret==-1)
	{
		tt_log(TT_ERROR, "controller mappings couldn't be added\n");
		tt_log(TT_ERROR, "SDL2 error message: %s", SDL_GetError());
	}
}