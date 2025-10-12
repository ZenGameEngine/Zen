#include <zen/layer/ZEN_LayerList.h>

namespace Zen {
  LayerList::~LayerList() {
    for (auto &l : m_layers) {
      if (l) {
        l->onDetach();
      }
    }
    m_layers.clear();
  }

  void LayerList::pushLayer(Layer *layer) { pushLayer(std::unique_ptr<Layer>(layer)); }

  void LayerList::pushOverlay(Layer *overlay) { pushOverlay(std::unique_ptr<Layer>(overlay)); }

  void LayerList::pushLayer(std::unique_ptr<Layer> layer) {
    const int priority = layer->getPriority();

    auto start = m_layers.begin();
    auto end   = m_layers.begin() + m_layerInsertIndex;

    auto position =
        std::upper_bound(start, end, priority, [](int i, const std::unique_ptr<Layer> &l) {
          return i < l->getPriority();
        });
    m_layers.insert(position, std::move(layer));
    m_layerInsertIndex++;
  }

  void LayerList::pushOverlay(std::unique_ptr<Layer> overlay) {
    m_layers.emplace_back(std::move(overlay));
  }

  void LayerList::popLayer(Layer *layer) {
    if (!layer) {
      return;
    }

    auto start = m_layers.begin();
    auto end   = m_layers.begin() + m_layerInsertIndex;

    auto it = std::find_if(start, end, [layer](const std::unique_ptr<Layer> &l) {
      return l.get() == layer;
    });

    if (it != m_layers.begin() + m_layerInsertIndex) {
      m_layers.erase(it);
      m_layerInsertIndex--;
    }
  }

  void LayerList::popOverlay(Layer *overlay) {
    if (!overlay)
      return;

    auto start = m_layers.begin() + m_layerInsertIndex;
    auto end   = m_layers.end();

    auto it = std::find_if(start, end, [overlay](const std::unique_ptr<Layer> &l) {
      return l.get() == overlay;
    });

    if (it != m_layers.end()) {
      m_layers.erase(it);
    }
  }
} // namespace Zen