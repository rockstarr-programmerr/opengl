#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <string>
#include <glad/glad.h>


std::string get_file_content(const char* filename);

class Shader
{
public:
	GLuint ID;
	Shader(const char* vertex_file, const char* fragment_file);

	void Activate();
	void Delete();
};

#endif
