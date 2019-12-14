#pragma once
#include "neon_core.h"
#include "neon_opengl.h"

namespace neon {

class Shader {
public:
	Shader() = default;
	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;
	Shader(Shader&& move) noexcept;
	Shader& operator=(Shader&& move) noexcept;
	virtual ~Shader();
	void load_from_file(const string& filename);
	GLuint get() const;
private:
	void set(const GLchar* source);
protected:
	GLuint shader_ = 0;
public:
	friend void swap(Shader& lhs, Shader& rhs) noexcept;
};

class Vertex_shader : public Shader {
public:
	Vertex_shader();
	explicit Vertex_shader(const string& filename);
};

class Fragment_shader : public Shader {
public:
	Fragment_shader();
	explicit Fragment_shader(const string& filename);
};
}
