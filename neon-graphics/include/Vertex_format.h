#pragma once
#include <cstdint>

#include "neon_opengl.h"

namespace neon {

constexpr uint32_t ATTRIBUTE_COUNT = 4;

class Vertex_format {
public:
	struct attribute {
		GLuint index = 0;
		GLuint size = 0;
		GLenum type = 0;
		GLboolean normalized = false;
		uint64_t offset = 0;
	};

	void add_attribute(uint32_t index, uint32_t size, GLenum type, bool normalized);
	void add_attribute(const attribute& attribute);

	bool is_valid() const;
	void bind() const;

private:
	GLsizei stride_ = 0;
	uint32_t attribute_count_ = 0;
	attribute attributes_[ATTRIBUTE_COUNT]{};
};

}