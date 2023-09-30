#include "rendering/pixel_buffer.hpp"
#include <algorithm>

namespace yay {

  PixelBuffer::PixelBuffer(UCount width, UCount height)
    : m_width(width)
    , m_height(height)
    , m_data(width * height, colors::Black)
  { }

  void PixelBuffer::clear(const Color& color) {
    std::fill(m_data.begin(), m_data.end(), color);
  }

  void PixelBuffer::resize(UCount width, UCount height) {
    m_data.resize(width * height, colors::Black);
  }

}
