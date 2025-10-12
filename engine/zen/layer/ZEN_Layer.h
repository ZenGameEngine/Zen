#pragma once

#include <zen/core/ZEN_Core.h>
#include <zen/events/ZEN_Event.h>
#include <zen/zen_pch.h>

namespace Zen {
  class Layer : public EventListener {
  public:
    Layer(int priority);
    virtual ~Layer() = default;

    virtual void onAttach() {}
    virtual void onDetach() {}
    virtual void onUpdate() {}
    virtual bool onEvent(const ZenEvent &event) = 0;

    virtual void onGUIRender() {}

    int getPriority() const;

  protected:
  private:
    int m_priority;
  };
}; // namespace Zen