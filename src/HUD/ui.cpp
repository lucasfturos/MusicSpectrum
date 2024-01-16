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
    style.Colors[ImGuiCol_Button] = ImVec4(0.16f, 0.16f, 0.16f, 1.0f);
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
    ImGui::Text("Select Audio File");

    if (ImGui::Button("Select File")) {
        IGFD::FileDialogConfig config;
        config.path = ".";
        config.sidePaneWidth = 350.0f;

        ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey",
                                                "Choose File", ".wav", config);
    }

    if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) {
        if (ImGuiFileDialog::Instance()->IsOk()) {
            std::string filePathName =
                ImGuiFileDialog::Instance()->GetFilePathName();

            listAudio.push_back(filePathName);
        }

        ImGuiFileDialog::Instance()->Close();
    }
}

void HUD::controlAudio() {
    ImGui::Text("Audio");
    ImGui::Spacing();

    if (ImGui::Button(!isPlaying ? "Play###ViewMode" : "Pause###ViewMode")) {
        toggleMusicPlayback();
    }
    ImGui::SameLine();
    if (ImGui::Button("<")) {
        skipBackward();
    }

    ImGui::SameLine();
    if (ImGui::Button("Stop")) {
        sound.stop();
        isPlaying = false;
    }

    ImGui::SameLine();
    if (ImGui::Button(">")) {
        skipForward();
    }
    ImGui::Spacing();
    ImGui::Spacing();
    if (ImGui::Button("Mute")) {
        toggleMusicMute();
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

    if (!fftMode && !spectrumMode) {
        option = 2;
    } else if (fftMode && !spectrumMode) {
        option = 1;
    } else if (fftMode && spectrumMode) {
        option = 3;
    } else if (!fftMode && spectrumMode) {
        option = 4;
    }
}

void HUD::audioList(std::size_t &selectedIndex) {
    for (auto item = 0UL; item < listAudio.size(); ++item) {
        const bool isSelected = (selectedIndex == item);

        size_t lastSlash = listAudio[item].find_last_of('/');
        std::string filename = listAudio[item].substr(lastSlash + 1);

        if (ImGui::Selectable(filename.c_str(), isSelected)) {
            selectedIndex = item;
            std::cout << listAudio[selectedIndex] << '\n';
            sound_buffer.loadFromFile(listAudio[selectedIndex]);
            sound.setBuffer(sound_buffer);
            resetControls();
        }
        if (isSelected) {
            ImGui::SetItemDefaultFocus();
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
        ImGui::SetWindowSize(ImVec2(HUD_WIDTH, HUD_HEIGHT));

        std::size_t selectedIndex = 0;
        audioList(selectedIndex);

        ImGui::End();
    }
}
