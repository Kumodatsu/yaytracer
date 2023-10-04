#pragma once
#include "common.hpp"
#include "input/key.hpp"
#include "event/event.hpp"
#include <string>
#include <GLFW/glfw3.h>

namespace yay {

  class Window {
  public:
    Window(const std::string& title, U32 width, U32 height);
    ~Window();

    Window(const Window&)              = delete;
    Window& operator = (const Window&) = delete;
    Window(Window&&)                   = delete;
    Window& operator = (Window&&)      = delete;

    inline U32 width()  const { return m_width;  }
    inline U32 height() const { return m_height; }

    inline GLFWwindow* handle() { return m_handle; }
    inline const GLFWwindow* handle() const { return m_handle; }

    bool is_close_requested() const;
    void poll_events() const;
    bool is_key_down(Key key) const;

    Event<const Window&, Key> on_key_pressed;
    Event<const Window&, Key> on_key_released;
  private:
    std::string m_title;
    U32 m_width, m_height;
    GLFWwindow* m_handle;
  };

}
