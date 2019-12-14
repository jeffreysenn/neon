#pragma once

#include "Program.h"
#include "neon_core.h"
#include "graphics.h"
#include "Vertex_buffer.h"
#include "Texture.h"
#include "Sampler.h"
#include "Vertex_format.h"
#include "Vertex.h"


namespace neon {

struct Test_vert {
	float x, y, u, v;
	float should_draw;
};

class Bitmap_font {
public:
	Bitmap_font();
	Bitmap_font(const char* filename);

	void load_from_file(const char* filename);
	void render(float x, float y, float size, const string& text);
	void flush();

private:
	Program program_;
	Vertex_format format_;
	Vertex_buffer buffer_;
	Texture texture_;
	Sampler sampler_;
	dynamic_array<Test_vert> vertices_;
	glm::mat4 projection_;
};


}