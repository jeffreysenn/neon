#version 330

layout(location=0) in vec3 position;
layout(location=1) in vec4 color;
layout(location=2) in vec2 texcoord;

uniform mat4 camera;

out vec4 f_color;
out vec2 f_texcoord;

void main() {
	gl_Position = camera * vec4(position,1);
	f_color = color;
	f_texcoord = texcoord;
}