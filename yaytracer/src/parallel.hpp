#pragma once
#include <thread>
#include <vector>
#include <atomic>
#include <functional>
#include <algorithm>
#include "common.hpp"
#include "logging.hpp"

namespace yay {

  template <typename Input, typename Output>
  class Parallel {
  public:
    using Function = std::function<Output(const Input&)>;

    Parallel(
      UCount   thread_count,
      UCount   work_size,
      Function function
    )
      : m_thread_count(thread_count)
      , m_work_size(work_size)
      , m_threads()
      , m_index(0)
      , m_input()
      , m_output()
      , m_function(function)
    { }

    ~Parallel() {
      wait();
    }

    Parallel(const Parallel&)              = delete;
    Parallel& operator = (const Parallel&) = delete;
    Parallel(Parallel&&)                   = delete;
    Parallel& operator = (Parallel&&)      = delete;

    std::vector<Output> wait() {
      for (auto& thread : m_threads) {
        if (thread.joinable()) {
          thread.join();
        }
      }
      m_index = 0;
      return m_output;
    }

    void start(const std::vector<Input>& input) {
      m_input = input;
      if (m_input.size() != m_output.size()) {
        m_output.resize(m_input.size());
      }
      for (UIndex i = 0; i < m_thread_count; ++i) {
        m_threads.emplace_back([this](){ this->run(); });
      }
    }
  private:
    UCount                   m_thread_count;
    UCount                   m_work_size;
    std::vector<std::thread> m_threads;
    std::atomic<UIndex>      m_index;

    std::vector<Input>  m_input;
    std::vector<Output> m_output;
    Function            m_function;

    void run() {
      UIndex index, end;
      do {
        index = m_index.fetch_add(m_work_size);
        end   = std::min(index + m_work_size, m_input.size());
        for (UIndex i = index; i < end; ++i) {
          m_output[i] = m_function(m_input[i]);
        }
      } while (end < m_input.size());
    }
  };

}
