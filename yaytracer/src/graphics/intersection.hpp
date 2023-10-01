#pragma once
#include "math/math.hpp"
#include "math/vector.hpp"
#include "graphics/color.hpp"

namespace yay {

  struct Intersection {
    Vector position;
    Vector normal;
    Color  color;

    Intersection() = default;
    
    constexpr Intersection(
      const Vector& position,
      const Vector& normal,
      const Color&  color
    )
      : position(position)
      , normal(normal)
      , color(color)
    {}
  };

}

