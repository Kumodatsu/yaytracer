#pragma once
#include "math/math.hpp"
#include "math/vector.hpp"
#include "graphics/intersection.hpp"
#include "graphics/ray.hpp"
#include <algorithm>
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
        a      = ray.direction.length_squared(),
        half_b = dot(sphere_to_ray, ray.direction),
        c      = sphere_to_ray.length_squared() - radius * radius,
        d      = half_b * half_b - a * c;
      if (d < 0.0f) {
        return std::nullopt;
      }
      const Real
        sqrt_d    = sqrt(d),
        inverse_a = 1.0f / a,
        t0        = inverse_a * (-half_b - sqrt_d),
        t1        = inverse_a * (-half_b + sqrt_d),
        t         = t0 < 0.0f ? t1 : t0;
      if (t < 0.0f) {
        return std::nullopt;
      }
      const Vector
        intersection_position = ray.at(t),
        intersection_normal   = (intersection_position - position) / radius;
      return Intersection(
        intersection_position,
        intersection_normal,
        colors::Red
      );
    }
  };

}

