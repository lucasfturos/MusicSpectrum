#pragma once

#include "../../external/ImGui-SFML/imgui-SFML.h"
#include "../../external/ImGuiFileDialog/ImGuiFileDialog.h"
#include "../../external/imgui/imgui.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

// Constantes
const int WIDTH = 1000;
const int HEIGHT = 720;
const int HUD_WIDTH = 400;
const int HUD_HEIGHT = 300;
const size_t buffer_size = 1000;

/*!
 * Classe que representa a interface gráfica do usuário (GUI) para interagir com
 * arquivos de áudio.
 *
 * A classe `HUD` (Heads-Up Display) gerencia a interface gráfica do usuário
 * para interação com arquivos de áudio. Ela fornece controles para reproduzir,
 * pausar, avançar, retroceder, ajustar volume, exibir e selecionar arquivos de
 * áudio, entre outras funcionalidades.
 */
class HUD {
  private:
    const float icon_size = 17.0f;

    int fftMode = 0;
    int spectrumMode = 0;
    float volume = 10.f;

    bool isMuted = false;
    bool isPlaying = false;
    bool audioListWindow = false;

    std::size_t selectedIndex = 0;
    std::vector<std::string> list_audio;

    sf::Texture play_tex, pause_tex;
    sf::Texture stop_tex, forward_tex;
    sf::Texture backward_tex, previous_tex;
    sf::Texture next_tex, mute_tex;
    sf::Texture volume_tex;

    std::shared_ptr<sf::RenderWindow> window;

    // GUI
    void initFont();
    void audioList();
    void modeAudio();
    void initTexture();
    void styleWidget();
    void drawAudioHUD();
    void controlAudio();
    void openFileDialog();
    void showAudioListWindow();

    // Events
    void skipForward();
    void skipBackward();
    void playNextAudio();
    void resetControls();
    void toggleMusicMute();
    void playPreviousAudio();
    void toggleMusicPlayback();

    // Util
    void setSoundBuffer(const std::string &filename);

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
