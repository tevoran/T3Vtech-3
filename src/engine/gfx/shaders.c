#include <tt.h>

struct shader
{
	GLuint compute;
	GLuint vertex;
	GLuint tess_control;
	GLuint tess_evaluation;
	GLuint geometry;
	GLuint fragment;
};

//shader compilation helper function to reduce code size
//returns true if successful and false in the case of an error
bool tt_gfx_shader_compilation(
	GLuint* shader,
	const char *path_to_shader, 
	const GLenum shader_type)
{
	Uint32 shader_size;
	FILE *shader_file;
	char *shader_buffer;
	GLenum error;

	switch(shader_type)
	{
		case GL_COMPUTE_SHADER:
			tt_log(TT_INFO, "creating a compute shader");
			break;
		case GL_VERTEX_SHADER:
			tt_log(TT_INFO, "creating a vertex shader");
			break;
		case GL_TESS_CONTROL_SHADER:
			tt_log(TT_INFO, "creating a tesselation control shader");
			break;
		case GL_TESS_EVALUATION_SHADER:
			tt_log(TT_INFO, "creating a tesselation evaluation shader");
			break;
		case GL_GEOMETRY_SHADER:
			tt_log(TT_INFO, "creating a geometry shader");
			break;
		case GL_FRAGMENT_SHADER:
			tt_log(TT_INFO, "creating a fragment shader");
			break;
		default:
			tt_log(TT_ERROR, "invalid shader type");
			return false;
	}
	shader_file=fopen(path_to_shader, "rb");
	if(!shader_file)
	{
		switch(shader_type)
		{
			case GL_COMPUTE_SHADER:
				tt_log(TT_ERROR, "while reading a compute shader from %s",
					path_to_shader);
				break;
			case GL_VERTEX_SHADER:
				tt_log(TT_ERROR, "while reading a vertex shader from %s",
					path_to_shader);
				break;
			case GL_TESS_CONTROL_SHADER:
				tt_log(TT_ERROR, "while reading a tesselation control shader from %s",
					path_to_shader);
				break;
			case GL_TESS_EVALUATION_SHADER:
				tt_log(TT_ERROR, "while reading a tesselation evaluation shader from %s",
					path_to_shader);
				break;
			case GL_GEOMETRY_SHADER:
				tt_log(TT_ERROR, "while reading a geometry shader from %s",
					path_to_shader);
				break;
			case GL_FRAGMENT_SHADER:
				tt_log(TT_ERROR, "while reading a fragment shader from %s",
					path_to_shader);
				break;
			default:
				tt_log(TT_ERROR, "invalid shader type");
		}
		fclose(shader_file);
		return false;
	}

	//determining the size of the shader file
	fseek(shader_file, 0, SEEK_END);
	shader_size=ftell(shader_file);
	fseek(shader_file, 0, SEEK_SET);
	shader_size++; //necessary for the zero termination of the C string
	shader_buffer=malloc(shader_size);
	fread(shader_buffer, shader_size, 1, shader_file);
	shader_buffer[shader_size-1]=0; //zero termination

	//create shader object
	*shader=glCreateShader(shader_type);
	if(!*shader)
	{
		tt_log(TT_ERROR, "couldn't create a shader");
		free(shader_buffer);
		fclose(shader_file);
		return false;
	}

	//passing the shader source code to the shader object
	const GLchar *shader_buffer_src=shader_buffer;
	glShaderSource(*shader, 1, &shader_buffer_src, NULL);
	Uint32 shader_size_check_length;
	//debug option
	glGetShaderiv(
		*shader,
		GL_SHADER_SOURCE_LENGTH,
		&shader_size_check_length);
	if(shader_size_check_length!=shader_size)
	{
		tt_log(TT_ERROR, "shader size got changed");
		free(shader_buffer);
		fclose(shader_file);
		return false;
	}

	//compiling the shader
	glCompileShader(*shader);
	glGetShaderiv(
		*shader,
		GL_COMPILE_STATUS,
		&error);
	if(error==GL_FALSE)
	{
		GLuint log_length;
		glGetShaderiv(
			*shader,
			GL_INFO_LOG_LENGTH,
			&log_length);
		char *error_msg=malloc(log_length);
		glGetShaderInfoLog(
			*shader,
			log_length,
			NULL,
			error_msg);
		tt_log(TT_ERROR, "shader couldn't be compiled");
		tt_log(TT_ERROR, "compilation error message:\n%s", error_msg);
		free(error_msg);
		free(shader_buffer);
		fclose(shader_file);
		return false;
	}

	//cleanup
	fclose(shader_file);
	free(shader_buffer);
	return true;
}


