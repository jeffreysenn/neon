#include "Program.h"

#include <cassert>
#include <glm/gtc/type_ptr.hpp>

#include "neon_error.h"
#include "shader_util.h"

namespace neon {
Program::Program()
{
	program_ = glCreateProgram();
	check_gl_error();
}

Program::Program(const Vertex_shader& vertex_shader, const Fragment_shader& fragment_shader)
	: Program()
{
	set(vertex_shader, fragment_shader);
}

Program::Program(Program&& move) noexcept
{
	swap(*this, move);
}

Program& Program::operator=(Program&& rhs) noexcept
{
	swap(*this, rhs);
	return *this;
}

Program::~Program()
{
	glDeleteProgram(program_);
}

void Program::set(const Vertex_shader& vertex_shader, const Fragment_shader& fragment_shader)
{
	glAttachShader(program_, vertex_shader.get());
	glAttachShader(program_, fragment_shader.get());
	glLinkProgram(program_);
	shader_util::check_status(shader_util::Type::PROGRAM, program_);
	glDetachShader(program_, vertex_shader.get());
	glDetachShader(program_, fragment_shader.get());
}

GLuint Program::get() const
{
	return program_;
}

void Program::bind() const
{
	glUseProgram(program_);
}

GLuint Program::get_attrib_location(const string& name) const
{
	bind();
	auto location = glGetAttribLocation(program_, name.c_str());
	if (location < -1) {
		throw Gl_error("failed to get shader attribute");
	}
	return location;
}

GLuint Program::get_uniform_location(const string& name) const
{
	bind();
	auto location = glGetUniformLocation(program_, name.c_str());
	if (location < 0) {
		throw Gl_error("failed to get shader uniform location");
	}
	return location;
}

void Program::set_uniform_mat4(const string& name, const glm::mat4& mat)
{
	auto location = get_uniform_location(name);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void Program::set_uniform_vec4(const string& name, const glm::vec4& vec)
{
	auto location = get_uniform_location(name);
	glUniform4fv(location, 1, glm::value_ptr(vec));
}


void swap(Program& lhs, Program& rhs)
{
	std::swap(lhs.program_, rhs.program_);
}
}