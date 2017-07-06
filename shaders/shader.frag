#version 450 core
#pragma debug(on)
#pragma optimize(off)

layout(binding=0) uniform sampler2D img;

uniform bool useTexture;

in VERTEX {
	smooth vec3 position;
	smooth vec3 normal;
	smooth vec2 texCoord;
	smooth vec4 color;
} vertex;

out vec4 fcolor;

void main(){
	if(useTexture){
		fcolor = texture(img, vertex.texCoord);
	}else{
		fcolor = vertex.color;
	}
}
