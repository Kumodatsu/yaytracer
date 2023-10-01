#pragma once
#include "common.hpp"
#include <cmath>

namespace yay {

  using Natural = U32;
  using Integer = I32;
  using Real    = F32;

  inline constexpr Real pi = 3.14159265f;

  inline Real sin(Real x)  { return ::sin(x);  }
  inline Real cos(Real x)  { return ::cos(x);  }
  inline Real tan(Real x)  { return ::tan(x);  }
  inline Real asin(Real x) { return ::asin(x); }
  inline Real acos(Real x) { return ::acos(x); }
  inline Real atan(Real x) { return ::atan(x); }
  
  inline Real atan2(Real y, Real x) {
    return ::atan2(y, x);
  }

  inline Real sqrt(Real x) { return ::sqrt(x); }

}
