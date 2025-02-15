#ifndef TT_GFX_OBJECTS_2D_H
#define TT_GFX_OBJECTS_2D_H


struct tt_2d_object
{
	//OpenGL relevant data
	GLuint vao;
	GLuint vbo;
	GLuint ibo;
	uint32_t num_indices;

	//transformations
	tt_vec2 translation;
	tt_vec2 scale;
	tt_mat2 rotation;

	//properties
	GLfloat transparency;
	GLuint texture;
		//says if the texture will be cleared when the object is deleted
		bool is_text_object;

} typedef tt_2d_object;

//engine internal functions
void tt_gfx_prepare_sprite();
void tt_2d_object_clear_render_list();

//common 2d object functions
tt_2d_object* tt_2d_object_new();
void tt_2d_object_delete(tt_2d_object **object);
void tt_2d_object_render(tt_2d_object *object);
void tt_2d_object_set_position(tt_2d_object *object, tt_vec2 *position);
void tt_2d_object_scale(tt_2d_object *object, tt_vec2 *scale);
void tt_2d_object_rotate(tt_2d_object *object, float radians);
void tt_2d_object_use_texture(tt_2d_object *object, tt_2d_texture *texture);
void tt_2d_object_set_transparency(tt_2d_object *object, float transparency);
bool tt_2d_object_is_colliding(tt_2d_object *a, tt_2d_object *b);

//object kinds
void tt_2d_object_make_sprite(tt_2d_object *object);

#endif