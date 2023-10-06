#pragma once
#include "common.hpp"
#include "graphics/color.hpp"
#include <vector>

namespace yay {

  class PixelBuffer {
  public:
    PixelBuffer(UCount width, UCount height);

    void clear(const Color& color = colors::Black);
    void resize(UCount width, UCount height);

    inline UCount       width()  const { return m_width;       }
    inline UCount       height() const { return m_height;      }
    inline const Color* data()   const { return m_data.data(); }
    
    inline Color* data() { return m_data.data(); }

    inline Color& at(UIndex u, UIndex v) {
      return m_data[u + m_width * v];
    }

    inline const Color& at(UIndex u, UIndex v) const {
      return m_data[u + m_width * v];
    }
  private:
    UCount             m_width;
    UCount             m_height;
    std::vector<Color> m_data;
  };

}
