#pragma once

#include "Bitmap_font.h"
#include "Camera.h"
#include "Camera_controller.h"
#include "Program.h"
#include "Sampler.h"
#include "Shader.h"
#include "Skybox.h"
#include "Skybox_texture.h"
#include "Texture.h"
#include "Vertex.h"
#include "Vertex_buffer.h"
#include "Vertex_format.h"


namespace neon {

class Index_buffer {
public:
	Index_buffer();
	explicit Index_buffer(const GLenum type);
	~Index_buffer();
	void set(const int size, const void* data);
	void bind() const;
	void render(GLenum primitive, int start, int count);

private:
	GLuint index_buffer_ = 0;
	GLenum type_ = GL_UNSIGNED_INT;
};


class Terrain {
public:
	struct Vertex {
		glm::vec3 pos;
		glm::vec2 uv;
		glm::vec3 normal;
	};

public:
	Terrain();
	
	void load_from_file(const char* filename, const char* texture);

	void render(const Camera& cam);

private:
	Program program_;
	Vertex_buffer vertex_buffer_;
	Index_buffer index_buffer_;
	Vertex_format format_;
	Texture texture_;
	Sampler sampler_;
	int index_count_;
};

}