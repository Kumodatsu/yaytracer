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

    inline U32 width()  const { return m_width;  }
    inline U32 height() const { return m_height; }
    
    inline GLuint id() const { return m_id; }

    void buffer(const PixelBuffer& pixels);
    void bind();
  private:
    U32    m_width;
    U32    m_height;
    GLuint m_id;
  };

}
