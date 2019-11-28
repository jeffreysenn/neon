// neon_testbed.cc

#include <neon_testbed.h>
#include <cassert>

#pragma warning(push)
#pragma warning(disable:4201)

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

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
{
}

bool testbed::enter()
{
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	vertex vertices[] = {
		{ 1.0f, -1.0f, 0xffffffff},
		{ 0.0f, 1.0f, 0xffffffff},
		{-1.0f, -1.0f, 0xffffffff},
	};

	if (!vbo_.create(sizeof(vertices), vertices)) {
		return false;
	}

	if (!program_.create("assets/vertex_shader.glsl", "assets/fragment_shader.glsl")) {
		return false;
	}

	format_.add_attribute(0, 2, GL_FLOAT, false);//x,y, not normalize
	format_.add_attribute(1, 4, GL_UNSIGNED_BYTE, true);//color

	program_.bind();
	GLint projection_index = glGetUniformLocation(program_.id_, "projection");

	glm::mat4 projection(1.0f);
	glUniformMatrix4fv(projection_index, 1, GL_FALSE, glm::value_ptr(projection));

	GLint mod_color_index = glGetUniformLocation(program_.id_, "mod_color");

	float mod_color[] = { 1.0f,1.0f,0.0f,1.0f };
	glUniform4fv(mod_color_index, 1, mod_color);

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

	program_.bind();
	vbo_.bind();
	format_.bind();
	glDrawArrays(GL_TRIANGLES, 0, 3);

	return true;
}
}