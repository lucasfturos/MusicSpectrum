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
}

void HUD::openFileDialog() {
    ImGui::Text("Select Audio File");

    if (ImGui::Button("Select File")) {
        const char *filters[] = {"*.wav"};
        const char *filename = tinyfd_openFileDialog("Open File", "./assets", 1,
                                                     filters, "Wave files", 0);
        if (filename != nullptr) {
            spectrum_ptr->setFileName(filename);
            std::cout << "Selected file: " << filename << '\n';
        } else {
            std::cerr << "No file selected.\n";
        }
    }
}

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
        isPlaying = false;
    }

    ImGui::SameLine();
    if (ImGui::Button("Next")) {
    }
    ImGui::Spacing();
    ImGui::Spacing();
    if (ImGui::Button("Mute")) {
        isMuted = !isMuted;
        if (isMuted) {
            orig_volume = volume;
            volume = 0.f;
        } else {
            volume = orig_volume;
        }
        sound.setVolume(volume);
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
    spectrum_ptr->setOption(option);
}
