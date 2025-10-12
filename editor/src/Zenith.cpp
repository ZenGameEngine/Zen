#include "ZEN_Log.h"
#include "zen.h"

class Zenith : public Zen::Application {
  public:
    Zenith() {
      ZEN_LOG_INFO("Zenith constucted");
    }
  private:
};

Zen::Application *Zen::CreateApplication() { return new Zenith(); };
