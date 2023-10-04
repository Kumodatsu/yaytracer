#include "app.hpp"
#include "common.hpp"
#include "graphics/sphere.hpp"

static constexpr yay::U32
  width  = 960,
  height = 540;

namespace yay {

  App::App()
    : m_pixel_buffer(width, height)
    , m_window("Yaytracer", width, height)
    , m_renderer(m_window)
    , m_camera(width, height, 0.5f, Vector(0.0f, 0.0f, 0.0f))
    , m_scene()
  {
    m_scene
      .add(Sphere(Vector(-1.0f, 0.0f, -1.0f), 0.1f))
      .add(Sphere(Vector(1.0f, 0.0f, -1.0f), 1.0f));
    run();
  }

  void App::run() {
    while (!m_window.is_close_requested()) {
      handle_input();
      m_renderer.begin_frame();
      render();
      m_renderer.render(m_pixel_buffer);
      m_renderer.end_frame();
      m_window.poll_events();
    }
  }

  void App::handle_input() {
    static constexpr F32 speed = 0.05f;
    Vector movement = Vector(0.0f, 0.0f, 0.0f);
    if (m_window.is_key_down(Key::A)) {
      movement += Vector(-1.0f, 0.0f, 0.0f);
    }
    if (m_window.is_key_down(Key::D)) {
      movement += Vector(1.0f, 0.0f, 0.0f);
    }
    if (m_window.is_key_down(Key::W)) {
      movement += Vector(0.0f, 0.0f, -1.0f);
    }
    if (m_window.is_key_down(Key::S)) {
      movement += Vector(0.0f, 0.0f, 1.0f);
    }
    if (m_window.is_key_down(Key::Space)) {
      movement += Vector(0.0f, 1.0f, 0.0f);
    }
    if (m_window.is_key_down(Key::LeftControl)) {
      movement += Vector(0.0f, -1.0f, 0.0f);
    }
    if (movement.length_squared() != 0.0f) {
      m_camera.move(speed * movement.normalized());
    }
  }

  void App::render() {
    const auto rays = m_camera.rays();
    for (UIndex v = 0; v < height; ++v) {
      for (UIndex u = 0; u < width; ++u) {
        const Ray&  ray   = rays[u + width * v];
        const Color color = m_scene.trace(ray);
        m_pixel_buffer.at(u, v) = color;
      }
    }
  }

}
