#pragma once
#include <functional>
#include <unordered_map>
#include <cstdint>
#include <type_traits>

namespace yay {

  template <typename Publisher, typename... Args>
  class Event {
    friend std::remove_cv_t<std::remove_reference_t<Publisher>>;
  public:
    using Callback     = std::function<void(Publisher, Args...)>;
    using Subscription = size_t;

    Event() : m_next_id(1), m_callbacks() {}

    Event(const Event&)              = delete;
    Event& operator = (const Event&) = delete;
    Event(Event&&)                   = delete;
    Event& operator = (Event&&)      = delete;
    
    Subscription subscribe(Callback callback) {
      m_callbacks.insert({m_next_id, callback});
      return m_next_id++;
    }
    
    void unsubscribe(Subscription subscription) {
      const auto it = m_callbacks.find(subscription);
      if (it != m_callbacks.end()) {
        m_callbacks.erase(it);
      }
    }
  private:
    Subscription m_next_id;
    std::unordered_map<Subscription, Callback> m_callbacks;

    void operator () (Publisher publisher, Args... args) const {
      fire(publisher, args...);
    }
    
    void fire(Publisher publisher, Args... args) const {
      for (const auto [subscription, callback] : m_callbacks) {
        callback(publisher, args...);
      }
    }
  };

  template <typename Publisher, typename... Args>
  class Subscriber {
  public:
    using Event = ::yay::Event<Publisher, Args...>;
    
    Subscriber(Event& event, Event::Callback callback)
      : m_event(event)
      , m_sub(m_event.subscribe(callback))
    {}
    
    ~Subscriber() {
      m_event.unsubscribe(m_sub);
    }

    Subscriber(const Subscriber&)              = delete;
    Subscriber& operator = (const Subscriber&) = delete;
    Subscriber(Subscriber&&)                   = delete;
    Subscriber& operator = (Subscriber&&)      = delete;
  private:
    Event& m_event;
    Event::Subscription m_sub;
  };

}
