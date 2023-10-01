#include "rendering/texture.hpp"

namespace yay {

  Texture::Texture()
    : m_width(0)
    , m_height(0)
    , m_id()
  {
    glCreateTextures(GL_TEXTURE_2D, 1, &m_id);
    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  }

  Texture::Texture(const PixelBuffer& pixels)
    : m_width(static_cast<U32>(pixels.width()))
    , m_height(static_cast<U32>(pixels.height()))
    , m_id()
  {
    glCreateTextures(GL_TEXTURE_2D, 1, &m_id);
    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    buffer(pixels);
  }

  Texture::~Texture() {
    if (m_id == 0) {
      return;
    }
    glDeleteTextures(1, &m_id);
  }

  Texture::Texture(Texture&& other)
    : m_width(other.m_width)
    , m_height(other.m_height)
    , m_id(other.m_id)
  {
    other.m_id = 0;
  }

  Texture& Texture::operator = (Texture&& other) {
    if (this == &other) {
      return *this;
    }
    if (m_id != 0) {
      glDeleteTextures(1, &m_id);
    }
    m_width    = other.m_width;
    m_height   = other.m_height;
    m_id       = other.m_id;
    other.m_id = 0;
    return *this;
  }

  void Texture::buffer(const PixelBuffer& pixels) {
    bind();
    m_width  = static_cast<U32>(pixels.width());
    m_height = static_cast<U32>(pixels.height());
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB,
      GL_FLOAT, pixels.data());
  }

  void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, m_id);
    glActiveTexture(GL_TEXTURE0);
    glBindTextureUnit(0, m_id);
  }

}
