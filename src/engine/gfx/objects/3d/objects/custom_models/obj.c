#include <tt.h>

struct tt_custom_model_vertex
{
	tt_vec3 pos;
	tt_vec2 tex_coord;
} typedef tt_custom_model_vertex;

//returns true if successful
bool tt_3d_object_custom_model_load_obj_file(
	const char *path,
	int *num_vertices)
{
	FILE *file=fopen(path, "r");
	if(!file)
	{
		printf("[ERROR] OBJ file couldn't be read from %s\n", path);
		return false;
	}

	//counting all the vertices
	int vertices_count=0;
	float x,y,z;
	while(fscanf(file, "v %f %f %f", &x, &y, &z)!=EOF)
	{
		vertices_count++;
	}
	printf("%i vertices counted\n", vertices_count);

	//saving all vertices in RAM

	fclose(file);
	
	return true;
}