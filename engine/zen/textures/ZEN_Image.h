#pragma once

#include <zen/zen_pch.h>

namespace Zen {
  typedef struct Image {
    unsigned char *data = new unsigned char;
    uint32_t width{0};
    uint32_t height{0};
    const char *filePath;

    Image() {};
    Image(unsigned char *data, uint32_t width, uint32_t height, const char *filePath) {
      this->data     = data;
      this->width    = width;
      this->height   = height;
      this->filePath = filePath;
    };

    ~Image() {
      delete this->data;
      this->data = nullptr;
    };

  } Image;
}; // namespace Zen
