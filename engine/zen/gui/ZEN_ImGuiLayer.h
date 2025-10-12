#pragma once

#include <zen/zen_pch.h>

#include <include/imgui/imgui.h>
#include <zen/layer/ZEN_Layer.h>

namespace Zen {
class ImGuiLayer : public Layer {
public:
  ImGuiLayer() = default;
  ~ImGuiLayer() = default;

  void onAttach() override;
  void onDetach() override;
  void onUpdate() override;
  bool onEvent(const SDL_Event &event) override;

  void begin();
  void end();

};

} // namespace Zen
