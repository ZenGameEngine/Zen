#pragma once
#include <memory>
#include <glm/glm.hpp>

#include <zen/renderer/ZEN_VertexArray.h>
#include <zen/renderer/ZEN_Buffer.h>
#include <zen/renderer/ZEN_Shader.h>
#include <zen/renderer/ZEN_Renderer.h>

class QuadBuilder {
public:

  void init(std::shared_ptr<Zen::Shader> shader);

  void drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& colour);


  const std::shared_ptr<Zen::VertexArray>& vao() const { return m_vao; }
  const std::shared_ptr<Zen::Shader>&      shader() const { return m_shader; }

private:
  struct QuadVertex {
    glm::vec2 pos;   
    glm::vec4 color; 
  };

  std::shared_ptr<Zen::VertexArray> m_vao;
  std::shared_ptr<Zen::VertexBuffer> m_vbo;
  std::shared_ptr<Zen::IndexBuffer>  m_ibo;
  std::shared_ptr<Zen::Shader>       m_shader;

};
