#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 viewPos;

uniform float normalsMult;

out vec3 vFragPos;
out vec3 vNormal;
out float vBlendFace;

void main() {
	vFragPos = vec3(model * vec4(aPos, 1.0));
	vNormal = mat3(transpose(inverse(model))) * aNormal * normalsMult;
	// vNormal = aNormal;
	// TexCoords = aTexCoords;

	vec4 pos = projection * view * vec4(vFragPos, 1.0);
	vBlendFace = step(dot(vNormal, pos.xyz - viewPos), 0);
	gl_Position = pos;
}
