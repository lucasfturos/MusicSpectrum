#include "hud.hpp"

// Construtor da classe HUD
HUD::HUD(std::shared_ptr<sf::RenderWindow> win) : window(win) {
    /*
     * Inicializa a interface gráfica do usuário (GUI) utilizando a biblioteca
     * ImGui. Carrega a fonte e as texturas necessárias.
     *
     * @param win: Um ponteiro compartilhado para uma janela RenderWindow do
     * SFML.
     * @throws std::runtime_error: Se ocorrer um erro ao inicializar a
     * RenderWindow.
     */
    if (!ImGui::SFML::Init(*window, false)) {
        throw std::runtime_error("Error when Initializing RenderWindow!");
    }
    styleWidget();

    initFont();

    initTexture();

    sample_buffer.reserve(buffer_size);
}

// Destrutor da classe HUD.
HUD::~HUD() { ImGui::SFML::Shutdown(); }

// Função de inicialização da fonte da interface
void HUD::initFont() {
    ImGui::GetIO().Fonts->Clear();
    ImGui::GetIO().Fonts->AddFontFromFileTTF("./assets/font/Roboto-Regular.ttf",
                                             18.f);
    if (!ImGui::SFML::UpdateFontTexture()) {
        throw std::runtime_error("Update Font Texture");
    }
}

// Função de inicialização dos icones
void HUD::initTexture() {
    if (!play_tex.loadFromFile("./assets/img/icon/botao-play.png")) {
        throw std::invalid_argument("Error Loading Texture Play");
    }
    if (!pause_tex.loadFromFile("./assets/img/icon/pausa.png")) {
        throw std::invalid_argument("Error Loading Texture Pause");
    }
    if (!stop_tex.loadFromFile("./assets/img/icon/pare.png")) {
        throw std::invalid_argument("Error Loading Texture Stop");
    }
    if (!forward_tex.loadFromFile("./assets/img/icon/avanco-rapido.png")) {
        throw std::invalid_argument("Error Loading Texture Forward");
    }
    if (!backward_tex.loadFromFile("./assets/img/icon/retroceder.png")) {
        throw std::invalid_argument("Error Loading Texture Backward");
    }
    if (!previous_tex.loadFromFile("./assets/img/icon/costas.png")) {
        throw std::invalid_argument("Error Loading Texture Previous");
    }
    if (!next_tex.loadFromFile("./assets/img/icon/proximo.png")) {
        throw std::invalid_argument("Error Loading Texture Next");
    }
    if (!mute_tex.loadFromFile("./assets/img/icon/mudo.png")) {
        throw std::invalid_argument("Error Loading Texture Mute");
    }
    if (!volume_tex.loadFromFile("./assets/img/icon/volume.png")) {
        throw std::invalid_argument("Error Loading Texture Volume");
    }
}

// Função define o buffer de áudio
void HUD::setSoundBuffer(const std::string &filename) {
    /*
     * @brief Define o buffer de som a partir de um arquivo de áudio.
     *
     * @param filename O caminho do arquivo de áudio.
     */
    sound_buffer.loadFromFile(filename);
    sound.setBuffer(sound_buffer);
    resetControls();
}

// Função principal para execução da interface gráfica
void HUD::run() {
    ImGui::Begin("Audio HUD", nullptr,
                 ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    ImGui::SetWindowPos(ImVec2(0, 0));
    ImGui::SetWindowSize(ImVec2(HUD_WIDTH, HUD_HEIGHT));

    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);

    ImGui::Separator();
    openFileDialog();

    ImGui::SameLine();

    showAudioListWindow();

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    controlAudio();

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    modeAudio();

    ImGui::PopFont();
    ImGui::End();

    ImGui::SFML::Render(*window);
}
