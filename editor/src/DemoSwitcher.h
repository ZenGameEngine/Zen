#pragma once

#include "editor/src/GameLayer.h"
#include <zen/events/ZEN_Event.h>
#include <zen/inputs/ZEN_KeyCodes.h>
#include <zen/layer/ZEN_Layer.h>
#include <zen/particles/ZEN_ParticleTestLayer.h>

namespace Zen {

  class DemoSwitcher : public Layer {
  public:
    DemoSwitcher() : Layer(99) {}

    void onAttach() override;
    void onUpdate(DeltaTime deltaTime) override;
    bool onEvent(const ZenEvent &event) override { return false; }
    void onGUIRender() override;

  private:
    GameLayer *m_gameLayer             = nullptr;
    ParticleTestLayer *m_particleLayer = nullptr;
    Layer *m_currentActive             = nullptr;

    void switchDemo();
    bool m_isShowingGame = true;
    float m_seconds      = 0;
  };

} // namespace Zen
