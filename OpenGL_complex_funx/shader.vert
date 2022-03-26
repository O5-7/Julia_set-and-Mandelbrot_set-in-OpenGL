#version 400 core
layout (location = 0) in vec3 aPos;
out vec2 pos;

void main()
{
	pos = vec2(aPos.x, aPos.y);
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}