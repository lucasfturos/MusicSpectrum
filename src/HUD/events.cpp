#include "hud.hpp"

// Função de controle dos eventos
void HUD::handleEvents(sf::Event &event) {
    /*
     * @brief Trata os eventos de entrada da janela SFML.
     *
     * Esta função trata os eventos de teclado da janela SFML, respondendo a
     * diferentes teclas para controlar a reprodução de áudio, ajustar o volume,
     * pular faixas e fechar a janela.
     *
     * @param event: Referência ao objeto sf::Event que contém informações
     * sobre o evento.
     */
    event.key.code == sf::Keyboard::Space ? toggleMusicPlayback() : (void(0));

    event.key.code == sf::Keyboard::M ? toggleMusicMute() : (void(0));

    event.key.code == sf::Keyboard::Q ? window->close() : (void(0));

    event.key.code == sf::Keyboard::Left ? skipBackward() : (void(0));

    event.key.code == sf::Keyboard::Right ? skipForward() : (void(0));

    event.key.code == sf::Keyboard::Period ? playNextAudio() : (void(0));

    event.key.code == sf::Keyboard::Comma ? playPreviousAudio() : (void(0));

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

// Função que alterna o estado de mudo do áudio
void HUD::toggleMusicMute() {
    isMuted = !isMuted;
    sound.setVolume(isMuted ? 0.f : volume);
}

// Função que alterna a reprodução de áudio
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

// Função para avançar a reprodução de áudio
void HUD::skipForward() {
    sf::Time currentOffset = sound.getPlayingOffset();
    sf::Time newOffset = currentOffset + sf::seconds(10.0f);
    sound.setPlayingOffset(newOffset);
}

// Função para retroceder a reprodução de áudio
void HUD::skipBackward() {
    sf::Time currentOffset = sound.getPlayingOffset();
    sf::Time newOffset = currentOffset - sf::seconds(10.0f);
    sound.setPlayingOffset(newOffset);
}

// Função para reproduzir a próxima faixa de áudio na lista
void HUD::playNextAudio() {
    if (!list_audio.empty()) {
        selectedIndex = (selectedIndex + 1) % list_audio.size();
        setSoundBuffer(list_audio[selectedIndex]);
        toggleMusicPlayback();
    }
}

// Função para reproduzir a faixa anterior de áudio na lista
void HUD::playPreviousAudio() {
    if (!list_audio.empty()) {
        selectedIndex =
            (selectedIndex - 1 + list_audio.size()) % list_audio.size();
        setSoundBuffer(list_audio[selectedIndex]);
        toggleMusicPlayback();
    }
}

// Função para resetar os controles de reprodução de áudio
void HUD::resetControls() {
    isPlaying = false;
    isMuted = false;
    volume = 10.f;
    sound.stop();
    sound.setVolume(volume);
}
