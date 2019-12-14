#version 330

layout(location = 0) in vec3 position;

uniform mat4 projection;
uniform mat4 view;

out vec3 f_texcoord;

void main()
{
	gl_Position = projection * view * vec4(position, 1.f);
	f_texcoord = position;
}