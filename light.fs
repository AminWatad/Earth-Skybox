#version 330 core
in vec3 pos;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
void main()
{
   FragColor = vec4(1.0f);
}
