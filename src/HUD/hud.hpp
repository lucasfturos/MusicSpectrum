#pragma once

#include "../../external/imgui-SFML.h"
#include "../../external/imgui.h"
#include "../util.hpp"

class HUD {
  private:
    float volume;
    bool isPlaying;
    bool isStop;
    int fftMode = 0;
    int spectrumMode = 0;

    std::shared_ptr<sf::RenderWindow> window;

    sf::Clock clock;
    sf::Sound sound;

    std::vector<std::string> openFileDialog();

    void modeAudio();
    void styleWidget();
    void controlAudio();

  public:
    void run();

    HUD(std::shared_ptr<sf::RenderWindow> win, sf::Sound sound);
    ~HUD();
};
