#include "hud.hpp"

/*!
 * Trata os eventos de entrada da janela SFML.
 *
 * Esta função trata os eventos de teclado da janela SFML, respondendo a
 * diferentes teclas para controlar a reprodução de áudio, ajustar o volume,
 * pular faixas e fechar a janela.
 *
 * `event`: Referência ao objeto sf::Event que contém informações
 * sobre o evento.
 */
void HUD::handleEvents(sf::Event &event) {
    switch (event.key.code) {
    case sf::Keyboard::Space:
        toggleMusicPlayback();
        break;
    case sf::Keyboard::M:
        toggleMusicMute();
        break;
    case sf::Keyboard::Escape:
        window->close();
        break;
    case sf::Keyboard::Left:
        skipBackward();
        break;
    case sf::Keyboard::Right:
        skipForward();
        break;
    case sf::Keyboard::Period:
        playNextAudio();
        break;
    case sf::Keyboard::Comma:
        playPreviousAudio();
        break;
    case sf::Keyboard::Enter: {
        sound.stop();
        isPlaying = false;
        break;
    }
    case sf::Keyboard::Up: {
        volume += 10.f;
        volume > 100.f ? volume = 100.f : 0;
        sound.setVolume(volume);
        break;
    }
    case sf::Keyboard::Down: {
        volume -= 10.f;
        volume < .0f ? volume = 0.f : 0;
        sound.setVolume(volume);
        break;
    }
    default:
        break;
    }
}

/*! Função que alterna o estado de mudo do áudio */
void HUD::toggleMusicMute() {
    isMuted = !isMuted;
    sound.setVolume(isMuted ? 0.f : volume);
}

/*! Função que alterna a reprodução de áudio */
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

/*! Função para avançar a reprodução de áudio */
void HUD::skipForward() {
    sf::Time currentOffset = sound.getPlayingOffset();
    sf::Time newOffset = currentOffset + sf::seconds(10.0f);
    sound.setPlayingOffset(newOffset);
}

/*! Função para retroceder a reprodução de áudio */
void HUD::skipBackward() {
    sf::Time currentOffset = sound.getPlayingOffset();
    sf::Time newOffset = currentOffset - sf::seconds(10.0f);
    sound.setPlayingOffset(newOffset);
}

/*! Função para reproduzir a próxima faixa de áudio na lista */
void HUD::playNextAudio() {
    if (!list_audio.empty()) {
        selectedIndex = (selectedIndex + 1) % list_audio.size();
        setSoundBuffer(list_audio[selectedIndex]);
        toggleMusicPlayback();
    }
}

/*! Função para reproduzir a faixa anterior de áudio na lista */
void HUD::playPreviousAudio() {
    if (!list_audio.empty()) {
        selectedIndex =
            (selectedIndex - 1 + list_audio.size()) % list_audio.size();
        setSoundBuffer(list_audio[selectedIndex]);
        toggleMusicPlayback();
    }
}

/*! Função para resetar os controles de reprodução de áudio */
void HUD::resetControls() {
    isPlaying = false;
    isMuted = false;
    volume = 10.f;
    sound.stop();
    sound.setVolume(volume);
}
