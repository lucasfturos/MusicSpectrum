#include "render.hpp"

void Render::handleEvents(sf::Event &event) {
    event.key.code == sf::Keyboard::Space ? toggleMusicPlayback() : (void(0));

    event.key.code == sf::Keyboard::Q ? window->close() : (void(0));

    if (event.key.code == sf::Keyboard::Enter) {
        spectrum_ptr->sound.stop();
        hud_ptr->isPlaying = false;
    }

    if (event.key.code == sf::Keyboard::Up) {
        hud_ptr->volume += 10.f;
        hud_ptr->volume > 100.f ? hud_ptr->volume = 100.f : 0;
        spectrum_ptr->sound.setVolume(hud_ptr->volume);
    }

    if (event.key.code == sf::Keyboard::Down) {
        hud_ptr->volume -= 10.f;
        hud_ptr->volume < .0f ? hud_ptr-> volume = 0.f : 0;
        spectrum_ptr->sound.setVolume(hud_ptr->volume);
    }
}

void Render::toggleMusicPlayback() {
    if (hud_ptr->isPlaying) {
        spectrum_ptr->sound.pause();
        hud_ptr->isPlaying = false;
    } else {
        spectrum_ptr->sound.play();
        spectrum_ptr->sound.setVolume(hud_ptr->volume);
        hud_ptr->isPlaying = true;
    }
}
