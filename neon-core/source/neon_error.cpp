#include "neon_error.h"

#include <stdio.h>

namespace neon {

Gl_error::Gl_error(const std::string& message)
{
	message_ = message;
}

const char* Gl_error::what() const noexcept
{
	return message_.c_str();
}

void check_gl_error()
{
	GLenum errorCode;
	while ((errorCode = glGetError()) != GL_NO_ERROR) {
		std::string error;
		switch (errorCode) {
		case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
		case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
		case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
		case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
		}
		throw Gl_error(error);
	}
}
}