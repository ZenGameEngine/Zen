#pragma once

#include <zen/zen_pch.h>

namespace Zen {
  class Shader {
  public:
    Shader(const char *vertexPath, const char *fragmentPath);
    ~Shader();

    void bind() const;
    void unBind() const;
    void uploadUniformMat4(const std::string &name, const glm::mat4 &matrix);

  private:
    uint32_t m_rendererID;
  };
} // namespace Zen