#pragma once

#include <zen/zen_pch.h>

#include <zen/events/ZEN_Event.h>

namespace Zen {
  class EventBuffer {
  public:
    EventBuffer(std::size_t capacity)
        : m_buffer(std::unique_ptr<ZenEvent[]>(new ZenEvent[capacity])), m_maxCapacity(capacity) {}

    ~EventBuffer() = default;

    void enqueue(ZenEvent event);
    ZenEvent dequeue();

    void flush();
    bool isEmpty() const;
    bool isFull() const;

    size_t capacity() const;
    size_t size() const;

  private:
    std::unique_ptr<ZenEvent[]> m_buffer;
    size_t m_head = 0;
    size_t m_tail = 0;
    const size_t m_maxCapacity;
    bool m_full = false;
  };
} // namespace Zen
