#include "spectrum.hpp"

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
