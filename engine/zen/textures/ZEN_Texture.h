#pragma once

#include <zen/textures/ZEN_Image.h>
#include <zen/zen_pch.h>

namespace Zen {
  typedef struct Texture {
    uint32_t id;
    uint32_t width{0};
    uint32_t height{0};
    const char *textureName;

    std::weak_ptr<Zen::Image> image;

    Texture(const char *textureName, std::weak_ptr<Zen::Image> image) {
      this->textureName = textureName;
      this->image       = image;
      this->width       = image.lock()->width;
      this->height      = image.lock()->height;

      glGenTextures(1, &this->id);
      glBindTexture(GL_TEXTURE_2D, this->id);
      glTexImage2D(GL_TEXTURE_2D,
                   0,
                   GL_RGBA,
                   this->width,
                   this->height,
                   0,
                   GL_RGBA,
                   GL_UNSIGNED_BYTE,
                   image.lock()->data);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, 1.0f);

      glBindTexture(GL_TEXTURE_2D, 0);
    };

  } Texture;

  using TexturePtr = std::shared_ptr<Zen::Texture>;
}; // namespace Zen
