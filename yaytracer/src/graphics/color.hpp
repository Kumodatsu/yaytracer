#pragma once
#include "common.hpp"
#include "math/math.hpp"

namespace yay {

  struct Color {
    Real r, g, b;
    Color() = default;
    constexpr Color(Real r, Real g, Real b) : r(r), g(g), b(b) {}
  };

  inline constexpr Color operator * (Real s, const Color& color) {
    return Color(s * color.r, s * color.g, s * color.b);
  }

  inline constexpr Color operator * (const Color& color, Real s) {
    return Color(s * color.r, s * color.g, s * color.b);
  }

  inline constexpr Color operator / (const Color& color, Real s) {
    const Real inverse = 1.0f / s;
    return inverse * color;
  }

  inline constexpr Color operator + (const Color& a, const Color& b) {
    return Color(a.r + b.r, a.g + b.g, a.b + b.b);
  }

  inline constexpr Color& operator += (Color& a, const Color& b) {
    a = a + b;
    return a;
  }
  
  inline constexpr Color blend(
    Real blend_factor, const Color& a, const Color& b
  ) {
    return (1.0f - blend_factor) * a + blend_factor * b;
  }

  namespace colors {
    inline constexpr Color
      Black   {0.0f, 0.0f, 0.0f},
      White   {1.0f, 1.0f, 1.0f},
      Red     {1.0f, 0.0f, 0.0f},
      Green   {0.0f, 1.0f, 0.0f},
      Blue    {0.0f, 0.0f, 1.0f},
      Yellow  {1.0f, 1.0f, 0.0f},
      Cyan    {0.0f, 1.0f, 1.0f},
      Magenta {1.0f, 0.0f, 1.0f};
  }

}
