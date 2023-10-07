#pragma once
#include "graphics/sphere.hpp"
#include "graphics/ray.hpp"
#include "graphics/intersection.hpp"
#include "graphics/color.hpp"
#include "rendering/pixel_buffer.hpp"
#include "random.hpp"
#include <vector>
#include <optional>

namespace yay {
  
  class Scene {
  public:
    Scene();

    inline Scene& add(const Sphere& object) {
      m_objects.emplace_back(object);
      return *this;
    }

    Color trace(const Ray& ray, U16 depth = 1);
    std::optional<Intersection> nearest_intersection(const Ray& ray) const;
  private:
    std::vector<Sphere> m_objects;
    RNG m_rng;
  };

}
