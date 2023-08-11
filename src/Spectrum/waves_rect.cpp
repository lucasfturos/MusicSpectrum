#include "spectrum.hpp"

void Spectrum::viewFormWaveRect() {
    window->clear();

    float rect_width = 2.0f;
    float rect_spacing = rect_width;
    float offsetY = HEIGHT / 2.f;

    for (std::size_t i = 0; i < buffer_size; ++i) {
        sf::Int16 sample_value = sample_buffer[i];
        float normalized_value = static_cast<float>(sample_value) / 32767.f;

        float rect_height = normalized_value * 150;

        sf::RectangleShape rectangle(sf::Vector2f(rect_width, rect_height));
        rectangle.setFillColor(sf::Color::Blue);

        rectangle.setPosition(static_cast<float>(i) *
                                  (rect_width + rect_spacing),
                              offsetY - rect_height);
        window->draw(rectangle);
    }

    window->display();
}

void Spectrum::viewFormWaveRectFFT(std::vector<std::complex<float>> &spectrum) {
    window->clear();

    float rect_width = 2.f;
    float centerY = HEIGHT - 10.f;

    for (std::size_t j = 0; j < buffer_size - 1; ++j) {
        float amplitude = std::abs(sample_buffer[j]) / 32767.f;
        float rect_height = amplitude * HEIGHT / 2.f;

        sf::RectangleShape rectangle(sf::Vector2f(rect_width, rect_height));
        rectangle.setFillColor(sf::Color::Green);

        rectangle.setPosition(static_cast<float>(j) * rect_width * rect_width,
                              centerY - rect_height);

        window->draw(rectangle);
    }
    window->display();
}
