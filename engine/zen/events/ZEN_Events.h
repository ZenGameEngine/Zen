#pragma once

#include <zen/zen_pch.h>

#include <zen/events/ZEN_Event.h>

namespace Zen {
  class EventListener {
  public:
    virtual ~EventListener() = default;

    virtual bool onEvent(const ZenEvent &event) = 0;
    virtual int getPriority() const             = 0;
  };

  class EventsDispatcher {
  public:
    void dispatch(const ZenEvent &event);
    void registerListener(EventListener *newListener);
    void unregisterListener(EventListener *targetListener);

  private:
    struct Listener {
      int priority;
      EventListener *listener_ptr;
    };

    std::vector<Listener> m_listeners;
  };
}; // namespace Zen
