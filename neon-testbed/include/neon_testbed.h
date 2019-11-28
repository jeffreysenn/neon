// neon_testbed.h

#ifndef NEON_TESTBED_H_INCLUDED
#define NEON_TESTBED_H_INCLUDED

#include <neon_core.h>
#include <neon_opengl.h>

#include "neon_graphics.h"

namespace test {
struct vertex {
	float x_;
	float y_;
	neon::uint32 color;
};

class testbed : public neon::application {
public:
	testbed();
	virtual bool enter() final;
	virtual void exit() final;
	virtual bool tick(const neon::time& dt) final;

private:

private:
	neon::shader_program program_;
	neon::vertex_buffer vbo_;
	neon::vertex_format format_;
};
} // !neon

#endif // !NEON_TESTBED_H_INCLUDED
