#include "ZEN_Log.h"
#include "editor/src/GameLayer.h"
#include "zen.h"

class Zenith : public Zen::Application {
public:
  Zenith() {
    ZEN_LOG_INFO("Zenith constucted");
    pushLayer(new GameLayer());
  }

private:
};

Zen::Application *Zen::CreateApplication() { return new Zenith(); };
