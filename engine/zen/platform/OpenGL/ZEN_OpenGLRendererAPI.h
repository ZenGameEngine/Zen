#pragma once

#include <zen/zen_pch.h>

#include <zen/renderer/ZEN_RendererAPI.h>

namespace Zen {
  class OpenGLRendererAPI : public RendererAPI {
  public:
    virtual void setClearColour(const glm::vec4 &colour) override;
    virtual void clear() override;

    virtual void drawIndexed(const std::shared_ptr<VertexArray> &vertexArray) override;
  };
} // namespace Zen