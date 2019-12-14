#pragma once
#include "neon_core.h"
#include "neon_opengl.h"

namespace neon {

class Skybox_texture {
public:
	Skybox_texture();
	~Skybox_texture();
	void load_from_file(const char* filenames[6]);
	void bind();
	GLuint get() const;
private:
	GLuint texture_;
};


}