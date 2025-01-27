#version 330 core

out vec4 FragColor;

in vec3 vFragPos;
in vec3 vNormal;
// in vec2 TexCoords;

struct Light {
  vec3 pos;
  vec3 color;
  vec2 atten;
};

#define MAX_LIGHTS 5
uniform Light lights[MAX_LIGHTS];
// uniform Light lightTest;
// uniform Light lights[MAX_LIGHTS];
uniform int lightsNum;
uniform float wireframes;
// uniform vec3 lightPos;
// uniform vec3 lightColor;
uniform vec3 viewPos;
// uniform sampler2D texture1;
uniform vec3 tintColor;
uniform vec2 lightAttenuationSq;
uniform vec3 wireColor;

float invlerp (float from, float to, float value){
  return (value - from) / (to - from);
}

float remap (float origFrom, float origTo, float targetFrom, float targetTo, float value){
  float rel = invlerp(origFrom, origTo, value);
  return mix(targetFrom, targetTo, rel);
}

vec3 attenuateLight (Light light, vec3 fragPos) {
	vec3 toLight = light.pos - vFragPos;
	float distSq = dot(toLight, toLight);
	float atteniation = clamp(remap(light.atten[0], light.atten[1], 1., 0. , distSq), 0., 1.);
	return light.color * atteniation;
}

void main()
{
    // if (wireColor.r > 0) {
    //   FragColor = vec4(wireColor, 1.0);
    //   return;
    // }
    // Ambient
    float ambientStrength = 0.05;
    vec3 ambient = ambientStrength * vec3(1.0);
    // if (lightsNum == 0) {
    //   FragColor = vec4(vec3(1,0,0), 1.); return;
    // }
    // if (lightsNum == 1) {
    //   FragColor = vec4(vec3(0,1,0), 1.); return;
    // }
    // if (lightsNum == 2) {
    //   FragColor = vec4(vec3(0,0,1), 1.); return;
    // }

    vec3 LIGHTING = vec3(0.0);

    // for (int i = 0; i < lightsNum; i++) {
    int i = 0;
      // Diffuse
      // vec3 norm = normalize(vNormal);
      vec3 norm = vNormal;
      vec3 lightDir = normalize(lights[i].pos - vFragPos);
      float diff = max(dot(norm, lightDir), 0.0);
      vec3 diffuse = diff * attenuateLight(lights[i], vFragPos);
      // TODO: discard not enlighten fragments

      // Specular
      float specularStrength = 0.5;
      vec3 viewDir = normalize(viewPos - vFragPos);
      vec3 reflectDir = reflect(-lightDir, norm);
      float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
      vec3 specular = specularStrength * spec * vec3(1.0);

      // vec3 result = (ambient + diffuse + specular) * texture(texture1, TexCoords).rgb;
      LIGHTING += (diffuse + specular) * tintColor;
    // }

    LIGHTING += (ambient * tintColor);
		// if inside a mesh
		// float inside = 1 - step(0, dot(viewDir, norm));
    // FragColor = vec4(result, inside * .3);
    LIGHTING = mix(LIGHTING, vec3(1.), wireframes);
    FragColor = vec4(LIGHTING, 1.);
    // FragColor = vec4(lightsNum / vec3(3), 1.);
		// FragColor = vec4(1.0);
}