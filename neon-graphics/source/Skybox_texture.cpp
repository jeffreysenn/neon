#include "Skybox_texture.h"
#include "neon_error.h"
#include <stdexcept>

namespace neon {

Skybox_texture::Skybox_texture()
{
	glGenTextures(1, &texture_);
	check_gl_error();
}

Skybox_texture::~Skybox_texture()
{
	if (texture_ != 0) {
		glDeleteTextures(1, &texture_);
	}
}

void Skybox_texture::load_from_file(const char* filenames[6])
{
	const char* names[] = {
	"assets/skybox/xpos.png",
	"assets/skybox/xneg.png",
	"assets/skybox/ypos.png",
	"assets/skybox/yneg.png",
	"assets/skybox/zpos.png",
	"assets/skybox/zneg.png",
	};

	image sides[6];
	for (int i = 0; i < 6; ++i) {
		if (!sides[i].create_from_file(names[i])) {
			throw std::runtime_error("could not load cubemap image");
		}
	}

	const int width = sides[0].width();
	const int height = sides[0].height();
	for (int i = 0; i < 6; ++i) {
		if (!(width == sides[i].width() && height == sides[i].height())) {
			throw std::runtime_error("cubemap sizes are different");
		}
	}

	glBindTexture(GL_TEXTURE_CUBE_MAP, texture_);
	for (int i = 0; i < 6; ++i) {
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					 0,
					 GL_RGBA,
					 width,
					 height,
					 0,
					 GL_RGBA,
					 GL_UNSIGNED_BYTE,
					 sides[i].data());
	}
	check_gl_error();
}

void Skybox_texture::bind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture_);
}

GLuint Skybox_texture::get() const
{
	return texture_;
}

}