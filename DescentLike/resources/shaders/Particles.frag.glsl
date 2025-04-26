#version 450 core

layout (location = 0) out vec4 FragColor;

in V_OUT {
    vec3 color;
} vIn;

void main(void)
{
    FragColor = vec4(vec3(1.), vIn.color.r);
}
