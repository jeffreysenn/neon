#pragma once
#include "neon_opengl.h"
#include "neon_core.h"

namespace neon {

namespace shader_util {

enum class Type {
	SHADER,
	PROGRAM,
};

void check_status(Type type, GLuint id);
}
}