#include "Skybox.h"
#include "neon_error.h"
#include <stdexcept>
namespace neon {



Skybox::Skybox()
{
	cube_map_.load_from_file(nullptr);

	constexpr float Q = 100.f;
	const glm::vec3 vertices[] =
	{
		// x positive
		{  Q,  Q, -Q },
		{  Q,  Q,  Q },
		{  Q, -Q,  Q },
		{  Q, -Q,  Q },
		{  Q, -Q, -Q },
		{  Q,  Q, -Q },

		// x negative
		{ -Q,  Q,  Q },
		{ -Q,  Q, -Q },
		{ -Q, -Q, -Q },
		{ -Q, -Q, -Q },
		{ -Q, -Q,  Q },
		{ -Q,  Q,  Q },

		// y positive
		{ -Q,  Q,  Q },
		{  Q,  Q,  Q },
		{  Q,  Q, -Q },
		{  Q,  Q, -Q },
		{ -Q,  Q, -Q },
		{ -Q,  Q,  Q },

		// y negative
		{ -Q, -Q, -Q },
		{  Q, -Q, -Q },
		{  Q, -Q,  Q },
		{  Q, -Q,  Q },
		{ -Q, -Q,  Q },
		{ -Q, -Q, -Q },

		// z positive
		{ -Q,  Q, -Q },
		{  Q,  Q, -Q },
		{  Q, -Q, -Q },
		{  Q, -Q, -Q },
		{ -Q, -Q, -Q },
		{ -Q,  Q, -Q },

		// z negative
		{  Q,  Q,  Q },
		{ -Q,  Q,  Q },
		{ -Q, -Q,  Q },
		{ -Q, -Q,  Q },
		{  Q, -Q,  Q },
		{  Q,  Q,  Q },
	};

	buffer_.set(sizeof(vertices), vertices);
	format_.add_attribute(0, 3, GL_FLOAT, false);

	Vertex_shader vertex_shader("assets/skybox/vertex_shader.glsl");
	Fragment_shader fragment_shader("assets/skybox/fragment_shader.glsl");
	program_.set(vertex_shader, fragment_shader);
	sampler_.set(GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
}

void Skybox::render(const Camera& camera)
{
	buffer_.bind();
	format_.bind();
	cube_map_.bind();
	sampler_.bind();
	program_.bind();
	program_.set_uniform_mat4("projection", camera.get_projection());
	auto view = camera.get_view();
	view[3] = glm::vec4(0.f, 0.f, 0.f, 1.f);
	program_.set_uniform_mat4("view", view);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

}