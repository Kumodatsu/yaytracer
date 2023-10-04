#pragma once
#include "graphics/sphere.hpp"
#include "graphics/ray.hpp"
#include "graphics/intersection.hpp"
#include "graphics/color.hpp"
#include "rendering/pixel_buffer.hpp"
#include <vector>
#include <optional>

namespace yay {
  
  class Scene {
  public:
    Scene() = default;

    inline Scene& add(const Sphere& object) {
      m_objects.emplace_back(object);
      return *this;
    }

    Color trace(const Ray& ray) const;
    std::optional<Intersection> nearest_intersection(const Ray& ray) const;
  private:
    std::vector<Sphere> m_objects;
  };

}
