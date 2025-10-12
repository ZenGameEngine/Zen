#include <zen/events/ZEN_Events.h>

namespace Zen {
  void EventsDispatcher::dispatch(const ZenEvent &event) {
    for (const auto &l : m_listeners) {
      EventListener *eventListener = l.listener_ptr;
      if (eventListener && eventListener->onEvent(event)) { // if not null and if onEvent == true
        break;
      }
    }
  }

  void EventsDispatcher::registerListener(EventListener *newListener) {
    if (!newListener) {
      return;
    }

    auto start = m_listeners.begin();
    auto end   = m_listeners.end();

    const int p = newListener->getPriority();

    auto duplicate = std::find_if(start, end, [newListener](Listener &l) {
      return newListener == l.listener_ptr;
    });
    if (duplicate != end) {
      return;
    }

    auto position = std::find_if(start, end, [p](const Listener &l) {
      return p > l.listener_ptr->getPriority();
    });
    m_listeners.insert(position, Listener(p, newListener));
  }

  void EventsDispatcher::unregisterListener(EventListener *targetListener) {
    if (!targetListener) {
      return;
    }

    auto start = m_listeners.begin();
    auto end   = m_listeners.end();

    auto it = std::find_if(start, end, [targetListener](Listener &l) {
      return targetListener == l.listener_ptr;
    });
    if (it != end) {
      m_listeners.erase(it);
    }
  }

}; // namespace Zen
