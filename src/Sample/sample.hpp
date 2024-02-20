#pragma once

#include "../HUD/hud.hpp"

class Sample {
  private:
    std::shared_ptr<HUD> hud_ptr;

  public:
    void monoSample();
    void getSampleBuffer();

    Sample(std::shared_ptr<HUD> hud);
};
