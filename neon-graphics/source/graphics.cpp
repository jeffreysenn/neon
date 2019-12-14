#include "graphics.h"

#include <stdexcept>
#include "neon_error.h"

namespace neon {



Terrain::Terrain()
{
}

void Terrain::load_from_file(const char* filename, const char* texture)
{
	texture_.load_from_file(texture);

	image heightmap;
	if (!heightmap.create_from_file(filename)) {
		throw std::runtime_error("could not open image: " + std::string(filename));
	}
	const int32 width = heightmap.width();
	const int32 height = heightmap.height();
	const int32 stride = width * 4;
	dynamic_array<Vertex> vertices;

	const float texture_cell_size = 1.f / static_cast<float>(width);
	const float cell_size = .1f;
	const float hight_ratio = .01f;
	for (int32 z = 0; z < height; ++z) {
		for (int32 x = 0; x < width; ++x) {
			const uint32 offset = x * 4 + z * stride;
			const uint8* rgba = heightmap.data() + offset;
			Vertex vertex{ glm::vec3((float)x * cell_size, hight_ratio * (float)rgba[1], (float)z * cell_size)
			, glm::vec2(x * texture_cell_size, z * texture_cell_size) };
			vertices.push_back(vertex);
		}
	}

	vertex_buffer_.set(vertices.size() * sizeof(Vertex), vertices.data());

	dynamic_array<uint32> index_array;

	for (auto row = 0; row < height - 1; ++row) {
		for (auto col = 0; col < width - 1; ++col) {
			index_array.push_back(row * width + col);
			index_array.push_back((row + 1) * width + col);
			index_array.push_back((row + 1) * width + col + 1);

			index_array.push_back(row * width + col);
			index_array.push_back((row + 1) * width + col + 1);
			index_array.push_back(row * width + col + 1);
		}
	}

	index_count_ = index_array.size();
	index_buffer_.set(index_count_ * sizeof(uint32), index_array.data());
	format_.add_attribute(0, 3, GL_FLOAT, false);
	format_.add_attribute(1, 2, GL_FLOAT, false);
	format_.add_attribute(2, 3, GL_FLOAT, false);
	sampler_.set(GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);

	Vertex_shader vertex_shader("assets/heightmap/vertex_shader.glsl");
	Fragment_shader fragment_shader("assets/heightmap/fragment_shader.glsl");
	program_.set(vertex_shader, fragment_shader);
}

void Terrain::render(const Camera& cam)
{
	program_.bind();
	program_.set_uniform_mat4("camera", cam.get_camera_matrix());
	texture_.bind();
	sampler_.bind();
	vertex_buffer_.bind();
	format_.bind();
	index_buffer_.bind();
	index_buffer_.render(GL_TRIANGLES, 0, index_count_);
}


Index_buffer::Index_buffer()
{
	glGenBuffers(1, &index_buffer_);
	check_gl_error();
}

Index_buffer::Index_buffer(const GLenum type)
	: Index_buffer()
{
	type_ = type;
}

Index_buffer::~Index_buffer()
{
	if (index_buffer_ != 0) {
		glDeleteBuffers(1, &index_buffer_);
	}
}

void Index_buffer::set(const int size, const void* data)
{
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	check_gl_error();
}

void Index_buffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_);
}

void Index_buffer::render(GLenum primitive, int start, int count)
{
	glDrawElements(primitive, count, type_, (const void*) nullptr);
}

}