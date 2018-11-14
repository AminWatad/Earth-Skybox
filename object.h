#include "shader.h"
#include "model.h"
#include "stack"
#include <math.h>

class Object
{
  private:
    Shader *shader;
    Model *mod;

  public:
    glm::vec3 position;
    glm::vec3 speed;
    glm::vec3 scale;
    glm::vec3 gravity;
    glm::vec3 lightPos;

    std::stack<glm::mat4> models;

    glm::mat4 view;
    glm::mat4 model;
    glm::mat4 projection;

    Object(string const &path, const char* shaderVs, const char* shaderFs) 
    {
      mod = new Model(path);
      shader = new Shader(shaderVs, shaderFs);
      glm::vec3 position = glm::vec3(0.0f, 0.0f, -3.0f);
      scale = glm::vec3(0.2f, 0.2f, 0.2f);
      gravity = glm::vec3(0.0f, -9.8f, 0.0f);
      lightPos = glm::vec3(-100.0f, -4.0f, 0.0f);
    }

    void Draw()
    {
      shader->use();
      view = glm::mat4(1.0f);
      view = camera.GetViewMatrix();
      float r = glm::radians((float)glfwGetTime() * 20);
      view = glm::translate(view, glm::vec3(position.x*cos(r), 0.0f, position.x*sin(r)));

      projection = glm::mat4(1.0f);
      projection = glm::perspective(glm::radians(45.0f),
                          800.0f / 600.0f, 0.1f, 100.0f);

      shader->setMat4("view", view);
      shader->setMat4("projection", projection);
      
      model = glm::mat4(1.0f);
      model = glm::translate(model, glm::vec3(0.0f, -1.75, 0.0f));
      //model = glm::scale(model, scale); 
      
      while (!models.empty()) {
        model = models.top() * model;
        models.pop();
      }
      shader->setMat4("model", model);
      shader->setVec3("lightPos", lightPos);
      shader->setVec3("viewPos", camera.Position);
      shader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
      shader->setVec3("material.ambient",  1.0f, 0.5f, 0.31f);
      shader->setVec3("material.diffuse",  1.0f, 0.5f, 0.31f);
      shader->setVec3("material.specular", 0.5f, 0.5f, 0.5f);
      shader->setFloat("material.shininess", 32.0f);
      shader->setVec3("light.ambient",  0.2f, 0.2f, 0.2f);
      shader->setVec3("light.diffuse",  0.5f, 0.5f, 0.5f); 
      shader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);
      mod->Draw(*shader);
    }

    void jump() {
      speed.y = 15.0f;
    }

    void update(float seconds) {
      if (position.y > 0.0f || speed.y > 0.0f) {
        speed.y -= seconds * (9.8f);
        position.y += speed.y * seconds;
      }
      else speed.y = 0.0f;
    }

    void rotate(float radians) {
      glm::mat4 rot = glm::mat4(1.0f);
      rot = glm::rotate(rot, radians, glm::vec3(0.0f, 1.0f, 0.0f));
      models.push(rot);
    }

};
