#include "sample.hpp"

Sample::Sample(std::shared_ptr<HUD> hud) : hud_ptr(hud) {}

void Sample::monoSample() {
    if (hud_ptr->sound_buffer.getChannelCount() == 2) {
        const sf::Int16 *samples = hud_ptr->sound_buffer.getSamples();
        hud_ptr->sample_buffer.reserve(buffer_size);
        for (std::size_t i = 0; i < buffer_size; ++i) {
            sf::Int16 mono_sample = static_cast<sf::Int16>(
                (samples[i * 2] + samples[i * 2 + 1]) / 2);
            hud_ptr->sample_buffer.push_back(mono_sample);
        }
    }
}

void Sample::getSampleBuffer() {
    std::size_t sample_count = hud_ptr->sound.getBuffer()->getSampleCount();
    std::size_t buffer_start = hud_ptr->sound.getPlayingOffset().asSeconds() *
                               hud_ptr->sound.getBuffer()->getSampleRate();
    std::size_t buffer_end = buffer_start + buffer_size;

    if (buffer_end >= sample_count) {
        buffer_end = sample_count;
    }

    const sf::Int16 *samples = hud_ptr->sound.getBuffer()->getSamples();
    for (std::size_t j = 0; j < buffer_size; ++j) {
        if (buffer_start + j < buffer_end) {
            hud_ptr->sample_buffer[j] = (samples[buffer_start + j * 2] +
                                         samples[buffer_start + j * 2 + 1]) /
                                        2;
        } else {
            hud_ptr->sample_buffer[j] = 0;
        }
    }
}
