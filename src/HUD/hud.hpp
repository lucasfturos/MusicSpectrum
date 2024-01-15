#pragma once

#include "../../external/imgui-SFML.h"
#include "../../external/imgui.h"
#include "../../external/tinyfiledialogs.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

const int WIDTH = 1000;
const int HEIGHT = 600;

class HUD {
  private:
    const size_t buffer_size = 1000;

    int fftMode = 0;
    int spectrumMode = 0;

    float volume = 10.f;

    bool isMuted = false;
    bool isPlaying = false;

    std::string filename;

    std::shared_ptr<sf::RenderWindow> window;

    void modeAudio();
    void styleWidget();
    void skipForward();
    void skipBackward();
    void controlAudio();
    void openFileDialog();
    void toggleMusicMute();
    void toggleMusicPlayback();

  public:
    int option = 2;

    sf::Sound sound;
    sf::SoundBuffer sound_buffer;
    std::vector<sf::Int16> sample_buffer;

    void run();
    void handleEvents(sf::Event &event);

    HUD(std::shared_ptr<sf::RenderWindow> win);
    ~HUD();
};
