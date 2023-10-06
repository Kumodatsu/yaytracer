#pragma once
#include "common.hpp"
#include "math/math.hpp"
#include "math/vector.hpp"
#include <random>

namespace yay {

  class RNG {
  public:
    using Seed = U32;

    RNG(Seed seed)
      : m_distribution(0.0f, 1.0f)
      , m_generator(seed)
    { }

    inline Real real() {
      return m_distribution(m_generator);
    }

    inline Real real(Real min, Real max) {
      return min + (max - min) * real();
    }

    inline Vector vector(Real min, Real max) {
      return Vector(real(min, max), real(min, max), real(min, max));
    }

    inline Vector hemisphere(const Vector& normal) {
      Vector result;
      do {
        result = vector(-1.0f, 1.0f);
      } while (result.length_squared() > 1.0f);
      result.normalize();
      return dot(result, normal) < 0.0f ? -result : result;
    }
  private:
    std::uniform_real_distribution<F32> m_distribution;
    std::mt19937 m_generator;
  };

}
