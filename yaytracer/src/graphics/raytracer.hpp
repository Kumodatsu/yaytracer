#pragma once
#include "random.hpp"
#include "graphics/camera.hpp"
#include "graphics/scene.hpp"
#include "rendering/pixel_buffer.hpp"

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <vector>

namespace yay {

  class Raytracer {
  public:
    Raytracer(const Camera& camera, const Scene& scene);
  private:
    RNG         m_rng;
    Camera      m_camera;
    Scene       m_scene;
    PixelBuffer m_buffer;

    std::vector<std::thread> m_threads;
    std::mutex               m_mutex;
    std::condition_variable  m_buffer_condition;

    void trace();
  };

}
