#include "DemoSwitcher.h"
#include "ZEN_Log.h"
#include "editor/src/GameLayer.h"
#include "particles/ZEN_ParticleTestLayer.h"
#include "zen.h"
class Zenith : public Zen::Application {
public:
  Zenith() { ZEN_LOG_INFO("[Zenith] Application constructed"); }
  virtual void registerLayers() override { pushLayer(new Zen::DemoSwitcher); };

private:
};

Zen::Application *Zen::CreateApplication() { return new Zenith(); };
