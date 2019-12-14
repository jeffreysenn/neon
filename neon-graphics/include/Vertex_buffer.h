#pragma once
#include "neon_core.h"
#include "neon_opengl.h"

namespace neon {
class Vertex_buffer {
public:
	Vertex_buffer();
	~Vertex_buffer();
	void set(int size, const void* data);
	void bind() const;
	void render(GLenum primitive, int start, int count);
private:
	GLuint vertex_buffer_ = 0;
};
}

