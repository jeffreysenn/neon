#include "Texture.h"

#include <stdexcept>
#include "stb_image.h"

#include "neon_error.h"

namespace neon {

Texture::Texture()
{
	glGenTextures(1, &texture_);
	check_gl_error();
}

Texture::~Texture()
{
	glDeleteTextures(1, &texture_);
}

void Texture::load_from_file(const char* filename)
{
	dynamic_array<uint8> file_content;
	if (!file_system::read_file_content(filename, file_content)) {
		throw std::runtime_error("could not read file: " + std::string(filename));
	}
	int width = 0, height = 0, components = 0;
	auto bitmap = stbi_load_from_memory(file_content.data(),
		(int)file_content.size(),
										&width,
										&height,
										&components,
										STBI_rgb_alpha);
	if (!bitmap) {
		throw std::runtime_error("could not read image: " + std::string(filename));
	}

	glBindTexture(GL_TEXTURE_2D, texture_);
	glTexImage2D(GL_TEXTURE_2D,
				  0,
				  GL_RGBA,
				  width,
				  height,
				  0,
				  GL_RGBA,
				  GL_UNSIGNED_BYTE,
				  bitmap);
	check_gl_error();
	stbi_image_free(bitmap);
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, texture_);
}

GLuint Texture::get() const
{
	return texture_;
}

}