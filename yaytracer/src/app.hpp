#pragma once
#include "rendering/pixel_buffer.hpp"
#include "rendering/window.hpp"
#include "rendering/renderer.hpp"
#include "graphics/camera.hpp"
#include "graphics/scene.hpp"

namespace yay {

  class App {
  public:
    App();
  private:
    PixelBuffer m_pixel_buffer;
    Window      m_window;
    Renderer    m_renderer;
    Camera      m_camera;
    Scene       m_scene;

    void run();
    void handle_input();
    void render();
  };

}
