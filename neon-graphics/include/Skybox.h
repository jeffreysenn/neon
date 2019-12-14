#pragma once
#include "Skybox_texture.h"
#include "Vertex_buffer.h"
#include "graphics.h"
#include "Camera.h"
#include "Vertex_format.h"

namespace neon {

class Skybox {
public:
	Skybox();

	void render(const Camera& camera);

private:
	Skybox_texture cube_map_;
	Vertex_buffer buffer_;
	Vertex_format format_;
	Sampler sampler_;
	Program program_;


};


}