#pragma once
#include "math/math.hpp"
#include "math/vector.hpp"
#include "graphics/intersection.hpp"
#include "graphics/ray.hpp"
#include <optional>

namespace yay {

  struct Sphere {
    Vector position;
    Real   radius;

    Sphere() = default;
    constexpr Sphere(const Vector& position, Real radius)
      : position(position), radius(radius)
    {}

    inline constexpr std::optional<Intersection>
      intersect(const Ray& ray) const
    {
      const Vector
        sphere_to_ray = ray.origin - position;
      const Real
        a = dot(ray.direction, ray.direction),
        b = 2.0f * dot(sphere_to_ray, ray.direction),
        c = dot(sphere_to_ray, sphere_to_ray) - radius * radius,
        d = b * b - 4.0f * a * c;
      if (d < 0.0f) {
        return std::nullopt;
      }
      return Intersection(
        Vector(0.0f, 0.0f, 0.0f),
        Vector(0.0f, 1.0f, 0.0f),
        colors::Red
      );
    }
  };

}

