#pragma once
#include "common.hpp"
#include "math/vector.hpp"
#include "graphics/ray.hpp"
#include <vector>

namespace yay {

  class Camera {
  public:
    Camera(
      Natural       width,
      Natural       height,
      Real          focal_length,
      const Vector& position
    );

    inline constexpr Real aspect() const {
      return static_cast<Real>(m_width) / static_cast<Real>(m_height);
    }

    std::vector<Ray> rays() const;
  private:
    Natural
      m_width,
      m_height;
    Real
      m_focal_length,
      m_viewport_width,
      m_viewport_height;
    Vector
      m_position,
      m_up,
      m_forward,
      m_right,
      m_viewport_u,
      m_viewport_v,
      m_pixel_u,
      m_pixel_v,
      m_pixel_position;
  };

}
