#version 330

layout(location=0) in vec2 position;
layout(location=1) in vec2 texcoord;
layout(location=2) in float is_active;

uniform mat4 projection;

out vec2 f_texcoord;
out float f_is_active;

void main() {
	gl_Position = projection * vec4(position, 0, 1);
	f_texcoord = texcoord;
	f_is_active = is_active;
}