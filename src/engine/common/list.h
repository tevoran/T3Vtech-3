#ifndef TT_LIST_H
#define TT_LIST_H

#include <tt.h>

struct tt_node
{
	void *last;
	void *next;
	void *data; //pointer to some data that is organized by the list
} typedef tt_node;

//returns NULL if reached the end of the list
tt_node* tt_list_next_node(tt_node *current_node);

tt_node* tt_list_last_node(tt_node *current_node);

//creates a new node after the current one
tt_node* tt_list_new_node(tt_node *current_node);

void tt_list_remove_node(tt_node **current_node);

void tt_list_node_set_data(tt_node *current_node, void *data);

#endif