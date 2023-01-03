#include "opengl/Shader.hpp"

Shader::Shader(const std::string& vert_path, const std::string& frag_path)$
{

}

GLuint Shader::get_id() const
{
	return *program_id;
}

void Shader::bind() const
{
	glUseProgram(get_id());
}

void Shader::unbind()
{
	glUseProgram(0);
}
