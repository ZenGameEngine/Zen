#pragma once

#include <zen/renderer/abstractions/ZEN_RendererAPI.h>

namespace Zen {
  struct DrawStats {
    static inline uint64_t drawCalls = 0;

    static void reset() { drawCalls = 0; }
    static void addDraw(uint32_t indexCount) { ++drawCalls; }
  };

  class RenderCommand {
  public:
    static void setClearColour(const glm::vec4 &colour) { s_rendererAPI->setClearColour(colour); }
    static void clear() { s_rendererAPI->clear(); }
    static void drawIndexed(const std::shared_ptr<VertexArray> &vertexArray) {
      uint32_t indexCount = vertexArray->getIndexBuffer()->getCount();
      DrawStats::addDraw(indexCount);
      s_rendererAPI->drawIndexed(vertexArray);
    }

    static void setViewport(const int width, const int height) {
      s_rendererAPI->setViewport(width, height);
    }

  private:
    static RendererAPI *s_rendererAPI;
  };

} // namespace Zen
