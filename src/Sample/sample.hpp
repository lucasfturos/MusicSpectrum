#pragma once

#include "../HUD/hud.hpp"

/*!
 * Classe auxiliar para processamento de amostras de áudio.
 *
 * A classe `Sample` fornece métodos para converter amostras de áudio estéreo
 * para mono e recuperar um buffer de amostras de acordo com o estado atual
 * do objeto `HUD`.
 */
class Sample {
  private:
    std::shared_ptr<HUD> hud_ptr;

  public:
    void processStereoToMono();
    void getSampleBuffer();

    Sample(std::shared_ptr<HUD> hud);
};
