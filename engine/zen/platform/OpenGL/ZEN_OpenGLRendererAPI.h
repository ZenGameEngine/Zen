#pragma once

#include <zen/zen_pch.h>

#include <zen/renderer/ZEN_RendererAPI.h>

namespace Zen {
  class OpenGLRendererAPI : public RendererAPI {
  public:
    void setClearColour(const glm::vec4 &colour) override;
    void clear() override;
    
    void drawIndexed(const std::shared_ptr<VertexArray> &vertexArray) override;
    void setViewport(int width, int height) override;
  };
} // namespace Zen