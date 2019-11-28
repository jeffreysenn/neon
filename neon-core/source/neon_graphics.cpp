#include "neon_graphics.h"
#include <cassert>
#include <stdexcept>

namespace neon {

bool vertex_buffer::create(const int size, const void* data)
{
	glGenBuffers(1, &id_);
	glBindBuffer(GL_ARRAY_BUFFER, id_);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	GLenum err = glGetError();
	return err == GL_NO_ERROR;
};

bool vertex_buffer::is_valid() const
{
	return id_ != 0;
};

void vertex_buffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, id_);
};

void vertex_buffer::destroy()
{
	if (!is_valid()) {
		return;
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &id_);
	id_ = 0;
};

namespace {
GLuint create_shader(GLenum type, const char* sourse)
{
	GLuint id = glCreateShader(type);
	glShaderSource(id, 1, &sourse, nullptr);
	glCompileShader(id);
	return id;
}

GLuint create_program(GLuint vid, GLuint fid)
{
	GLuint id = glCreateProgram();
	glAttachShader(id, vid);
	glAttachShader(id, fid);
	glLinkProgram(id);

	GLint status = GL_TRUE;
	glGetProgramiv(id, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {

		char vsh_err[1024] = {};
		char fsh_err[1024] = {};
		char sh_err[1024] = {};

		glGetShaderInfoLog(vid, sizeof(vsh_err), nullptr, vsh_err);
		glGetShaderInfoLog(vid, sizeof(fsh_err), nullptr, fsh_err);
		glGetProgramInfoLog(id, sizeof(sh_err), nullptr, sh_err);

		assert(false);

		glDeleteProgram(id);
		id = 0;
	}
	glDetachShader(id, vid);
	glDetachShader(id, fid);
	glDeleteShader(vid);
	glDeleteShader(fid);
	return id;
}
}

shader_program::shader_program() : id_(0) {}

bool shader_program::create(const string& vertex_shader_filename, const string& fragment_shader_filename)
{
	if (is_valid()) {
		return false;
	}

	dynamic_array<uint8> vertex_shader_file_content;
	if (!file_system::read_file_content(vertex_shader_filename, vertex_shader_file_content)) {
		return false;
	}

	vertex_shader_file_content.push_back(0);

	const char* vertex_shader_Sourse = (const char*)vertex_shader_file_content.data();

	dynamic_array<uint8> fragment_shader_file_content;
	if (!file_system::read_file_content(fragment_shader_filename, fragment_shader_file_content)) {
		return false;
	}
	fragment_shader_file_content.push_back(0);

	const char* fragment_shader_sourse = (const char*)fragment_shader_file_content.data();

	GLuint vid = create_shader(GL_VERTEX_SHADER, vertex_shader_Sourse);
	GLuint fid = create_shader(GL_FRAGMENT_SHADER, fragment_shader_sourse);
	id_ = create_program(vid, fid);

	GLenum error = glGetError();
	return error == GL_NO_ERROR;
}

void shader_program::destroy()
{
	if (!is_valid()) {
		return;
	}
	glDeleteProgram(id_);
	id_ = 0;
}
bool shader_program::is_valid() const
{
	return id_ != 0;
}

void shader_program::bind() const
{
	glUseProgram(id_);
}

namespace {
uint32 size_of_gl_type(GLenum type)
{
	switch (type) {
	case GL_FLOAT:
		return sizeof(GLfloat);
	case GL_UNSIGNED_BYTE:
		return sizeof(uint8);
	}
	assert(false);
	return 0;
}
}

void vertex_format::add_attribute(const uint32 index, const uint32 size, const GLenum type, const bool normalized)
{
	const attribute attribute { index, size, type, normalized };
	add_attribute(attribute);
}

void vertex_format::add_attribute(const attribute& attribute)
{
	assert(attribute_count_ < ATTRIBUTE_COUNT);
	uint32 at = attribute_count_++;
	attributes_[at] = attribute;
	attributes_[at].offset = stride_;

	stride_ += attribute.size * size_of_gl_type(attribute.type);
}

bool vertex_format::is_valid() const
{
	return attribute_count_ > 0;
}

void vertex_format::bind() const
{
	// TODO: why ATTRIBUTE_COUNT?
	for (uint32 index = 0; index < ATTRIBUTE_COUNT; index++) {
		glDisableVertexAttribArray(index);
	}

	for (uint32 index = 0; index < attribute_count_; index++) {
		const attribute& attrib = attributes_[index];
		glEnableVertexAttribArray(attrib.index);
		glVertexAttribPointer(attrib.index, attrib.size, attrib.type, attrib.normalized, stride_, (const void*)attrib.offset);
	}
};
}