#ifndef TT_GFX_OBJECTS_3D_H
#define TT_GFX_OBJECTS_3D_H

#include <tt.h>

#define MAX_POINT_LIGHTS_PER_OBJECT 16
#define MAX_AO_LIGHTS_PER_OBJECT 16

//all 3D objects are organized in a linked list that the render goes through
struct tt_3d_object
{
	//pointer to a node in the render list that points also back to the object
	tt_node *node;

	//OpenGL relevant data
	GLuint vao;
	GLuint vbo;
	GLuint ibo;
	uint32_t num_verts;
	uint32_t num_indices;

	//actual model data
	GLfloat *vertex_data;
	GLuint *index_data;

	//transformations
	tt_mat4 translation;
	tt_mat4 scale;
	tt_mat4 rotation;

	//properties
	GLuint texture;
	tt_vec3 color;
	tt_vec3 emission;

	float bounding_sphere_radius;
	bool invisibility_toggle;
	bool backface_culling_toggle;

	//lighting
	tt_point_light point_lights[MAX_POINT_LIGHTS_PER_OBJECT];
	int point_light_count;

	tt_ao_light ao_lights[MAX_AO_LIGHTS_PER_OBJECT];
	int ao_light_count;

	bool lighting_affected;

	//collision properties
	tt_3d_collision_aabb aabb; //its measurements derive from the mesh itself
		//so it needs effectively transformed like the mesh itself to be usable

} typedef tt_3d_object;

#include "batch_objects/batch_object.h"
#include "custom_models/custom_model.h"

//preparation functions
//they keep the data for the primitves already in memory, so they don't need to be created on the fly
void tt_gfx_prepare_quad();
void tt_gfx_prepare_cube();

//clean up functions
void tt_gfx_cleanup_quad();
void tt_gfx_cleanup_cube();

//3D object related
tt_3d_object* tt_3d_object_new();
void tt_3d_object_make_quad(tt_3d_object *object);
void tt_3d_object_make_cube(tt_3d_object *object);
void tt_3d_object_use_custom_model(tt_3d_object *object, tt_3d_custom_model *model);
void tt_3d_object_use_batch_object(tt_3d_object *object, tt_3d_batch_object *batch_object);
void tt_3d_object_delete(tt_3d_object **object);

//transformations
void tt_3d_object_scale(tt_3d_object *object, tt_vec3 *scale);
void tt_3d_object_set_position(tt_3d_object *object, tt_vec3 *position);
void tt_3d_object_set_rotation(tt_3d_object *object, tt_vec3 *rot_axis, float radians);
void tt_3d_object_rotate(tt_3d_object *object, tt_vec3 *rot_axis, float radians);
void tt_3d_object_rotate_local_axis(tt_3d_object *object, tt_vec3 *rot_axis, float radians);
void tt_3d_object_rotate_like(tt_3d_object *object_target, tt_3d_object *object_already_rotated);

//object properties
void tt_3d_object_use_texture(tt_3d_object *object, tt_3d_texture *texture);
void tt_3d_object_use_default_texture(tt_3d_object *object);
void tt_3d_object_set_color(tt_3d_object *object, tt_vec3 *color);
void tt_3d_object_set_emission(tt_3d_object *object, tt_vec3 *emission);
void tt_3d_object_make_invisible(tt_3d_object *object, bool toggle);
void tt_3d_object_back_face_culling(tt_3d_object *object, bool toggle);
float tt_3d_object_get_bounding_sphere_size(tt_3d_object *object);

void tt_3d_object_light_affected(tt_3d_object *object, bool toggle);
void tt_3d_object_add_point_light(tt_3d_object *object, tt_point_light light);
void tt_3d_object_remove_point_light(tt_3d_object *object, tt_point_light light);
void tt_3d_object_clear_point_lights(tt_3d_object *object);
int tt_3d_object_get_point_light_count(tt_3d_object *object);
void tt_3d_object_add_ao_light(tt_3d_object *object, tt_ao_light light);
void tt_3d_object_remove_ao_light(tt_3d_object *object, tt_ao_light light);
void tt_3d_object_clear_ao_lights(tt_3d_object *object);
int tt_3d_object_get_ao_light_count(tt_3d_object *object);

//collisions
void tt_3d_aabb_after_world_transform(tt_3d_object *obj, tt_3d_collision_aabb *aabb);
bool tt_3d_object_colliding_aabb(tt_3d_object *a, tt_3d_object *b);

#endif
