#version 330 core
layout(location=0) in vec2 a_Position;
layout(location=1) in vec4 a_Color;

uniform mat4 u_viewProjection;
out vec4 v_Color;

void main() {
  gl_Position =  u_viewProjection * vec4(a_Position, 0.0, 1.0);
  v_Color = a_Color;
}
