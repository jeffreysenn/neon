#version 330

uniform sampler2D diffuse;

in vec2 f_texcoord;
in float f_is_active;

out vec4 frag_color;

void main() {
	vec4 tex_color = texture(diffuse, f_texcoord);
	if (f_is_active == 0.f && tex_color.g == 0) {
		discard;
	}

	frag_color = tex_color;
}