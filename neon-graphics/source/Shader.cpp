#include "Shader.h"

#include <stdexcept>

#include "shader_util.h"
#include "Shader.h"
#include "neon_error.h"

namespace neon {

namespace {

auto read_file(const string& filename)
{
	auto data = dynamic_array<uint8>();
	if (!file_system::read_file_content(filename, data)) {
		throw std::runtime_error("Failed to file: " + filename);
	}
	data.push_back(0);
	return data;
}

auto get_source(const dynamic_array<uint8>& data)
{
	return reinterpret_cast<const GLchar*>(data.data());
}
}

Shader::Shader(Shader&& move) noexcept
{
	swap(*this, move);
}

Shader& Shader::operator=(Shader&& move) noexcept
{
	swap(*this, move);
	return *this;
}

Shader::~Shader()
{
	glDeleteShader(shader_);
}

void Shader::load_from_file(const string& filename)
{
	const auto data = read_file(filename);
	const auto source = get_source(data);
	set(source);
}

GLuint Shader::get() const
{
	return shader_;
}

void Shader::set(const GLchar* source)
{
	glShaderSource(shader_, 1, &source, nullptr);
	glCompileShader(shader_);
	shader_util::check_status(shader_util::Type::SHADER, shader_);
}

Vertex_shader::Vertex_shader()
{
	shader_ = glCreateShader(GL_VERTEX_SHADER);
	check_gl_error();
}

Vertex_shader::Vertex_shader(const string& filename)
	: Vertex_shader()
{
	load_from_file(filename);
}

Fragment_shader::Fragment_shader()
{
	shader_ = glCreateShader(GL_FRAGMENT_SHADER);
	check_gl_error();
}

Fragment_shader::Fragment_shader(const string& filename)
	: Fragment_shader()
{
	load_from_file(filename);
}

void swap(Shader& lhs, Shader& rhs) noexcept
{
	std::swap(lhs.shader_, rhs.shader_);
}
}