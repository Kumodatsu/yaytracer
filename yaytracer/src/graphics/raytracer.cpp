#include "raytracer.hpp"

namespace yay {

  Raytracer::Raytracer(const Camera& camera, const Scene& scene)
    : m_rng(17171717)
    , m_camera(camera)
    , m_scene(scene)
    , m_buffer(m_camera.width(), m_camera.height())
    , m_threads()
    , m_mutex()
    , m_buffer_condition()
  {

  }

  void Raytracer::trace() {
    static constexpr UCount work_size = 256;
    m_scene.sample()
  }

}
