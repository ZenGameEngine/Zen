#pragma once

#include <zen/time/ZEN_DeltaTime.h>
#include <zen/zen_pch.h>

#include <include/imgui/imgui.h>
#include <zen/layer/ZEN_Layer.h>

namespace Zen {
  class ImGuiLayer : public Layer {
  public:
    ImGuiLayer() : Layer(100) {}
    ~ImGuiLayer() = default;

    void onAttach() override;
    void onDetach() override;
    void onUpdate(DeltaTime deltaTime) override;
    bool onEvent(const ZenEvent &event) override;

    void begin();
    void end();
  };

} // namespace Zen
