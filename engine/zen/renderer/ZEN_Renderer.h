#pragma once

#include <zen/camera/ZEN_Camera.h>
#include <zen/renderer/ZEN_RenderCommand.h>
#include <zen/renderer/ZEN_Shader.h>
#include <zen/zen_pch.h>

namespace Zen {
  class Renderer {
  public:
    static void beginScene(Camera &camera);
    static void endScene();

    static void submit(const std::shared_ptr<Shader> &shader,
                       const std::shared_ptr<VertexArray> &vertexArray);

    static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }

  private:
    struct SceneData {
      glm::mat4 ViewProjectionMatrix;
    };

    static SceneData *m_sceneData;
  };
} // namespace Zen