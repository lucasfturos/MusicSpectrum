#include "spectrum.hpp"

void Spectrum::viewFormWaveRect() {
    float rect_width = 3.0f;
    float rect_spacing = 1.f;
    float offsetY = HEIGHT / 2.f;

    for (std::size_t i = 0; i < buffer_size - 1; i += 5) {
        sf::Int16 sample_value = hud_ptr->sample_buffer[i];
        float normalized_value = static_cast<float>(sample_value) / 32767.f;

        float rect_height = normalized_value * 150;

        float t = static_cast<float>(i * 4) / buffer_size;
        t = t * t * (3.0f - 2.0f * t);
        sf::Color vertex_color(
            static_cast<sf::Uint8>(start_color.r * (1 - t) + end_color.r * t),
            static_cast<sf::Uint8>(start_color.g * (1 - t) + end_color.g * t),
            static_cast<sf::Uint8>(start_color.b * (1 - t) + end_color.b * t));

        sf::RectangleShape rectangle(sf::Vector2f(rect_width, rect_height));
        rectangle.setFillColor(vertex_color);

        rectangle.setPosition(static_cast<float>(i) *
                                  (rect_width + rect_spacing),
                              offsetY - rect_height);
        window->draw(rectangle);
    }
}

void Spectrum::viewFormWaveRectFFT() {
    float rect_width = 3.f;
    float centerY = HEIGHT - 10.f;
    static std::vector<float> prev_amplitudes(buffer_size, 0.0f);

    for (std::size_t j = 0; j < buffer_size - 1; j += 6) {
        float amplitude = std::abs(hud_ptr->sample_buffer[j]) / 32767.f;
        float rect_height = amplitude * HEIGHT;

        sf::RectangleShape rectangle(sf::Vector2f(rect_width, rect_height));

        float t = static_cast<float>(j * 3) / buffer_size;
        t = t * t * (3.0f - 2.0f * t);
        sf::Color vertex_color(
            static_cast<sf::Uint8>(start_color.r * (1 - t) + end_color.r * t),
            static_cast<sf::Uint8>(start_color.g * (1 - t) + end_color.g * t),
            static_cast<sf::Uint8>(start_color.b * (1 - t) + end_color.b * t));

        rectangle.setFillColor(vertex_color);
        sf::Vector2f position(j * rect_width, centerY - rect_height);
        rectangle.setPosition(position);

        window->draw(rectangle);

        sf::RectangleShape gravity_rect(sf::Vector2f(10.f, 5.f));
        gravity_rect.setFillColor(vertex_color);
        sf::Vector2f rect_pos =
            sf::Vector2f(position.x + rect_width / 2 - 5.f, position.y);
        gravity_rect.setPosition(rect_pos);

        window->draw(gravity_rect);
    }
}
