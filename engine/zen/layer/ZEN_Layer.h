#pragma once

#include <zen/time/ZEN_DeltaTime.h>
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
    virtual void onUpdate(DeltaTime deltaTime) {}
    virtual bool onEvent(const ZenEvent &event) = 0;

    virtual void onGUIRender() {}

    int getPriority() const;

  protected:
  private:
    int m_priority;
  };
}; // namespace Zen