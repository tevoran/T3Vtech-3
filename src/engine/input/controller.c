#include <tt.h>

#define MAX_NUM_CONTROLLERS 8

extern bool tt_quiet; //this activates/deactivates debug messages

struct controller
{
	tt_node *this_node;
	SDL_GameController *controller;
	SDL_Joystick *joy;
	SDL_JoystickID id;
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
		}

		case SDL_CONTROLLERBUTTONDOWN:
		{
			printf("KEY\n");
		}

		case SDL_CONTROLLERAXISMOTION:
		{
			//printf("AXIS\n");
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