#include <tt.h>

//this is the beginning of the 3D object rendering list
extern tt_node *tt_3d_list_entry_node;

tt_3d_object* tt_3d_object_new() 
{
	//creating the 3d object and putting it into the render list
	tt_3d_object *new_object=malloc(sizeof(tt_3d_object));
	new_object->node=tt_list_new_node(tt_3d_list_entry_node);
	if(!tt_3d_list_entry_node) //save the entry node if it's one
	{
		tt_3d_list_entry_node=new_object->node;
	}
	tt_list_node_set_data(new_object->node, new_object);

	//initializing the object to default values
	new_object->num_verts=0;
	new_object->vao=0;
	new_object->vbo=0;
	new_object->ibo=0;

	return new_object;
}

//the function uses a pointer pointer so that the deleted object pointer can
//be set to NULL. This is done to reduce possible segfaults by accidentally
//deleting the same object twice.
void tt_3d_object_delete(tt_3d_object **object)
{
	//if this object has already been deleted then just quit
	if(*object==NULL)
	{
		return; 
	}

	//if this object is the first object in the render list
	if((*object)->node==tt_3d_list_entry_node)
	{
		tt_list_remove_node(&tt_3d_list_entry_node);
	}
	else
	{
		tt_list_remove_node(&(*object)->node);
	}

	free(*object);
	*object=NULL; //mark object as deleted
}
