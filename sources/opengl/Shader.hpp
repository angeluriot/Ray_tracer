#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <GL/glew.h>

class Shader
{
public:

	Shader(const std::string& vert_path, const std::string& frag_path);

	GLuint get_id() const;
	void bind() const;
	void unbind();
};

#endif
