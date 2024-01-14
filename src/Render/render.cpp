#include "render.hpp"

Render::Render() {
    window = std::make_shared<sf::RenderWindow>(
        sf::VideoMode(WIDTH, HEIGHT), "Music Spectrum",
        sf::Style::Titlebar | sf::Style::Close);
    desktop = std::make_shared<sf::VideoMode>(sf::VideoMode::getDesktopMode());
    window->setPosition(
        sf::Vector2i(desktop->width / 2.f - window->getSize().x / 2.f,
                     desktop->height / 2.f - window->getSize().y / 2.f));

    spectrum_ptr = std::make_shared<Spectrum>(window);
    hud_ptr = std::make_shared<HUD>(window, spectrum_ptr);
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
                handleEvents(event);
            }
        }

        ImGui::SFML::Update(*window, clock.restart());

        window->clear();

        hud_ptr->run();
        spectrum_ptr->run();

        window->display();
    }
}
