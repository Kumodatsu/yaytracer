#pragma once
#include "math/math.hpp"
#include <ostream>

namespace yay {

  struct Vector {
    Real x, y, z;
    
    Vector() = default;
    constexpr Vector(Real x, Real y, Real z) : x(x), y(y), z(z) {}

    [[nodiscard]]
    inline constexpr Real length_squared() const {
      return x * x + y * y + z * z;
    }

    [[nodiscard]]
    inline Real length() const {
      return sqrt(length_squared());
    }

    [[nodiscard("`normalized` doesn't modify the vector, it returns a new one")]]
    inline Vector normalized() const {
      const Real inverse_length = 1.0f / length();
      return Vector(inverse_length * x, inverse_length * y, inverse_length * z);
    }

    inline void normalize() {
      const Real inverse_length = 1.0f / length();
      x *= inverse_length;
      y *= inverse_length;
      z *= inverse_length;
    }
  };

  inline constexpr Vector operator + (const Vector& a, const Vector& b) {
    return Vector(a.x + b.x, a.y + b.y, a.z + b.z);
  }

  inline constexpr Vector operator - (const Vector& a, const Vector& b) {
    return Vector(a.x - b.x, a.y - b.y, a.z - b.z);
  }

  inline constexpr Vector operator * (const Vector& a, const Vector& b) {
    return Vector(a.x * b.x, a.y * b.y, a.z * b.z);
  }

  inline constexpr Vector operator / (const Vector& a, const Vector& b) {
    return Vector(a.x / b.x, a.y / b.y, a.z / b.z);
  }

  inline constexpr Vector operator - (const Vector& v) {
    return Vector(-v.x, -v.y, -v.z);
  }

  inline constexpr Vector operator * (Real s, const Vector& v) {
    return Vector(s * v.x, s * v.y, s * v.z);
  }

  inline constexpr Vector operator * (const Vector& v, Real s) {
    return Vector(s * v.x, s * v.y, s * v.z);
  }

  inline constexpr Vector operator / (const Vector& v, Real s) {
    const Real inverse = 1.0f / s;
    return inverse * v;
  }

  inline constexpr Real dot(const Vector& a, const Vector& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
  }

  inline constexpr Vector cross(const Vector& a, const Vector& b) {
    return Vector(
      a.y * b.z - a.z * b.y,
      a.z * b.x - a.x * b.z,
      a.x * b.y - a.y * b.x
    );
  }

  inline std::ostream& operator << (std::ostream& stream, const Vector& v) {
    return stream << "(" << v.x << ", " << v.y << ", " << v.z << ")";
  }

}
