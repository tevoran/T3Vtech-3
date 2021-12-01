#include <tt.h>

tt_3d_custom_model* tt_3d_custom_model_load_file(const char *path)
{
	int num_verts;

	//deciding the file type
	//OBJ
	if(strstr(path, ".obj") || strstr(path, ".OBJ"))
	{
		if(!tt_3d_object_custom_model_load_obj_file(path, &num_verts))
		{
			return NULL;
		}
		else
		{
			printf("OBJ model from %s successfully loaded\n", path);
		}
	}
}
