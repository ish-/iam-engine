#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float normalsMult;

out vec3 vFragPos;
out vec3 vNormal;

void main() {
	vFragPos = vec3(model * vec4(aPos, 1.0));
	vNormal = mat3(transpose(inverse(model))) * aNormal * normalsMult;
	// vNormal = aNormal;
	// TexCoords = aTexCoords;

	gl_Position = projection * view * vec4(vFragPos, 1.0);
}
