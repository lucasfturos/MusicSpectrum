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

void Render::frameRate(time_point<high_resolution_clock> &prev_time) {
    auto current_time = high_resolution_clock::now();
    auto elapsed_time =
        duration_cast<duration<double>>(current_time - prev_time);

    if (elapsed_time.count() < frame_duration) {
        auto sleep_duration =
            duration<double>(frame_duration - elapsed_time.count());
        std::this_thread::sleep_for(
            duration_cast<milliseconds>(sleep_duration));
    }

    prev_time = high_resolution_clock::now();
}

void Render::run() {
    window->setVerticalSyncEnabled(true);
    auto prev_time = high_resolution_clock::now();

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

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        window->clear();

        ImGui_ImplOpenGL3_NewFrame();

        hud_ptr->run();
        window->pushGLStates();
        spectrum_ptr->run(std::bind(&Render::handlePlot, this,
                                    std::placeholders::_1,
                                    std::placeholders::_2));
        window->popGLStates();

        spectrum3D_ptr->run(std::bind(&Render::handlePlot, this,
                                      std::placeholders::_1,
                                      std::placeholders::_2));

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window->display();

        frameRate(prev_time);
    }
}
