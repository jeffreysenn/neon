#include "Vertex_buffer.h"
#include "neon_error.h"

namespace neon {

Vertex_buffer::Vertex_buffer()
{
	glGenBuffers(1, &vertex_buffer_);
	check_gl_error();
}

Vertex_buffer::~Vertex_buffer()
{
	glDeleteBuffers(1, &vertex_buffer_);
}

void Vertex_buffer::set(int size, const void* data)
{
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	check_gl_error();
};

void Vertex_buffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
}

void Vertex_buffer::render(GLenum primitive, int start, int count)
{
	glDrawArrays(primitive, start, count);
}
}