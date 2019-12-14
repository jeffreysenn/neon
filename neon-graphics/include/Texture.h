#pragma once
#include "neon_core.h"
#include "neon_opengl.h"

namespace neon {
class Texture {
public:
	Texture();
	~Texture();

	void load_from_file(const char* filename);
	void bind();
	GLuint get() const;
private:
	GLuint texture_;

};
}