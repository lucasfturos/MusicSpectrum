#include "spectrum.hpp"

void Spectrum::viewFormWave() {
    sf::VertexArray waveform(sf::LineStrip, buffer_size);
    float offsetY = HEIGHT / 2.f;

    for (std::size_t i = 0; i < buffer_size; ++i) {
        sf::Int16 sample_value = sample_buffer[i];
        float normalized_value = static_cast<float>(sample_value) / 32767.f;
        waveform[i].position = sf::Vector2f(
            static_cast<float>(i), normalized_value * offsetY + offsetY);

        float t = static_cast<float>(i) / buffer_size;
        sf::Color vertex_color(
            static_cast<sf::Uint8>(start_color.r * (1 - t) + end_color.r * t),
            static_cast<sf::Uint8>(start_color.g * (1 - t) + end_color.g * t),
            static_cast<sf::Uint8>(start_color.b * (1 - t) + end_color.b * t));

        waveform[i].color = vertex_color;
    }

    window->clear();
    window->draw(waveform);
    window->display();
}

void Spectrum::viewFormWaveFFT(
    const std::vector<std::complex<float>> &spectrum) {
    sf::VertexArray waveform(sf::LineStrip, buffer_size);

    for (std::size_t i = 0; i < buffer_size; ++i) {
        float amplitude = std::abs(sample_buffer[i]) / 32767.f;
        float offsetY = HEIGHT - 20;
        waveform[i].position =
            sf::Vector2f(static_cast<float>(i), offsetY + offsetY * -amplitude);

        float t = static_cast<float>(i) / buffer_size;
        sf::Color vertex_color(
            static_cast<sf::Uint8>(start_color.r * (1 - t) + end_color.r * t),
            static_cast<sf::Uint8>(start_color.g * (1 - t) + end_color.g * t),
            static_cast<sf::Uint8>(start_color.b * (1 - t) + end_color.b * t));

        waveform[i].color = vertex_color;
    }

    window->clear();
    window->draw(waveform);
    window->display();
}