#pragma once

#include <zen/core/ZEN_Core.h>
#include <zen/layer/ZEN_Layer.h>
#include <zen/zen_pch.h>

namespace Zen {
  class LayerList {
  public:
    using ListOfLayers = std::vector<std::unique_ptr<Layer>>;

    LayerList() = default;
    ~LayerList();

    void pushLayer(std::unique_ptr<Layer> layer);
    void pushOverlay(std::unique_ptr<Layer> overlay);

    void pushLayer(Layer *layer);
    void pushOverlay(Layer *overlay);

    void popLayer(Layer *layer);
    void popOverlay(Layer *overlay);

    ListOfLayers::iterator begin() { return m_layers.begin(); }
    ListOfLayers::iterator end() { return m_layers.end(); }
    ListOfLayers::reverse_iterator rbegin() { return m_layers.rbegin(); }
    ListOfLayers::reverse_iterator rend() { return m_layers.rend(); }

    ListOfLayers::const_iterator begin() const { return m_layers.begin(); }
    ListOfLayers::const_iterator end() const { return m_layers.end(); }
    ListOfLayers::const_reverse_iterator rbegin() const { return m_layers.rbegin(); }
    ListOfLayers::const_reverse_iterator rend() const { return m_layers.rend(); }

  private:
    ListOfLayers m_layers;
    size_t m_layerInsertIndex = 0;
  };
}; // namespace Zen