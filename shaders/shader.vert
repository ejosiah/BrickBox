#version 450 core
#pragma debug(on)
#pragma optimize(off)

uniform mat4 MVP;

layout(location = 0) in vec3 p;
layout(location = 4) in vec4 c;
layout(location = 5) in vec2 uv;

smooth out vec4 color;
smooth out vec2 texCood;

void main(){
	color = c;
	texCood = uv;
	gl_Position = MVP * vec4(p, 1.0);
}