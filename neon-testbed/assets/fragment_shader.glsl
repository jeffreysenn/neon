#version 330

uniform vec4 mod_color;
uniform sampler2D diffuse;

in vec4 f_color;
in vec2 f_texcoord;

out vec4 frag_color;

void main() {
	vec4 color = texture(diffuse, f_texcoord);
	frag_color = color * mod_color;
}