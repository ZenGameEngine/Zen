#include "zen/zen_pch.h"
#include <zen/platform/OpenGL/ZEN_OpenGLRendererAPI.h>

namespace Zen {
  void OpenGLRendererAPI::setClearColour(const glm::vec4 &colour) {
    glClearColor(colour.r, colour.g, colour.b, colour.a);
  }

  void OpenGLRendererAPI::clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

  void OpenGLRendererAPI::setViewport(int width, int height) {
    ZEN_LOG_TRACE("resize opengl viewport");
    glViewport(0, 0, width, height);
  }

  void OpenGLRendererAPI::drawIndexed(const std::shared_ptr<VertexArray> &vertexArray) {
    glDrawElements(GL_TRIANGLES,
                   vertexArray->getIndexBuffer()->getCount(),
                   GL_UNSIGNED_INT,
                   nullptr);
  }

} // namespace Zen