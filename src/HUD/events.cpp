#include "hud.hpp"

void HUD::handleEvents(sf::Event &event) {
    event.key.code == sf::Keyboard::Space ? toggleMusicPlayback() : (void(0));

    event.key.code == sf::Keyboard::M ? toggleMusicMute() : (void(0));

    event.key.code == sf::Keyboard::Q ? window->close() : (void(0));

    event.key.code == sf::Keyboard::Left ? skipBackward() : (void(0));

    event.key.code == sf::Keyboard::Right ? skipForward() : (void(0));

    if (event.key.code == sf::Keyboard::Enter) {
        sound.stop();
        isPlaying = false;
    }

    if (event.key.code == sf::Keyboard::Up) {
        volume += 10.f;
        volume > 100.f ? volume = 100.f : 0;
        sound.setVolume(volume);
    }

    if (event.key.code == sf::Keyboard::Down) {
        volume -= 10.f;
        volume < .0f ? volume = 0.f : 0;
        sound.setVolume(volume);
    }
}

void HUD::toggleMusicMute() {
    isMuted = !isMuted;
    sound.setVolume(isMuted ? 0.f : volume);
}

void HUD::toggleMusicPlayback() {
    if (isPlaying) {
        sound.pause();
        isPlaying = false;
    } else {
        sound.play();
        sound.setVolume(volume);
        isPlaying = true;
    }
}

void HUD::skipForward() {
    sf::Time currentOffset = sound.getPlayingOffset();
    sf::Time newOffset = currentOffset + sf::seconds(10.0f);
    sound.setPlayingOffset(newOffset);
}

void HUD::skipBackward() {
    sf::Time currentOffset = sound.getPlayingOffset();
    sf::Time newOffset = currentOffset - sf::seconds(10.0f);
    sound.setPlayingOffset(newOffset);
}
