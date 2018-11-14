glm::vec3 gravity = glm::vec3(0.0f, -9.8f, 0.0f);

glm::vec3 aToS (glm::vec3 acceleration, glm::vec3 speed, float time)
{
  return speed + time * acceleration;
}


