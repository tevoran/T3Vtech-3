#include <tt.h>

//returns NULL if reached the end of the list
tt_node* tt_list_next_node(tt_node *current_node)
{
	return current_node->next;
}

tt_node* tt_list_last_node(tt_node *current_node)
{
	if(!current_node->last)
	{
		return current_node;
	}
	return current_node->last;
}

//creates a new node after the current one
tt_node* tt_list_new_node(tt_node *current_node)
{
	tt_node *node=NULL;
	node=malloc(sizeof(tt_node));
	node->data=NULL;

	//if there is no current node yet (NULL as input)
	if(!current_node)
	{
		tt_node *node=malloc(sizeof(tt_node));
		node->last=NULL;
		node->next=NULL;
		node->data=NULL;
		return node;		
	}

	//if current last node
	if(!current_node->next && current_node->last)
	{
		current_node->next=node;
		node->next=NULL;
		node->last=current_node;
		return node;
	}

	//if current first node
	if(!current_node->next && !current_node->last)
	{
		node->last=current_node;
		current_node->next=node;
		node->next=NULL;
		return node;
	}

	//if current node is in between other nodes
	node->next=current_node->next;
	current_node->next=node;
	node->last=current_node;
	tt_node *following=node->next;
	following->last=node;
	return node;
}

void tt_list_node_set_data(tt_node *current_node, void *data)
{
	current_node->data=data;
}