#include "scene.hpp"
#include <limits>

namespace yay {

  Scene::Scene()
    : m_objects()
    , m_rng(7319337)
  { }

  Color Scene::sample(const Ray& ray, U16 depth) {
    static constexpr UCount max_depth = 8;
    if (depth > max_depth) {
      return colors::Black;
    }
    const auto intersection = nearest_intersection(ray);
    if (intersection.has_value()) {
      const Vector& normal    = intersection->normal;
      const Vector  direction = (normal + m_rng.unit_vector()).normalized();
      const Ray bounced_ray(intersection->position, direction);
      return 0.5f * sample(bounced_ray, depth + 1);
      //return blend(0.5f, intersection->color, trace(bounced_ray, depth + 1));
      //return 0.5f * Color(normal.x + 1.0f, normal.y + 1.0f, normal.z + 1.0f);
    } else {
      const auto a = 0.5f * ray.direction.y + 1.0f;
      return blend(a, colors::White, Color(0.5f, 0.7f, 1.0f));
    }
  }

  void Scene::trace(Color& color, const Ray& ray) {
    TraceProgress progress {
      .samples = 0,
    };
    trace(color, ray, progress);
  }

  void Scene::trace(Color& color, const Ray& ray, TraceProgress& progress) {
    const auto sample_color = sample(ray);
    const auto sample_count = static_cast<Real>(progress.samples);
    color = (sample_color + sample_count * color) / (sample_count + 1.0f);
    progress.samples++;
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
    static constexpr F32 epsilon = 0.001f;
    if (nearest_distance < epsilon) {
      return std::nullopt;
    }
    return nearest_intersection;
  }

}
