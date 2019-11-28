#version 330

uniform vec4 mod_color;

in vec4 f_color;

out vec4 frag_color;

void main() {
	frag_color = f_color * mod_color;
}