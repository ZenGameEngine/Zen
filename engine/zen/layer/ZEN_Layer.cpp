#include <zen/layer/ZEN_Layer.h>

namespace Zen {
  Layer::Layer(int priority) : m_priority(priority) {}

  int Layer::getPriority() const { return m_priority; }
} // namespace Zen