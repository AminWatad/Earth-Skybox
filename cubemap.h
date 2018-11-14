#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class Cubemap {
  
  public:
  Cubemap(vector<std::string> faces){

    cubemapTexture = loadCubemap(faces);
    skyboxshader = new Shader("skybox.vs", "skybox.fs");
    glGenBuffers(1, &skyVBO);
    glBindBuffer(GL_ARRAY_BUFFER, skyVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices,
                GL_STATIC_DRAW);

    glGenVertexArrays(1, &skyVAO);
    glBindVertexArray(skyVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 
                          sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
  }

  void Draw() 
  {
    glDepthMask(GL_FALSE);
    skyboxshader->use();
    glm::mat4 view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f),
                              800.0f / 600.0f, 0.1f, 100.0f);
    skyboxshader->setMat4("view", view);
    skyboxshader->setMat4("projection", projection);
    glBindVertexArray(skyVAO);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDepthMask(GL_TRUE);
   
  }

  private:
  Shader *skyboxshader;
  unsigned int cubemapTexture;
  unsigned int skyVAO, skyVBO;
  
  unsigned int loadCubemap(vector<std::string> faces)
  {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); ++i)
    {
      unsigned char *data = stbi_load(faces[i].c_str(), &width, &height,
                                    &nrChannels, 0);
      if (data)
      {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                   0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,
                   data);
        stbi_image_free(data);
      }
      else {
        std::cout << "Cubemap texture failed to load at path: " << faces[i];
        std::cout << endl;
      }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
  }
};
