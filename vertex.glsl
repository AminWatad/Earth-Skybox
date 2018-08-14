#version 330 core
layout (location = 0) in vec3 aPos;

void main() {
  gl_position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
