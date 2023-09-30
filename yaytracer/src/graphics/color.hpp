#pragma once
#include "common.hpp"

namespace yay {

  struct Color {
    F32 r, g, b, a;
    Color() = default;
    constexpr Color(F32 r, F32 g, F32 b, F32 a = 1.0f)
      : r(r), g(g), b(b), a(a) {}
  };

  namespace colors {
    inline constexpr Color
      Black   {0.0f, 0.0f, 0.0f, 1.0f},
      White   {1.0f, 1.0f, 1.0f, 1.0f},
      Red     {1.0f, 0.0f, 0.0f, 1.0f},
      Green   {0.0f, 1.0f, 0.0f, 1.0f},
      Blue    {0.0f, 0.0f, 1.0f, 1.0f},
      Yellow  {1.0f, 1.0f, 0.0f, 1.0f},
      Cyan    {0.0f, 1.0f, 1.0f, 1.0f},
      Magenta {1.0f, 0.0f, 1.0f, 1.0f};
  }

}
