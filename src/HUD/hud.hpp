#pragma once

#include "../../external/ImGui-SFML/imgui-SFML.h"
#include "../../external/ImGuiFileDialog/ImGuiFileDialog.h"
#include "../../external/imgui/imgui.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

const int WIDTH = 1000;
const int HEIGHT = 720;
const int HUD_WIDTH = 400;
const int HUD_HEIGHT = 300;
const size_t buffer_size = 1000;

class HUD {
  private:
    int fftMode = 0;
    int spectrumMode = 0;
    float volume = 10.f;
    bool isMuted = false;
    bool isPlaying = false;
    bool audioListWindow = false;
    std::vector<std::string> listAudio;

    std::shared_ptr<sf::RenderWindow> window;

    void modeAudio();
    void skipForward();
    void styleWidget();
    void drawAudioHUD();
    void controlAudio();
    void skipBackward();
    void resetControls();
    void openFileDialog();
    void toggleMusicMute();
    void showAudioListWindow();
    void toggleMusicPlayback();
    void audioList(std::size_t &selectedIndex);

  public:
    int option = 3;

    sf::Sound sound;
    sf::SoundBuffer sound_buffer;
    std::vector<sf::Int16> sample_buffer;

    void run();
    void handleEvents(sf::Event &event);

    HUD(std::shared_ptr<sf::RenderWindow> win);
    ~HUD();
};
