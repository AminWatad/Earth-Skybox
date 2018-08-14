#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>

using namespace std;

class Shader {
  public:
  
  unsigned int ID;

  Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

  void use();

  void setBool(const string &name, bool value) const;
  void setInt(const string &name, int value) const;
  void setFloat(const string &name, float value) const;
  void setMat4(const string &name, const glm::mat4 &mat) const;
};

#endif
