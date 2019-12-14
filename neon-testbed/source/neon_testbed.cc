// neon_testbed.cc

#include <neon_testbed.h>
#include <cassert>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

namespace neon {
application* application::create(int& width, int& height, string& title)
{
	width = 1280; height = 720;
	title = "neon-testbed";
	return new test::testbed;
}
}

namespace test {
testbed::testbed()
	: camera_controller_(camera_, keyboard_, mouse_)
{
}

bool testbed::enter()
{
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	vertex cube_vertices[] = {
	{-1.0f,-1.0f,-1.0f, 0xffffff00, 1.f, 0.0f, },
	{-1.0f,-1.0f, 1.0f, 0xffffff00, 0.5f, 1.0f	},
	{-1.0f, 1.0f, 1.0f, 0xffffff00, 0.0f, 0.0f	},
	{1.0f, 1.0f,-1.0f, 	0xffffffff, 1.f, 0.0f },
	{-1.0f,-1.0f,-1.0f,	0xffffffff, 0.5f, 1.0f },
	{-1.0f, 1.0f,-1.0f,	0xffffffff, 0.0f, 0.0f },
	{1.0f,-1.0f, 1.0f,	0xffffffff, 1.f, 0.0f },
	{-1.0f,-1.0f,-1.0f,	0xffffffff, 0.5f, 1.0f },
	{1.0f,-1.0f,-1.0f,	0xffffffff, 0.0f, 0.0f },
	{1.0f, 1.0f,-1.0f,	0xffffffff, 1.f, 0.0f,},
	{1.0f,-1.0f,-1.0f,	0xffffffff, 0.5f, 1.0f},
	{-1.0f,-1.0f,-1.0f,	0xffffffff, 0.0f, 0.0f},
	{-1.0f,-1.0f,-1.0f,	0xffffffff, 1.f, 0.0f },
	{-1.0f, 1.0f, 1.0f,	0xffffffff, 0.5f, 1.0f},
	{-1.0f, 1.0f,-1.0f,	0xffffffff, 0.0f, 0.0f},
	{1.0f,-1.0f, 1.0f,	0xffffffff, 1.f, 0.0f },
	{-1.0f,-1.0f, 1.0f,	0xffffffff, 0.5f, 1.0f},
	{-1.0f,-1.0f,-1.0f,	0xffffffff, 0.0f, 0.0f},
	{-1.0f, 1.0f, 1.0f,	0xffffffff, 1.f, 0.0f,},
	{-1.0f,-1.0f, 1.0f,	0xffffffff, 0.5f, 1.0f},
	{1.0f,-1.0f, 1.0f,	0xffffffff, 0.0f, 0.0f},
	{1.0f, 1.0f, 1.0f,	0xffffffff, 1.f, 0.0f },
	{1.0f,-1.0f,-1.0f,	0xffffffff, 0.5f, 1.0f},
	{1.0f, 1.0f,-1.0f,	0xffffffff, 0.0f, 0.0f},
	{1.0f,-1.0f,-1.0f,	0xffffffff, 1.f, 0.0f },
	{1.0f, 1.0f, 1.0f,	0xffffffff, 0.5f, 1.0f},
	{1.0f,-1.0f, 1.0f,	0xffffffff, 0.0f, 0.0f},
	{1.0f, 1.0f, 1.0f,	0xffffffff, 1.f, 0.0f,},
	{1.0f, 1.0f,-1.0f,	0xffffffff, 0.5f, 1.0f},
	{-1.0f, 1.0f,-1.0f,	0xffffffff, 0.0f, 0.0f},
	{1.0f, 1.0f, 1.0f,	0xffffffff, 1.f, 0.0f },
	{-1.0f, 1.0f,-1.0f,	0xffffffff, 0.5f, 1.0f},
	{-1.0f, 1.0f, 1.0f,	0xffffffff, 0.0f, 0.0f},
	{1.0f, 1.0f, 1.0f,	0xffffffff, 1.f, 0.0f },
	{-1.0f, 1.0f, 1.0f,	0xffffffff, 0.5f, 1.0f},
	{1.0f,-1.0f, 1.0f,	0xffffffff, 0.0f, 0.0f},
	};

	cube_buffer_.set(sizeof(cube_vertices), cube_vertices);
	auto vertex_shader = neon::Vertex_shader("assets/vertex_shader.glsl");
	auto fragment_shader = neon::Fragment_shader("assets/fragment_shader.glsl");
	program_.set(vertex_shader, fragment_shader);

	cube_format_.add_attribute(0, 3, GL_FLOAT, false);//x,y, not normalize
	cube_format_.add_attribute(1, 4, GL_UNSIGNED_BYTE, true);//color
	cube_format_.add_attribute(2, 2, GL_FLOAT, false);

	texture_.load_from_file("assets/test.png");
	sampler_.set(GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
	program_.bind();
	program_.set_uniform_vec4("mod_color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	font_.load_from_file("assets/Anikki_square_8x8.png");

	camera_.set_perspective(glm::radians(45.f), 16.f / 9.f, 0.1f, 100.f);

	terrain_.load_from_file("assets/heightmap/heightmap.png",
							"assets/heightmap/texture.png");


	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		//...
	}

	return true;
}

void testbed::exit()
{
}

bool testbed::tick(const neon::time& dt)
{
	if (keyboard_.is_pressed(neon::KEYCODE_ESCAPE)) {
		return false;
	}

	glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	font_.render(100, 100, 50, "test  sdfad");
	camera_controller_.update(dt);

	//program_.bind();
	////rot_degree_ = (rot_degree_ + .05f);
	//const auto model = glm::mat4(1.f);
	////const auto projection = glm::perspective(glm::radians(60.f), 4.f / 3.f, 0.1f, 100.f);
	//const auto camera = camera_.get_camera_matrix();
	////const auto rot = glm::rotate(glm::mat4(1.f), rot_degree_, glm::vec3(0, 1, 0));
	//const auto mvp = camera * model;
	//program_.set_uniform_mat4("camera", mvp);

	//cube_buffer_.bind();
	//cube_format_.bind();
	//texture_.bind();
	//sampler_.bind();

	skybox_.render(camera_);
	terrain_.render(camera_);

	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glDrawArrays(GL_TRIANGLES, 0, 36);

	font_.flush();

	return true;
}
}