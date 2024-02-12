#include "render.hpp"
#include "../../external/imgui/imgui_impl_opengl3.h"
#include <chrono>
#include <thread>

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

void Render::run() {
    window->setVerticalSyncEnabled(true);
    auto prev_time = std::chrono::high_resolution_clock::now();

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed) {
                window->close();
            } else if (event.type == sf::Event::KeyPressed) {
                hud_ptr->handleEvents(event);
            }
            event.type == sf::Event::MouseWheelMoved
                ? spectrum3D_ptr->getWhellDelta(event.mouseWheel.delta)
                : void(0);
        }

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

        window->pushGLStates();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        window->popGLStates();

        window->display();

        auto current_time = std::chrono::high_resolution_clock::now();
        auto elapsed_time =
            std::chrono::duration_cast<std::chrono::duration<double>>(
                current_time - prev_time);

        if (elapsed_time.count() < frame_duration) {
            auto sleep_duration = std::chrono::duration<double>(
                frame_duration - elapsed_time.count());
            std::this_thread::sleep_for(
                std::chrono::duration_cast<std::chrono::milliseconds>(
                    sleep_duration));
        }

        prev_time = std::chrono::high_resolution_clock::now();
    }
}
