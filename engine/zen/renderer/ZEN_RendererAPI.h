#pragma once

#include <zen/zen_pch.h>

#include <zen/renderer/ZEN_VertexArray.h>

namespace Zen {
  class RendererAPI {
  public:
    enum class API { None = 0, OpenGL = 1 };

    virtual void setClearColour(const glm::vec4 &colour) = 0;

    virtual void clear() = 0;

    virtual void setViewport(int width, int height) = 0;

    virtual void drawIndexed(const std::shared_ptr<VertexArray> &vertexArray) = 0;

    static API getAPI() { return s_API; }

  private:
    static API s_API;
  };
}; // namespace Zen