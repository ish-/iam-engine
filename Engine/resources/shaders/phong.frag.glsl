#version 330 core

out vec4 FragColor;

in vec3 vFragPos;
in vec3 vNormal;
in vec2 vUv;
in float vBlendFace;

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
uniform vec3 tintColor;
uniform vec2 lightAttenuationSq;
uniform vec3 wireColor;

uniform sampler2D sAlbedo;
uniform float uShininess;
uniform vec3 uSpecularColor;
uniform bool uWorldAlignedTexture;
uniform float uUvScale;

float invlerp (float from, float to, float value){
  return (value - from) / (to - from);
}

float remap (float origFrom, float origTo, float targetFrom, float targetTo, float value){
  float rel = invlerp(origFrom, origTo, value);
  return mix(targetFrom, targetTo, rel);
}

float attenuateLight (Light light, vec3 fragPos) {
	vec3 toLight = light.pos - vFragPos;
	float distSq = dot(toLight, toLight);
	return clamp(remap(light.atten[0], light.atten[1], 1., 0. , distSq), 0., 1.);
}

vec3 blendWeights(vec3 normal) {
    vec3 absNormal = abs(normal);
    return absNormal / (absNormal.x + absNormal.y + absNormal.z);
}

vec2 getTexCoord(vec3 position, int axis) {
    if (axis == 0) return position.zy; // X projection
    if (axis == 1) return position.xz; // Y projection
    return position.xy;                // Z projection
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

    vec3 LIGHTING = vec3(0.0);

    for (int i = 0; i < lightsNum; i++) {
    // int i = 0;
      // Diffuse
      // vec3 norm = normalize(vNormal);
      vec3 norm = vNormal;
      vec3 lightDir = normalize(lights[i].pos - vFragPos);
      // float diff = max(dot(norm, lightDir), 0.0);
      float diff = abs(dot(norm, lightDir));
      float attenuation = attenuateLight(lights[i], vFragPos);
      vec3 diffuse = diff * attenuation * lights[i].color;
      // TODO: discard not enlighten fragments

      // Specular
      vec3 viewDir = normalize(viewPos - vFragPos);
      vec3 reflectDir = reflect(-lightDir, norm);
      float spec = pow(max(dot(viewDir, reflectDir), 0.0), uShininess);
      vec3 specular = spec * uSpecularColor * min(attenuation * 10, 1);


      vec3 albedo;
      if (uWorldAlignedTexture) {
        vec3 weights = blendWeights(normalize(norm));

        vec2 uvX = getTexCoord(vFragPos * uUvScale, 0);
        vec2 uvY = getTexCoord(vFragPos * uUvScale, 1);
        vec2 uvZ = getTexCoord(vFragPos * uUvScale, 2);

        vec3 texX = texture(sAlbedo, uvX).rgb;
        vec3 texY = texture(sAlbedo, uvY).rgb;
        vec3 texZ = texture(sAlbedo, uvZ).rgb;

        albedo = texX * weights.x + texY * weights.y + texZ * weights.z;
      }
      else {
        albedo = texture(sAlbedo, vUv * uUvScale).rgb;
      }

      LIGHTING += (diffuse * albedo + specular) * tintColor;
    }

    LIGHTING += (ambient * tintColor);
		// if inside a mesh
		// float inside = 1 - step(0, dot(viewDir, norm));
    // FragColor = vec4(result, inside * .3);
    LIGHTING = mix(LIGHTING, vec3(1.), wireframes);
    // FragColor = vec4(LIGHTING, vBlendFace);
    FragColor = vec4(LIGHTING, 1.);
    // FragColor = vec4(lightsNum / vec3(3), 1.);
		// FragColor = vec4(1.0);
}