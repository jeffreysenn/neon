#include "Camera_controller.h"

namespace neon {
Camera_controller::Camera_controller(Camera& camera, keyboard& kb, mouse& m)
	: camera_(camera)
	, keyboard_(kb)
	, mouse_(m)
{
}

void Camera_controller::update(const time& dt)
{
	constexpr float camera_speed = 5.f;
	const float amount = camera_speed * dt.as_seconds();

	if (keyboard_.is_down(KEYCODE_W)) {
		camera_.forward(-amount);
	}

	if (keyboard_.is_down(KEYCODE_S)) {
		camera_.forward(amount);
	}

	if (keyboard_.is_down(KEYCODE_A)) {
		camera_.sidestep(-amount);
	}

	if (keyboard_.is_down(KEYCODE_D)) {
		camera_.sidestep(amount);
	}

	if (keyboard_.is_down(KEYCODE_SPACE)) {
		camera_.go_up(amount);
	}

	if (mouse_.is_down(MOUSE_BUTTON_RIGHT)) {
		glm::vec2 new_mouse_pos;
		new_mouse_pos.x = mouse_.x_;
		new_mouse_pos.y = mouse_.y_;
		auto delta_mouse_pos = new_mouse_pos - mouse_pos_;

		camera_.rotate_y(glm::radians(delta_mouse_pos.x) * dt.as_seconds());
		camera_.rotate_x(glm::radians(delta_mouse_pos.y) * dt.as_seconds());
	}
	mouse_pos_ = glm::vec2((float)mouse_.x_, (float)mouse_.y_);

	camera_.update();
}
}