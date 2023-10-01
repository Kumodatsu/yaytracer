#pragma once
#include "math/vector.hpp"

namespace yay {

  // Hi, Ray!
  struct Ray {
    Vector origin;
    Vector direction;

    Ray() = default;

    constexpr Ray(const Vector& origin, const Vector& direction)
      : origin(origin)
      , direction(direction)
    {}

    inline constexpr Vector at(Real distance) const {
      return origin + distance * direction;
    }
  };

}
