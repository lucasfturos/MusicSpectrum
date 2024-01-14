#include "render.hpp"

void Render::handleEvents(sf::Event &event) {
    event.key.code == sf::Keyboard::Space ? toggleMusicPlayback() : (void(0));

    event.key.code == sf::Keyboard::M ? toggleMusicMute() : (void(0));

    event.key.code == sf::Keyboard::Q ? window->close() : (void(0));

    if (event.key.code == sf::Keyboard::Enter) {
        hud_ptr->sound.stop();
        hud_ptr->isPlaying = false;
    }

    if (event.key.code == sf::Keyboard::Up) {
        hud_ptr->volume += 10.f;
        hud_ptr->volume > 100.f ? hud_ptr->volume = 100.f : 0;
        hud_ptr->sound.setVolume(hud_ptr->volume);
    }

    if (event.key.code == sf::Keyboard::Down) {
        hud_ptr->volume -= 10.f;
        hud_ptr->volume < .0f ? hud_ptr->volume = 0.f : 0;
        hud_ptr->sound.setVolume(hud_ptr->volume);
    }
}

void Render::toggleMusicMute() {
    hud_ptr->isMuted = !hud_ptr->isMuted;
    hud_ptr->sound.setVolume(hud_ptr->isMuted ? 0.f : hud_ptr->volume);
}

void Render::toggleMusicPlayback() {
    if (hud_ptr->isPlaying) {
        hud_ptr->sound.pause();
        hud_ptr->isPlaying = false;
    } else {
        hud_ptr->sound.play();
        hud_ptr->sound.setVolume(hud_ptr->volume);
        hud_ptr->isPlaying = true;
    }
}
