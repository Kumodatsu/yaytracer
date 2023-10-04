#pragma once
#include "rendering/pixel_buffer.hpp"
#include "rendering/window.hpp"
#include "rendering/renderer.hpp"
#include "graphics/camera.hpp"
#include "graphics/sphere.hpp"

namespace yay {

  class App {
  public:
    App();
  private:
    PixelBuffer m_pixel_buffer;
    Window      m_window;
    Renderer    m_renderer;
    Camera      m_camera;

    Sphere m_sphere;

    void run();
    void handle_input();
    void render();
  };

}
