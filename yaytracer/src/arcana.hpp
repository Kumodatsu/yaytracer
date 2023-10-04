#pragma once
#include <type_traits>

namespace yay {

  template <typename T>
  concept Enum = std::is_enum_v<T>;

  inline constexpr auto underlying_cast(Enum auto variant) {
    return static_cast<std::underlying_type_t<decltype(variant)>>(variant);
  }

}
