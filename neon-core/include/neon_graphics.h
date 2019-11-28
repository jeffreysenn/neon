#ifndef NEON_GRAPHICS_H_INCLUDED
#define NEON_GRAPHICS_H_INCLUDED

#include <neon_core.h>
#include <neon_opengl.h>

namespace neon {

class vertex_buffer {
public:
	vertex_buffer() = default;
	bool create(const int size, const void* data);
	void destroy();
	bool is_valid() const;
	void bind() const;

private:
	GLuint id_ = 0;
};

struct shader_program {
	shader_program();

	bool create(const string& vertex_shader_filename, const string& fragment_shader_filename);
	void destroy();
	bool is_valid() const;
	void bind() const;

	GLuint id_;
};

constexpr uint32 ATTRIBUTE_COUNT = 4;

struct vertex_format {
	struct attribute {
		GLuint index = 0;
		GLuint size = 0;
		GLenum type = 0;
		GLboolean normalized = false;
		uint64 offset = 0;
	};

	void add_attribute(const uint32 index, const uint32 size, const GLenum type, const bool normalized);
	void add_attribute(const attribute& attribute);

	bool is_valid() const;
	void bind() const;

	GLsizei stride_ = 0;
	uint32 attribute_count_ = 0;
	attribute attributes_[ATTRIBUTE_COUNT]{};
};
}
#endif

// !NEON_GRAPHICS_H_INCLUDED
