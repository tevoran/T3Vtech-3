#include <tt.h>

extern GLuint tt_std_3d_shader; //the default shader program for all 3d objects
extern GLuint tt_std_2d_shader; //the default shader program for all 2d objects


//test data
GLfloat tri[]=
{
	-1.0, 1.0, 0.0,
	1.0, 1.0, 0.0,
	0.0, -1.0, 0.0,
};

void tt_gfx_render()
{
	glUseProgram(tt_std_3d_shader);
	
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tri), tri, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*3, (void*)0);
	glEnableVertexAttribArray(0);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	//printf("%i\n", sizeof(tri));


	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}
