#include "Sampler.h"
#include "neon_error.h"

namespace neon {

Sampler::Sampler()
{
	glGenSamplers(1, &sampler_);
	check_gl_error();
}

Sampler::~Sampler()
{
	glDeleteSamplers(0, &sampler_);
}

void Sampler::set(const GLenum filter, const GLenum address_mode_u, const GLenum address_mode_v)
{
	bind();
	glSamplerParameteri(sampler_, GL_TEXTURE_MIN_FILTER, filter);
	glSamplerParameteri(sampler_, GL_TEXTURE_MAG_FILTER, filter);
	glSamplerParameteri(sampler_, GL_TEXTURE_WRAP_S, address_mode_u);
	glSamplerParameteri(sampler_, GL_TEXTURE_WRAP_T, address_mode_v);
	check_gl_error();
}

void Sampler::bind() const
{
	glBindSampler(0, sampler_);
}


}