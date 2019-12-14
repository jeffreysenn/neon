#include "Vertex_format.h"
#include <cassert>

namespace neon {

namespace {

uint32_t size_of_gl_type(GLenum type)
{
	switch (type) {
	case GL_FLOAT:
		return sizeof(GLfloat);
	case GL_UNSIGNED_BYTE:
		return sizeof(uint8_t);
	}
	assert(false && "incorrect type");
	return 0;
}
}

void Vertex_format::add_attribute(uint32_t index, uint32_t size, GLenum type, bool normalized)
{
	const attribute attribute{ index, size, type, normalized };
	add_attribute(attribute);
}

void Vertex_format::add_attribute(const attribute& attribute)
{
	assert(attribute_count_ < ATTRIBUTE_COUNT);
	uint32_t at = attribute_count_++;
	attributes_[at] = attribute;
	attributes_[at].offset = stride_;

	stride_ += attribute.size * size_of_gl_type(attribute.type);
}

bool Vertex_format::is_valid() const
{
	return attribute_count_ > 0;
}

void Vertex_format::bind() const
{
	for (uint32_t index = 0; index < ATTRIBUTE_COUNT; index++) {
		glDisableVertexAttribArray(index);
	}

	for (uint32_t index = 0; index < attribute_count_; index++) {
		const attribute& attrib = attributes_[index];
		glEnableVertexAttribArray(attrib.index);
		glVertexAttribPointer(attrib.index, attrib.size, attrib.type, attrib.normalized, stride_, (const void*)attrib.offset);
	}
}

}