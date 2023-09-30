#pragma once
#include "common.hpp"
#include "rendering/pixel_buffer.hpp"
#include <glad/glad.h>

namespace yay {

  class Texture {
  public:
    Texture();
    Texture(const PixelBuffer& pixels);
    ~Texture();
    Texture(const Texture& other)              = delete;
    Texture& operator = (const Texture& other) = delete;
    Texture(Texture&& other);
    Texture& operator = (Texture&& other);

    inline USize width()  const { return m_width;  }
    inline USize height() const { return m_height; }
    
    inline GLuint id() const { return m_id; }

    void buffer(const PixelBuffer& pixels);
    void bind();
  private:
    USize  m_width;
    USize  m_height;
    GLuint m_id;
  };

}
