#include "DemoSwitcher.h"
#include "ZEN_Log.h"
#include "editor/src/GameLayer.h"
#include "particles/ZEN_ParticleTestLayer.h"
#include "zen.h"
class Zenith : public Zen::Application {
public:
  Zenith() {
    // TODO: Find a way to 'register' layers so when Application->init(); is called, the ;layers are
    // pushed instead of in the constructor
    // pushLayer(new Zen::DemoSwitcher);
    ZEN_LOG_INFO("Zenith constucted");
  }

private:
};

Zen::Application *Zen::CreateApplication() { return new Zenith(); };
