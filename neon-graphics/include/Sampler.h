#pragma once
#include "neon_opengl.h"

namespace neon {

class Sampler {
public:
	Sampler();
	~Sampler();
	void set(const GLenum filter,
				const GLenum address_mode_u,
				const GLenum address_mode_v
				);
	void bind() const;
private:
	GLuint sampler_ = 0;
};
}