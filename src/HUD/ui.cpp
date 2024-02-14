#include "hud.hpp"

void HUD::styleWidget() {
    ImGuiStyle &style = ImGui::GetStyle();
    // Window
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
    style.Colors[ImGuiCol_Button] = ImVec4(0.16f, 0.16f, 0.16f, 0.0f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.16f, 0.16f, 0.16f, 0.5f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.31f, 0.28f, 0.28f, 1.0f);
    // Slider
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.70f, 0.70f, 0.70f, 0.62f);
    style.Colors[ImGuiCol_SliderGrabActive] =
        ImVec4(0.30f, 0.30f, 0.30f, 0.84f);
    // RadioButton
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.90f, 0.90f, 0.90f, 0.83f);
    // Header
    style.Colors[ImGuiCol_Header] = ImVec4(0.12f, 0.12f, 0.12f, 1.0f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.24f, 0.24f, 0.24f, 1.0f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.31f, 0.31f, 0.31f, 1.0f);
}

void HUD::openFileDialog() {
    ImVec2 dialog_maxsize = ImVec2(HUD_WIDTH * 2.f, HUD_HEIGHT * 2.f);
    ImGui::Text("Select Audio File");

    if (ImGui::Button("Select File")) {
        const char *filter = "Audio File (*.flac,*.wav){.flac,.wav}";
        IGFD::FileDialogConfig config;
        config.path = "../audio";
        config.sidePaneWidth = 450.0f;

        ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey",
                                                "Choose File", filter, config);
    }

    if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey",
                                             ImGuiWindowFlags_NoCollapse |
                                                 ImGuiWindowFlags_NoResize,
                                             dialog_maxsize, dialog_maxsize)) {
        if (ImGuiFileDialog::Instance()->IsOk()) {
            std::string filePathName =
                ImGuiFileDialog::Instance()->GetFilePathName();
            if (list_audio.empty()) {
                setSoundBuffer(filePathName);
            }

            auto it =
                std::find(list_audio.begin(), list_audio.end(), filePathName);
            if (it == list_audio.end()) {
                list_audio.push_back(filePathName);
            } else {
                setSoundBuffer(filePathName);
            }
        }

        ImGuiFileDialog::Instance()->Close();
    }
}

void HUD::controlAudio() {
    ImGui::Text("Audio");
    ImGui::Spacing();
    if (ImGui::ImageButton(!isPlaying ? play_tex : pause_tex,
                           sf::Vector2f(icon_size, icon_size))) {
        toggleMusicPlayback();
    }
    ImGui::SameLine();
    if (ImGui::ImageButton(previous_tex, sf::Vector2f(icon_size, icon_size))) {
        playPreviousAudio();
    }
    ImGui::SameLine();
    if (ImGui::ImageButton(backward_tex, sf::Vector2f(icon_size, icon_size))) {
        skipBackward();
    }
    ImGui::SameLine();
    if (ImGui::ImageButton(stop_tex, sf::Vector2f(icon_size, icon_size))) {
        sound.stop();
        isPlaying = false;
    }
    ImGui::SameLine();
    if (ImGui::ImageButton(forward_tex, sf::Vector2f(icon_size, icon_size))) {
        skipForward();
    }
    ImGui::SameLine();
    if (ImGui::ImageButton(next_tex, sf::Vector2f(icon_size, icon_size))) {
        playNextAudio();
    }
    ImGui::Spacing();
    ImGui::Spacing();
    if (ImGui::ImageButton(isMuted ? mute_tex : volume_tex,
                           sf::Vector2f(icon_size + 3, icon_size + 3))) {
        toggleMusicMute();
    }
    ImGui::SameLine();
    if (ImGui::SliderFloat(" ", &volume, 0.f, 100.f, "%.0f")) {
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
    ImGui::RadioButton("Spectrum", &spectrumMode, 1);
    ImGui::SameLine();
    ImGui::RadioButton("Oscillation", &spectrumMode, 0);
    ImGui::SameLine();
    ImGui::RadioButton("Oscillation3D", &spectrumMode, 2);

    if (fftMode == 0) {
        switch (spectrumMode) {
        case 0:
            option = 2;
            break;
        case 1:
            option = 4;
            break;
        case 2:
            option = 6;
            break;
        default:
            break;
        }
    } else if (fftMode == 1) {
        switch (spectrumMode) {
        case 0:
            option = 1;
            break;
        case 1:
            option = 3;
            break;
        case 2:
            option = 5;
            break;
        default:
            break;
        }
    }
}

void HUD::audioList() {
    for (auto item = 0UL; item < list_audio.size(); ++item) {
        const bool isSelected = (selectedIndex == item);

        std::size_t lastSlash = list_audio[item].find_last_of('/');
        std::string filename = list_audio[item].substr(lastSlash + 1);

        if (ImGui::Selectable(filename.c_str(), isSelected)) {
            selectedIndex = item;
            std::cout << list_audio[selectedIndex] << '\n';
            setSoundBuffer(list_audio[selectedIndex]);
        }
    }
}

void HUD::showAudioListWindow() {
    if (ImGui::Button("Show Audio List")) {
        audioListWindow = !audioListWindow;
    }

    if (audioListWindow) {
        ImGui::Begin("Audio List", nullptr,
                     ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
        ImGui::SetWindowPos(ImVec2(HUD_WIDTH + 10, 0));
        ImGui::SetWindowSize(ImVec2(HUD_WIDTH, HUD_HEIGHT - 100));

        audioList();

        ImGui::End();
    }
}
