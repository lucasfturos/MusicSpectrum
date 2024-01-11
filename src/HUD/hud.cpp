#include "hud.hpp"

HUD::HUD(std::shared_ptr<sf::RenderWindow> win, sf::Sound sound)
    : window(win), sound(sound) {
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
}

HUD::~HUD() { ImGui::SFML::Shutdown(); }

void HUD::styleWidget() {
    ImGuiStyle &style = ImGui::GetStyle();
    style.WindowRounding = 5.3f;
    style.FrameRounding = 2.3f;
    style.ScrollbarRounding = 0;

    style.Colors[ImGuiCol_Text] = ImVec4(0.9f, 0.9f, 0.9f, 0.9f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.6f, 0.6f, 0.6f, 1.0f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.3f, 0.3f, 0.3f, 0.3f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.3f, 0.3f, 0.3f, 0.3f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.0f, 0.0f, 0.1f, 1.0f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.9f, 0.8f, 0.8f, 0.4f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.9f, 0.6f, 0.6f, 0.4f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.8f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.1f, 0.1f, 0.1f, 0.8f);
    // Botões
    style.Colors[ImGuiCol_Button] = ImVec4(0.16f, 0.16f, 0.16f, 1.0f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.16f, 0.16f, 0.16f, 0.5f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.31f, 0.28f, 0.28f, 1.0f);
    // Slider
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.70f, 0.70f, 0.70f, 0.62f);
    style.Colors[ImGuiCol_SliderGrabActive] =
        ImVec4(0.30f, 0.30f, 0.30f, 0.84f);
    // RadioButton
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.90f, 0.90f, 0.90f, 0.83f);
}

std::vector<std::string> HUD::openFileDialog() { return {""}; }

void HUD::controlAudio() {
    ImGui::Text("Audio");
    ImGui::Spacing();

    if (ImGui::Button(!isPlaying ? "Play###ViewMode" : "Pause###ViewMode")) {
        if (isPlaying) {
            sound.pause();
            isPlaying = false;
        } else {
            sound.play();
            sound.setVolume(volume);
            isPlaying = true;
        }
    }
    ImGui::SameLine();
    if (ImGui::Button("Prev")) {
    }

    ImGui::SameLine();
    if (ImGui::Button("Stop")) {
        sound.stop();
    }

    ImGui::SameLine();
    if (ImGui::Button("Next")) {
    }
    ImGui::Spacing();
    ImGui::Spacing();
    if (ImGui::Button("Mute")) {
    }
    ImGui::SameLine();
    if (ImGui::SliderFloat("Volume", &volume, 0.f, 100.f, "%.0f")) {
        volume += 0.f;
        volume = std::max(0.f, std::min(100.f, volume));
        sound.setVolume(volume);
    }
}

void HUD::modeAudio() {
    ImGui::Text("Mode");
    ImGui::Spacing();

    ImGui::RadioButton("NoFFT", &fftMode, 0);
    ImGui::SameLine();
    ImGui::RadioButton("FFT", &fftMode, 1);
    ImGui::Spacing();
    ImGui::RadioButton("Oscillation", &spectrumMode, 0);
    ImGui::SameLine();
    ImGui::RadioButton("Spectrum", &spectrumMode, 1);
}

void HUD::run() {
    window->clear();
    ImGui::SFML::Update(*window, clock.restart());

    ImGui::Begin("HUD Audio", nullptr,
                 ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                     ImGuiWindowFlags_NoScrollbar);
    ImGui::SetWindowPos(ImVec2(0, 0));
    ImGui::SetWindowSize(ImVec2(400, 300));

    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);

    ImGui::Separator();
    ImGui::Text("Open Audio Files");
    if (ImGui::Button("Select File")) {
        std::vector<std::string> selectedFile = openFileDialog();
    }
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
    window->display();
}
