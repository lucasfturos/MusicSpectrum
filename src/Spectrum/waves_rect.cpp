#include "spectrum.hpp"

void Spectrum::viewFormWaveRect() {
    window->clear();

    float rect_width = 3.0f;
    float rect_spacing = 1;
    float offsetY = HEIGHT / 2.f;

    for (std::size_t i = 0; i < buffer_size - 1; i += 3) {
        sf::Int16 sample_value = sample_buffer[i];
        float normalized_value = static_cast<float>(sample_value) / 32767.f;

        float rect_height = normalized_value * 150;

        float t = static_cast<float>(i * 4) / buffer_size;
        int r = start_color.r * (1 - t) + end_color.r * t;
        int g = start_color.g * (1 - t) + end_color.g * t;
        int b = start_color.b * (1 - t) + end_color.b * t;

        sf::Color alternate_color(static_cast<sf::Uint8>(clamp(r, 0, 255)),
                                  static_cast<sf::Uint8>(clamp(g, 0, 255)),
                                  static_cast<sf::Uint8>(clamp(b, 0, 255)));

        sf::RectangleShape rectangle(sf::Vector2f(rect_width, rect_height));
        rectangle.setFillColor(alternate_color);

        rectangle.setPosition(static_cast<float>(i) *
                                  (rect_width + rect_spacing),
                              offsetY - rect_height);
        window->draw(rectangle);
    }

    window->display();
}

void Spectrum::viewFormWaveRectFFT(std::vector<std::complex<float>> &spectrum) {
    window->clear();

    float rect_width = 3.f;
    float centerY = HEIGHT - 10.f;

    for (std::size_t j = 0; j < buffer_size - 1; j += 5) {
        float amplitude = std::abs(sample_buffer[j]) / 32767.f;
        float rect_height = amplitude * HEIGHT / 2.f;

        sf::RectangleShape rectangle(sf::Vector2f(rect_width, rect_height));

        float t = static_cast<float>(j * 4) / buffer_size;
        int r = start_color.r * (1 - t) + end_color.r * t;
        int g = start_color.g * (1 - t) + end_color.g * t;
        int b = start_color.b * (1 - t) + end_color.b * t;

        sf::Color alternate_color(static_cast<sf::Uint8>(clamp(r, 0, 255)),
                                  static_cast<sf::Uint8>(clamp(g, 0, 255)),
                                  static_cast<sf::Uint8>(clamp(b, 0, 255)));

        rectangle.setFillColor(alternate_color);

        rectangle.setPosition(static_cast<float>(j) * rect_width + rect_width,
                              centerY - rect_height);

        window->draw(rectangle);
    }
    window->display();
}
