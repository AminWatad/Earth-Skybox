#version 330 core
struct Material {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};

struct Light {
  vec3 position;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

uniform Light light;
uniform Material material;
in vec3 pos;
in vec2 TexCoord;
in vec3 Normal;

out vec4 FragColor;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

void main()
{
  // ambient
  vec3 ambient = light.ambient * material.ambient;

  // diffuse
  vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(lightPos - pos);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse;
  if (diff > 0.01) {
    diffuse = vec3(texture(texture_diffuse1, TexCoord).xyz) * diff;
  }
  else diffuse = vec3(texture(texture_specular1, TexCoord).xyz);

  // specular
  vec3 viewDir = normalize(viewPos - pos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  vec3 specular = light.specular * (spec * material.specular);
  
  vec3 result = ambient + specular + diffuse;
  FragColor = vec4(result, 1.0);
}
