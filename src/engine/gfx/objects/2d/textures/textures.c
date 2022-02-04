#include <tt.h>

extern GLuint tt_gfx_2d_default_tex; //default texture

GLubyte default_tex_2d[]=
{
	255, 0, 255
};

void tt_gfx_2d_default_tex_init()
{
	glGenTextures(1, &tt_gfx_2d_default_tex);
	glBindTexture(GL_TEXTURE_2D, tt_gfx_2d_default_tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, default_tex_2d);
}

tt_2d_texture* tt_2d_texture_new(const char *path, const bool bilinear_filtering)
{
	tt_2d_texture *new_texture=malloc(sizeof(tt_2d_texture));
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
		printf("image successfully loaded as a 2D texture from %s\n", path);
		printf("texture resolution is %ix%i\n", x, y);
	}
	else
	{
		printf("[ERROR] image couldn't be read from %s\n", path);
		free(new_texture);
		stbi_image_free(image_data);
		return NULL;
	}
	if(!(n==3 || n==4))
	{
		printf("[ERROR] image has not 3 or 4 channels and can't be used\n");
		return NULL;
	}

	//flip image
	uint8_t *image_flip=malloc(x*y*4*sizeof(unsigned char)); //a pixel is RGBA
	int iy_origin=0;
	for(int iy=y-1; iy>=0; iy--)
	{
		for(int ix=0; ix<x; ix++)
		{
			image_flip[(iy*x+ix)*4]=image_data[(iy_origin*x+ix)*n];
			image_flip[(iy*x+ix)*4+1]=image_data[(iy_origin*x+ix)*n+1];
			image_flip[(iy*x+ix)*4+2]=image_data[(iy_origin*x+ix)*n+2];
			if(n==3)
			{
				image_flip[(iy*x+ix)*4+3]=255;
			}
			if(n==4)
			{
				image_flip[(iy*x+ix)*4+3]=image_data[(iy_origin*x+ix)*4+3];
			}
		}
		iy_origin++;
	}		

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_flip);
	stbi_image_free(image_data);
	free(image_flip);
	return new_texture;
}

tt_2d_texture* tt_2d_texture_new_from_RGBA(
	void *image_data, 
	const int res_x,
	const int res_y,
	const bool bilinear_filtering)
{
	tt_2d_texture *new_texture=malloc(sizeof(tt_2d_texture));
	glGenTextures(1, &new_texture->texture);

	glBindTexture(GL_TEXTURE_2D, new_texture->texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

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

	//flip image
	uint8_t *image_flip=malloc(res_x*res_y*4*sizeof(unsigned char)); //a pixel is RGBA
	uint8_t *image_data_u8=image_data;
	int iy_origin=0;
	for(int iy=res_y-1; iy>=0; iy--)
	{
		for(int ix=0; ix<res_x; ix++)
		{
			image_flip[(iy*res_x+ix)*4]=image_data_u8[(iy_origin*res_x+ix)*4];
			image_flip[(iy*res_x+ix)*4+1]=image_data_u8[(iy_origin*res_x+ix)*4+1];
			image_flip[(iy*res_x+ix)*4+2]=image_data_u8[(iy_origin*res_x+ix)*4+2];
			image_flip[(iy*res_x+ix)*4+3]=image_data_u8[(iy_origin*res_x+ix)*4+3];
		}
		iy_origin++;
	}		


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, res_x, res_y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_flip);
	free(image_flip);
	return new_texture;
}

void tt_2d_texture_delete(tt_2d_texture **texture)
{
	glDeleteTextures(1, &(*texture)->texture);
	free((*texture));
	*texture=NULL; //marking the texture as deleted
}
