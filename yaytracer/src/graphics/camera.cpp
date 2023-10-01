#include "camera.hpp"
#include "logging.hpp"

namespace yay {

  Camera::Camera(
    Natural       width,
    Natural       height,
    Real          focal_length,
    const Vector& position
  )
    : m_width(width)
    , m_height(height)
    , m_focal_length(focal_length)
    , m_viewport_width(aspect())
    , m_viewport_height(1.0f)
    , m_position(position)
    , m_up(0.0f, 1.0f, 0.0f)
    , m_forward(0.0f, 0.0f, -1.0f)
    , m_right(1.0f, 0.0f, 0.0f)
    , m_viewport_u(m_viewport_width, 0.0f, 0.0f)
    , m_viewport_v(0.0f, -m_viewport_height, 0.0f)
    , m_pixel_u(m_viewport_u / static_cast<Real>(m_width))
    , m_pixel_v(m_viewport_v / static_cast<Real>(m_height))
    , m_pixel_position(
      m_position
      - Vector(0.0f, 0.0f, m_focal_length)
      - 0.5f * m_viewport_u
      - 0.5f * m_viewport_v
      + 0.5f * (m_pixel_u + m_pixel_v)
    )
  { }

  std::vector<Ray> Camera::rays() const {
    std::vector<Ray> rays;
    for (Natural v = 0; v < m_height; ++v) {
      for (Natural u = 0; u < m_width; ++u) {
        const auto pixel_position
          = m_pixel_position
          + static_cast<Real>(u) * m_pixel_u
          + static_cast<Real>(v) * m_pixel_v;
        const auto direction = (pixel_position - m_position).normalized();
        rays.emplace_back(m_position, direction);
      }
    }
    return rays;
  }

}