//not used shaders can be passed as NULL
//although vertex and fragment shaders are necessary to show something
//returns 0 if an error occured
GLuint tt_gfx_create_shader(
	const char *path_to_compute_shader,
	const char *path_to_vertex_shader,
	const char *path_to_tess_control_shader,
	const char *path_to_tess_evaluation_shader,
	const char *path_to_geometry_shader,
	const char *path_to_fragment_shader)
{
	struct shader shader;
	shader.compute=0;
	shader.vertex=0;
	shader.tess_control=0;
	shader.tess_evaluation=0;
	shader.geometry=0;
	shader.fragment=0;

	//return when no shader was given
	if(
		!path_to_compute_shader &&
		!path_to_vertex_shader &&
		!path_to_tess_control_shader &&
		!path_to_tess_evaluation_shader &&
		!path_to_geometry_shader &&
		!path_to_fragment_shader)
	{
		tt_log(TT_ERROR, "no shader to compile has been found");
		return 0;
	}

	GLuint program=glCreateProgram();
	if(!program)
	{
		tt_log(TT_ERROR, "OpenGL couldn't create the shader program");
		return 0;
	}

	//creating the compute shader
	if(path_to_compute_shader)
	{
		if(tt_gfx_shader_compilation(
			&shader.compute,
			path_to_compute_shader,
			GL_COMPUTE_SHADER))
		{
			tt_log(TT_INFO, "successfully created a compute shader");
		}
		else
		{
			return 0;
		}
	}

	//creating the vertex shader
	if(path_to_vertex_shader)
	{
		if(tt_gfx_shader_compilation(
			&shader.vertex,
			path_to_vertex_shader,
			GL_VERTEX_SHADER))
		{
			tt_log(TT_INFO, "successfully created a vertex shader");
		}
		else
		{
			return 0;
		}
	}

	//creating the tesselation control shader
	if(path_to_tess_control_shader)
	{
		if(tt_gfx_shader_compilation(
			&shader.tess_control,
			path_to_tess_control_shader,
			GL_TESS_CONTROL_SHADER))
		{
			tt_log(TT_INFO, "successfully created a tesselation control shader");
		}
		else
		{
			return 0;
		}
	}

	//creating the tesselation evaluation shader
	if(path_to_tess_evaluation_shader)
	{
		if(tt_gfx_shader_compilation(
			&shader.tess_evaluation,
			path_to_tess_evaluation_shader,
			GL_TESS_EVALUATION_SHADER))
		{
			tt_log(TT_INFO, "successfully created a tesselation evaluation shader");
		}
		else
		{
			return 0;
		}
	}

	//creating the geometry shader
	if(path_to_geometry_shader)
	{
		if(tt_gfx_shader_compilation(
			&shader.geometry,
			path_to_geometry_shader,
			GL_GEOMETRY_SHADER))
		{
			tt_log(TT_INFO, "successfully created a geometry shader");
		}
		else
		{
			return 0;
		}
	}

	//creating the fragment shader
	if(path_to_fragment_shader)
	{
		if(tt_gfx_shader_compilation(
			&shader.fragment,
			path_to_fragment_shader,
			GL_FRAGMENT_SHADER))
		{
			tt_log(TT_INFO, "successfully created a fragment shader");
		}
		else
		{
			return 0;
		}
	}

	//linking the different shaders together for the final shader program
	if(shader.compute)
	{
		glAttachShader(program, shader.compute);
	}
	if(shader.vertex)
	{
		glAttachShader(program, shader.vertex);
	}
	if(shader.tess_control)
	{
		glAttachShader(program, shader.tess_control);
	}
	if(shader.tess_evaluation)
	{
		glAttachShader(program, shader.tess_evaluation);
	}
	if(shader.geometry)
	{
		glAttachShader(program, shader.geometry);
	}
	if(shader.fragment)
	{
		glAttachShader(program, shader.fragment);
	}

	glLinkProgram(program);

	//cleanup
	//if shader values are zero then they are ignored
	glDeleteShader(shader.compute);
	glDeleteShader(shader.vertex);
	glDeleteShader(shader.tess_control);
	glDeleteShader(shader.tess_evaluation);
	glDeleteShader(shader.geometry);
	glDeleteShader(shader.fragment);

	return program;
}