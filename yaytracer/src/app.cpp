#include "app.hpp"
#include "common.hpp"
#include "graphics/sphere.hpp"
#include "graphics/color.hpp"
#include "logging.hpp"
#include <chrono>

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
    , m_parallel(8, 256, [this](const Ray& ray) {
        Color color = colors::Black;
        this->m_scene.trace(color, ray);
        return color;
      })
    , m_rays(m_camera.rays())
  {
    Logger::get_static_logger().set_log_level(LogLevel::Debug);
    m_scene
      .add(Sphere(Vector(0.0f, 0.0f, -1.0f), 0.5f))
      .add(Sphere(Vector(0.0f, -100.5f, -1.0f), 100.0f));
    run();
  }

  void App::run() {
    using clock = std::chrono::steady_clock;
    auto   time          = clock::now();
    auto   previous_time = time;
    auto   frame_timer   = time;
    UCount frames        = 0;     
    while (!m_window.is_close_requested()) {
      previous_time = time;
      time          = clock::now(); 
      const auto delta = time - previous_time;
      if (time - frame_timer > std::chrono::seconds(1)) {
        YAY_LOG(Info) << "Framerate: " << frames << " Hz";
        frame_timer = time;
        frames      = 0;
      }
      handle_input();
      m_renderer.begin_frame();
      render();
      m_renderer.render(m_pixel_buffer);
      m_renderer.end_frame();
      m_window.poll_events();
      frames++;
    }
  }

  void App::handle_input() {
    static constexpr F32 speed = 0.05f;
    Vector movement = Vector::zero()
      + m_window.is_key_down(Key::A)           * Vector::left()
      + m_window.is_key_down(Key::D)           * Vector::right()
      + m_window.is_key_down(Key::W)           * Vector::forward()
      + m_window.is_key_down(Key::S)           * Vector::backward()
      + m_window.is_key_down(Key::Space)       * Vector::up()
      + m_window.is_key_down(Key::LeftControl) * Vector::down();
    if (movement.length_squared() != 0.0f) {
      m_camera.move(speed * movement.normalized());
      m_rays = m_camera.rays();
    }
  }

  void App::render() {
    m_parallel.start(m_rays);
    const auto colors = m_parallel.wait();
    memcpy(m_pixel_buffer.data(), colors.data(), sizeof(Color) * colors.size());
  }

}
