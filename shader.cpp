#include "shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
  string vertexCode;
  string fragmentCode;
  ifstream vShaderFile;
  ifstream fShaderFile;
  
  vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
  try
  {
    vShaderFile.open(vertexPath);
    fShaderFile.open(fragmentPath);
    stringstream vShaderStream, fShaderStream;

    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();

    vShaderFile.close();
    fShaderFile.close();

    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
  }
  catch(ifstream::failure e)
  {
    cout << "ERROR::SHADER::FILE_FAILED_TO_LOAD" << endl;
  }
  const char* vShaderCode = vertexCode.c_str();
  const char* fShaderCode = fragmentCode.c_str();
  
  unsigned int vertex, fragment;
  int success;
  char infoLog[512];

  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);

  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if(!success)
  {
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    cout << "ERROR:SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
  };

  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, NULL);
  glCompileShader(fragment);

  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if(!success)
  {
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    cout << "ERROR:SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
  };
  
  ID = glCreateProgram();
  glAttachShader(ID, vertex);
  glAttachShader(ID, fragment);
  glLinkProgram(ID);

  glGetProgramiv(ID, GL_LINK_STATUS, &success);
  if(!success)
  {
    glGetProgramInfoLog(ID, 512, NULL, infoLog);
    cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
  }

  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

void Shader::use()
{
  glUseProgram(ID);
}

void Shader::setBool(const string &name, bool value) const
{
  glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const string &name, int value) const
{
  glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const string &name, float value) const
{
  glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
void shader::setmat4(const std::string &name, const glm::mat4 &mat) const
{
  gluniformmatrix4fv(glgetuniformlocation(id, name.c_str()), 1, gl_false, &mat[0][0]);
}
void shader::setVec3(const std::string &name, const glm::vec3 &vec) const
{
  glUniform3f(glGetUniformLocation(ID, name.c_str()), 1, &vec[0]);
}


