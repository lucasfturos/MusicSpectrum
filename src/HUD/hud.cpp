#include "hud.hpp"

HUD::HUD(std::shared_ptr<sf::RenderWindow> win) : window(win) {
    if (!ImGui::SFML::Init(*window, false)) {
        throw std::runtime_error("Erro ao inicializar RenderWindow!");
    }
    styleWidget();

    ImGui::GetIO().Fonts->Clear();
    ImGui::GetIO().Fonts->AddFontFromFileTTF("./assets/font/Roboto-Regular.ttf",
                                             18.f);
    if (!ImGui::SFML::UpdateFontTexture()) {
        throw std::runtime_error("Update Font Texture");
    }

    sample_buffer.reserve(buffer_size);
}

HUD::~HUD() { ImGui::SFML::Shutdown(); }

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
