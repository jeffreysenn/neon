// neon_testbed.h

#ifndef NEON_TESTBED_H_INCLUDED
#define NEON_TESTBED_H_INCLUDED

#include <neon_core.h>
#include <neon_opengl.h>

#include "graphics.h"

namespace test {

struct cube_vertex {
	float x, y, z;
};

struct vertex {
	float x;
	float y;
	float z;
	neon::uint32 color;
	float u;
	float v;
};

class testbed : public neon::application {
public:
	testbed();
	virtual bool enter() final;
	virtual void exit() final;
	virtual bool tick(const neon::time& dt) final;

private:
	neon::Program program_;
	neon::Vertex_format cube_format_;
	neon::Texture texture_;
	neon::Sampler sampler_;
	neon::Vertex_buffer cube_buffer_;
	float rot_degree_ = 0;
	neon::Bitmap_font font_;
	neon::Camera camera_;
	neon::Camera_controller camera_controller_;
	neon::Skybox skybox_;
	neon::Terrain terrain_;
};
} // !neon

#endif // !NEON_TESTBED_H_INCLUDED
