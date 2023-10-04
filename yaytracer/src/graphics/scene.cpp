#include "scene.hpp"
#include <limits>

namespace yay {

  Color Scene::trace(const Ray& ray) const {
    const auto intersection = nearest_intersection(ray);
    if (intersection.has_value()) {
      // return intersection->color;
      const Vector& normal = intersection->normal;
      return 0.5f * Color(normal.x + 1.0f, normal.y + 1.0f, normal.z + 1.0f);
    } else {
      const auto a = 0.5f * ray.direction.y + 1.0f;
      return blend(a, colors::White, Color(0.5f, 0.7f, 1.0f));
    }
  }

  std::optional<Intersection> Scene::nearest_intersection(const Ray& ray) const
  {
    std::optional<Intersection> nearest_intersection = std::nullopt;
    F32 nearest_distance = std::numeric_limits<F32>().infinity();
    for (const auto& object : m_objects) {
      const auto intersection = object.intersect(ray);
      if (intersection.has_value()) {
        const F32 distance = (intersection->position - ray.origin)
          .length_squared();
        if (distance < nearest_distance) {
          nearest_distance     = distance;
          nearest_intersection = intersection;
        }
      }
    }
    return nearest_intersection;
  }

}
