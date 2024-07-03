#include "spectrum.hpp"

//! Renderiza a forma de onda do sinal de áudio utilizando linhas.
void Spectrum::viewWaveform() {
    sf::VertexArray waveform(sf::LineStrip, buffer_size);
    float offsetY = HEIGHT / 2.f;

    for (std::size_t i = 0; i < buffer_size; ++i) {
        sf::Int16 sample_value = hud_ptr->sample_buffer[i];
        float normalized_value = static_cast<float>(sample_value) / 32767.f;
        waveform[i].position = sf::Vector2f(
            static_cast<float>(i), normalized_value * offsetY + offsetY);

        float milliseconds = timer_ptr->elapsed() / 1000;
        float interval = milliseconds / 80.0f;

        float t = interval + (static_cast<float>(i) / buffer_size);
        t = t - static_cast<int>(t);

        sf::Color vertex_color(
            static_cast<sf::Uint8>(start_color.r * (1 - t) + end_color.r * t),
            static_cast<sf::Uint8>(start_color.g * (1 - t) + end_color.g * t),
            static_cast<sf::Uint8>(start_color.b * (1 - t) + end_color.b * t));

        waveform[i].color = vertex_color;
    }

    window->draw(waveform);
}

//! Renderiza a FFT do sinal de áudio utilizando linhas.
void Spectrum::viewWaveformFFT() {
    sf::VertexArray waveform(sf::LineStrip, buffer_size);
    float centerY = HEIGHT - 10.f;

    for (std::size_t i = 0; i < buffer_size; ++i) {
        float amplitude = std::abs(hud_ptr->sample_buffer[i]) / 32767.f;
        float offsetY = amplitude * HEIGHT;
        waveform[i].position =
            sf::Vector2f(static_cast<float>(i), centerY - offsetY);

        float t = static_cast<float>(i) / buffer_size;
        sf::Color vertex_color(
            static_cast<sf::Uint8>(start_color.r * (1 - t) + end_color.r * t),
            static_cast<sf::Uint8>(start_color.g * (1 - t) + end_color.g * t),
            static_cast<sf::Uint8>(start_color.b * (1 - t) + end_color.b * t));

        waveform[i].color = vertex_color;
    }

    window->draw(waveform);
}
