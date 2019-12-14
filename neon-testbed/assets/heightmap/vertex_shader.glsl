#version 330
// heightmap shader

layout(location=0) in vec3 position;
layout(location=1) in vec2 texcoord;
layout(location=2) in vec3 normal;

uniform mat4 camera;

out vec2 f_texcoord;

void main() {
	gl_Position = camera * vec4(position, 1);
	f_texcoord = texcoord;
}