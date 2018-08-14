#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>
#include "shader.h"
#include "camera.h"
#include "controls.h"
#include "mesh.h"
#include "model.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

string file = "nanosuit/nanosuit.obj";

int main() {
  float screenWidth = 800;
  float screenHeight = 600;

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
  if (window == NULL)
  {
    cout << "Failed to create GLFW window" << endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    cout << "Failed to initialize GLAD" << endl;
    return -1;
  }

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetCursorPosCallback(window, mouse_callback);

  glEnable(GL_DEPTH_TEST);

  Shader ours("1.model_loading.vs", "1.model_loading.fs");
  
  Model nanosuit("nanosuit/nanosuit.obj");
  // render loop
  while(!glfwWindowShouldClose(window))
  {

    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
        
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // check for input 
    processInput(window);
    
    //rendering commands
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    ours.use();
    glm::mat4 view = camera.GetViewMatrix();
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), 
                screenWidth / screenHeight, 0.1f, 100.0f);
    
    ours.setMat4("view", view);
    ours.setMat4("projection", projection);

    glm::mat4 model;
    model = glm::translate(model, glm::vec3(0.0f, -1.75, 0.0f));
    model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
    ours.setMat4("model", model);

    nanosuit.Draw(ours);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
