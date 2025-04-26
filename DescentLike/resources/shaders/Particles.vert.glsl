#version 450 core

layout (location = 0) in vec3 aPos;

layout (location = 2) in vec3 aInstancePos;

out V_OUT {
    vec3 color;
} vOut;

uniform mat4 mvp;
uniform vec3 CamPos;
uniform float InstanceScale;

float invlerp (float from, float to, float value){
  return (value - from) / (to - from);
}
float remap (float origFrom, float origTo, float targetFrom, float targetTo, float value){
  float rel = invlerp(origFrom, origTo, value);
  return mix(targetFrom, targetTo, rel);
}

void main(void)
{
    gl_Position = mvp * vec4(aPos * InstanceScale + aInstancePos, 1.);

    vec3 toPoint = gl_Position.xyz - CamPos;
    float distSq = dot(toPoint, toPoint);
    float far = 80.;
    float luminance = clamp(
      remap(far*far, 0., 0.1, 1., distSq),
      .1, .8
    );

    vOut.color = vec3(luminance);
}
