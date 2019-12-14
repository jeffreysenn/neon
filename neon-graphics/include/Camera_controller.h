#pragma once
#include "Camera.h"
#include "neon_core.h"

namespace neon {

class Camera_controller {
public:
	Camera_controller(Camera& camera, keyboard& kb, mouse& m);

	void update(const time& dt);
private:
	Camera& camera_;
	keyboard& keyboard_;
	mouse& mouse_;

	glm::vec2 mouse_pos_ = glm::vec2(0.f);
};


}