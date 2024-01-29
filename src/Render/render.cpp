#include "render.hpp"
#include "../../external/imgui/imgui_impl_opengl3.h"

Render::Render() {
    window = std::make_shared<sf::RenderWindow>(
        sf::VideoMode(WIDTH, HEIGHT), "Music Spectrum",
        sf::Style::Titlebar | sf::Style::Close);

    desktop = std::make_shared<sf::VideoMode>(sf::VideoMode::getDesktopMode());
    window->setPosition(
        sf::Vector2i(desktop->width / 2.f - window->getSize().x / 2.f,
                     desktop->height / 2.f - window->getSize().y / 2.f));

    hud_ptr = std::make_shared<HUD>(window);
    fft_ptr = std::make_shared<FFT<sf::Int16>>();
    spectrum_ptr = std::make_shared<Spectrum>(window, hud_ptr, fft_ptr);
    spectrum3D_ptr =
        std::make_shared<Spectrum3D>(window, hud_ptr, spectrum_ptr, fft_ptr);
}

void Render::handlePlot(std::vector<std::complex<float>> spectrum,
                        std::size_t fft_size) {
    switch (hud_ptr->option) {
    case 1:
        fft_ptr->fftAnalyze(hud_ptr->sample_buffer, 1, spectrum, fft_size);
        spectrum_ptr->viewWaveformFFT();
        break;
    case 2:
        spectrum_ptr->viewWaveform();
        break;
    case 3:
        fft_ptr->fftAnalyze(hud_ptr->sample_buffer, 1, spectrum, fft_size);
        spectrum_ptr->viewWaveformRectFFT();
        break;
    case 4:
        spectrum_ptr->viewWaveformRect();
        break;
    case 5:
        fft_ptr->fftAnalyze(hud_ptr->sample_buffer, 1, spectrum, fft_size);
        spectrum3D_ptr->viewWaveformFFT();
        break;
    case 6:
        spectrum3D_ptr->viewWaveform();
        break;
    default:
        break;
    }
}

void Render::run() {
    window->setVerticalSyncEnabled(true);
    window->setFramerateLimit(60);

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed) {
                window->close();
            } else if (event.type == sf::Event::KeyPressed) {
                hud_ptr->handleEvents(event);
            }
        }
        spectrum3D_ptr->handleMouse();

        ImGui::SFML::Update(*window, clock.restart());

        window->clear();

        window->pushGLStates();
        hud_ptr->run();
        spectrum_ptr->run(std::bind(&Render::handlePlot, this,
                                    std::placeholders::_1,
                                    std::placeholders::_2));
        window->popGLStates();

        window->pushGLStates();
        ImGui_ImplOpenGL3_NewFrame();
        window->popGLStates();

        spectrum3D_ptr->run(std::bind(&Render::handlePlot, this,
                                      std::placeholders::_1,
                                      std::placeholders::_2));

        spectrum3D_ptr->viewWaveform();
        window->pushGLStates();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        window->popGLStates();

        window->display();
    }
}
