#include "Bitmap_font.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace neon {



Bitmap_font::Bitmap_font()
{
	auto vertex_shader = neon::Vertex_shader("assets/vertex_shader_font.glsl");
	auto fragment_shader = neon::Fragment_shader("assets/fragment_shader_font.glsl");
	program_.set(vertex_shader, fragment_shader);
	format_.add_attribute(0, 2, GL_FLOAT, false);
	format_.add_attribute(1, 2, GL_FLOAT, false);
	format_.add_attribute(2, 1, GL_FLOAT, false);
	buffer_.set(512, nullptr);
	sampler_.set(GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
	projection_ = glm::ortho(0.0f, 1280.f, 720.f, 0.f);
}

Bitmap_font::Bitmap_font(const char* filename)
	: Bitmap_font()
{
	load_from_file(filename);
}

void Bitmap_font::load_from_file(const char* filename)
{
	texture_.load_from_file(filename);
}

constexpr int CHARACTERS_PER_ROW = 16;
void Bitmap_font::render(float pos_x, float pos_y, float size, const string& text)
{
	const float duv = 1.f / 16.f;

	for (const auto& character : text) {
		float is_active = 1.f;
		int index = character - ' ';
		if (index < 80) {
			is_active = 0.f;
		}

		int col = index % CHARACTERS_PER_ROW;
		int row = index / CHARACTERS_PER_ROW + 2;

		float u = (float) col / 16.f;
		float v = (float) row / 16.f;

		Test_vert verts[] = {
		{pos_x, pos_y, u, v, is_active},
		{pos_x, pos_y + size, u, v + duv, is_active},
		{pos_x + size, pos_y + size, u + duv, v + duv, is_active},

		{pos_x, pos_y, u, v, is_active},
		{pos_x + size, pos_y + size, u + duv, v + duv, is_active},
		{pos_x + size, pos_y, u + duv, v, is_active},
		};

		for (const auto& vert : verts) {
			vertices_.push_back(vert);
		}

		pos_x += size;
	}
}

void Bitmap_font::flush()
{
	GLsizei size = (GLsizei)(sizeof(Test_vert) * vertices_.size());
	buffer_.set(size, vertices_.data());
	glDisable(GL_DEPTH_TEST);
	program_.bind();
	program_.set_uniform_mat4("projection", projection_);
	buffer_.bind();
	format_.bind();
	texture_.bind();
	sampler_.bind();
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)vertices_.size());
	vertices_.clear();
}

}