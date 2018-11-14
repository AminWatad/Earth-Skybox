#version 330 core
in vec3 pos;
in vec2 TexCoord;
in vec3 Normal;

out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;

void main()
{
  vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(lightPos - pos);

  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * vec3(1.0f);

  float ambientStrength = 0.1;
  vec3 ambient = ambientStrength * vec3(1.0f);

  float specStrength = 0.5;
  vec3 viewDir = normalize(viewPos - pos);
  vec3 reflectDir = reflect(-lightDir, norm);

  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
  vec3 specular = specStrength * spec * vec3(1.0f);

  vec3 result = vec3(texture(texture_diffuse1, TexCoord).xyz) * (ambient + diffuse + specular);
  FragColor = vec4(result, 1.0);
}
