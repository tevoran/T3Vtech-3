#include <tt.h>

extern GLuint tt_gfx_3d_default_tex; //default texture

GLubyte default_tex[]=
{
	255, 0, 255
};

void tt_gfx_3d_default_tex_init()
{
	glGenTextures(1, &tt_gfx_3d_default_tex);
	glBindTexture(GL_TEXTURE_2D, tt_gfx_3d_default_tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, default_tex);
}

tt_3d_texture* tt_3d_texture_new(const char *path, const bool bilinear_filtering)
{
	tt_3d_texture *new_texture=malloc(sizeof(tt_3d_texture));
	glGenTextures(1, &new_texture->texture);

	glBindTexture(GL_TEXTURE_2D, new_texture->texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	if(bilinear_filtering)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	int x,y,n;
	unsigned char *image_data=stbi_load(path, &x, &y, &n, 0);
	if(image_data)
	{
		printf("image successfully loaded as a texture from %s\n", path);
		printf("texture resolution is %ix%i\n", x, y);
	}
	else
	{
		printf("[ERROR] image couldn't be read from %s\n", path);
		free(new_texture);
		return NULL;
	}

	if(n==4)
	{
		printf("[WARNING] image has 4 channels but only 3 are supported right now\n");
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
	stbi_image_free(image_data);
	return new_texture;
}

void tt_3d_texture_delete(tt_3d_texture **texture)
{
	glDeleteTextures(1, &(*texture)->texture);
	free((*texture));
	texture=NULL; //marking the texture as deleted
}
