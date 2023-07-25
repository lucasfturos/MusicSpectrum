#include "spectrum.hpp"

void Spectrum::optionsPlot(int opc, std::vector<std::complex<float>> spectrum,
                           std::size_t fft_size) {
    switch (opc) {
    case 1:
        fft_ptr->fft(sample_buffer, 1, spectrum, fft_size);
        viewFormWaveFFT(spectrum);
        break;
    case 2:
        viewFormWave();
        break;
    case 3:
        fft_ptr->fft(sample_buffer, 1, spectrum, fft_size);
        viewFormWaveRectFFT(spectrum);
        break;
    case 4:
        viewFormWaveRect();
        break;
    default:
        break;
    }
}

void Spectrum::optionKeyboard(sf::Event &event) {
    event.key.code == sf::Keyboard::Space ? toggleMusicPlayback() : (void(0));

    event.key.code == sf::Keyboard::Q ? window->close() : (void(0));

    event.key.code == sf::Keyboard::Enter ? sound.stop() : (void(0));

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

void Spectrum::toggleMusicPlayback() {
    if (isPlaying) {
        sound.pause();
        isPlaying = false;
    } else {
        sound.play();
        sound.setVolume(volume);
        isPlaying = true;
    }
}

void Spectrum::monoSample() {
    if (sound_buffer.getChannelCount() == 2) {
        const sf::Int16 *samples = sound_buffer.getSamples();
        sample_buffer.reserve(buffer_size);
        for (std::size_t i = 0; i < buffer_size; ++i) {
            sf::Int16 mono_sample = static_cast<sf::Int16>(
                (samples[i * 2] + samples[i * 2 + 1]) / 2);
            sample_buffer.push_back(mono_sample);
        }
    }
}

void Spectrum::getSampleBuffer() {
    std::size_t sample_count = sound.getBuffer()->getSampleCount();
    std::size_t buffer_start = sound.getPlayingOffset().asSeconds() *
                               sound.getBuffer()->getSampleRate();
    std::size_t buffer_end = buffer_start + buffer_size;

    if (buffer_end >= sample_count) {
        buffer_end = sample_count;
    }

    const sf::Int16 *samples = sound.getBuffer()->getSamples();
    for (std::size_t j = 0; j < buffer_size; ++j) {
        if (buffer_start + j < buffer_end) {
            sample_buffer[j] = (samples[buffer_start + j * 2] +
                                samples[buffer_start + j * 2 + 1]) /
                               2;
        } else {
            sample_buffer[j] = 0;
        }
    }
}
void Spectrum::viewFormWave() {
    sf::VertexArray waveform(sf::LineStrip, buffer_size);
    float offsetY = HEIGHT / 2.f;

    for (std::size_t i = 0; i < buffer_size; ++i) {
        sf::Int16 sample_value = sample_buffer[i];
        float normalized_value = static_cast<float>(sample_value) / 32767.f;
        waveform[i].position = sf::Vector2f(
            static_cast<float>(i), normalized_value * offsetY + offsetY);
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
    }

    window->clear();
    window->draw(waveform);
    window->display();
}

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

void Spectrum::run(int opc) {
    opc == 0 ? throw std::invalid_argument("Opção de gráfico inválida!") : 0;

    window->setPosition(
        sf::Vector2i(desktop->width / 2.f - window->getSize().x / 2.f,
                     desktop->height / 2.f - window->getSize().y / 2.f));
    window->setFramerateLimit(60);

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            } else if (event.type == sf::Event::KeyPressed) {
                optionKeyboard(event);
            }
        }

        monoSample();
        std::vector<std::complex<float>> spectrum;
        if (sound.getStatus() == sf::SoundSource::Playing) {
            getSampleBuffer();

            std::size_t fft_size = 1;
            while (fft_size < buffer_size) {
                fft_size *= 2;
            }

            spectrum.resize(fft_size, 0);
            optionsPlot(opc, spectrum, fft_size);
        }

        sf::sleep(sf::milliseconds(10));
    }
}
