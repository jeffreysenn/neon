#pragma once
#include "Shader.h"
#include <glm/glm.hpp>

namespace neon {

class Program {
public:
	Program();
	Program(const Vertex_shader& vertex_shader, const Fragment_shader& fragment_shader);
	Program(const Program&) = delete;
	Program& operator=(const Program&) = delete;
	Program(Program&& move) noexcept;
	Program& operator=(Program&& rhs) noexcept;
	~Program();
	
	void set(const Vertex_shader& vertex_shader, const Fragment_shader& fragment_shader);
	GLuint get() const;
	void bind() const;

	GLuint get_attrib_location(const string& name) const;
	GLuint get_uniform_location(const string& name) const;
	void set_uniform_mat4(const string& name, const glm::mat4& mat);
	void set_uniform_vec4(const string& name, const glm::vec4& mat);
private:
	GLuint program_ = 0;
public:
	friend void swap(Program& lhs, Program& rhs);
};
}