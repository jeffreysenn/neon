#version 330

uniform sampler2D diffuse;

in vec2 f_texcoord;

out vec4 frag_color;

void main() {
	vec4 color = texture(diffuse, f_texcoord);
	frag_color = color;
}