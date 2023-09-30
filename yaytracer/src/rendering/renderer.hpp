#pragma once
#include "rendering/pixel_buffer.hpp"
#include "rendering/texture.hpp"
#include "rendering/window.hpp"
#include <memory>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace yay {

  class Renderer {
  public:
    Renderer(Window& window);
    ~Renderer();
    Renderer(const Renderer&)               = delete;
    Renderer& operator = (const Renderer&)  = delete;
    Renderer(Renderer&& other)              = delete;
    Renderer& operator = (Renderer&& other) = delete;

    void begin_frame();
    void render(const PixelBuffer& pixels);
    void end_frame();
  private:
    Window& m_window;
    GLuint
      m_vbo_id,
      m_vao_id,
      m_shader_program_id;
    std::unique_ptr<Texture> m_texture;
  };

}
