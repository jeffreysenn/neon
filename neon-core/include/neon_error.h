#include "neon_opengl.h"
#include <stdio.h>
#include <exception>
#include <string>

namespace neon {

class Gl_error : public std::exception {
public:
	Gl_error() = default;
	explicit Gl_error(const std::string& message);
	virtual ~Gl_error() = default;

	virtual const char* what() const noexcept override;

private:
	std::string message_{};
};


/**
 * Checks the latest gl error. 
 * Throws an exception if there is an error. 
 */
void check_gl_error();


#ifdef GL_VERSION_4_3
/**
 * requires OpenGL version 4.3 to register the callback.
 */
void message_callback(GLenum source,
					 GLenum type,
					 GLuint id,
					 GLenum severity,
					 GLsizei length,
					 const GLchar* message,
					 const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: ** GL ERROR ** type = 0x%x, severity = 0x%x, message = %s\n", type, severity, message);
}
#endif
}
