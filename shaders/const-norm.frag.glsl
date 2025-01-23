#version 330 core

out vec4 FragColor;

in vec3 vFragPos;
in vec3 vNormal;
// in vec2 TexCoords;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;
// uniform sampler2D texture1;
uniform vec3 tintColor;
uniform vec2 lightAttenuation;

float invlerp (float from, float to, float value){
  return (value - from) / (to - from);
}

float remap (float origFrom, float origTo, float targetFrom, float targetTo, float value){
  float rel = invlerp(origFrom, origTo, value);
  return mix(targetFrom, targetTo, rel);
}

vec3 attenuateLight (vec3 lightPos, vec3 lightColor, vec3 fragPos) {
	float dist = length(lightPos - vFragPos);
	float atteniation = clamp(remap(lightAttenuation[0], lightAttenuation[1], 1., 0. , dist), 0., 1.);
	return lightColor * atteniation;
}

void main()
{
    // Ambient
    float ambientStrength = 0.03;
    vec3 ambient = ambientStrength * vec3(1.0);

    // Diffuse
    vec3 norm = normalize(vNormal);
    vec3 lightDir = normalize(lightPos - vFragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * attenuateLight(lightPos, lightColor, vFragPos);

    // Specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - vFragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * vec3(1.0);

    // vec3 result = (ambient + diffuse + specular) * texture(texture1, TexCoords).rgb;
    vec3 result = (ambient + diffuse + specular) * tintColor;
    FragColor = vec4(result, 1.0);
		// FragColor = vec4(1.0);
}