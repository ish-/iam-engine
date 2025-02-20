#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 viewPos;
uniform int instancesCount;

uniform float normalsMult;

out vec3 vFragPos;
out vec3 vNormal;
// out float vBlendFace;

layout (location = 3) in vec4 instanceMat0; // mat4 first column
layout (location = 4) in vec4 instanceMat1;
layout (location = 5) in vec4 instanceMat2;
layout (location = 6) in vec4 instanceMat3;

void main() {
	mat4 _model = model;
	if (instancesCount > 1) {
		_model = mat4(instanceMat0, instanceMat1, instanceMat2, instanceMat3);
	}
	vFragPos = vec3(_model * vec4(aPos, 1.0));
	vNormal = mat3(transpose(inverse(mat3(_model)))) * aNormal;
	// vNormal = aNormal;
	// TexCoords = aTexCoords;

	vec4 pos = projection * view * vec4(vFragPos, 1.0);
	// vBlendFace = step(dot(vNormal, pos.xyz - viewPos), 0);
	gl_Position = pos;
}
