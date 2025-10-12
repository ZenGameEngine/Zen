#include <zen/events/ZEN_Event.h>
#include <zen/events/ZEN_EventBuffer.h>

namespace Zen {

  void EventBuffer::enqueue(ZenEvent event) {
    m_buffer[m_head] = event;

    if (m_full) {
      m_tail = (m_tail + 1) % m_maxCapacity;
    }

    m_head = (m_head + 1) % m_maxCapacity;
    m_full = m_head == m_tail;
  }

  ZenEvent EventBuffer::dequeue() {
    if (isEmpty()) {
      return {};
    }

    ZenEvent event = m_buffer[m_tail];

    m_full = false;
    m_tail = (m_tail + 1) % m_maxCapacity;

    return event;
  }

  void EventBuffer::flush() {
    m_head = m_tail;
    m_full = false;
  }

  bool EventBuffer::isEmpty() const { return (!m_full && (m_head == m_tail)); }
  bool EventBuffer::isFull() const { return m_full; }

  size_t EventBuffer::capacity() const { return m_maxCapacity; }
  size_t EventBuffer::size() const {
    size_t size = m_maxCapacity;

    if (!m_full) {
      if (m_head >= m_tail) {
        size = m_head - m_tail;
      } else {
        size = m_maxCapacity + m_head - m_tail;
      }
    }

    return size;
  }

} // namespace Zen
