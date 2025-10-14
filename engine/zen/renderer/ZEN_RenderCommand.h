#pragma once

#include <zen/renderer/ZEN_RendererAPI.h>

namespace Zen {
  class RenderCommand {
  public:
    static void setClearColour(const glm::vec4 &colour) { s_rendererAPI->setClearColour(colour); }

    static void clear() { s_rendererAPI->clear(); }

    static void drawIndexed(const std::shared_ptr<VertexArray> &vertexArray) {
      s_rendererAPI->drawIndexed(vertexArray);
    }

    static void setViewport(int width, int height) { s_rendererAPI->setViewport(width, height); }

  private:
    static RendererAPI *s_rendererAPI;
  };

} // namespace Zen