#include "spectrum.hpp"

Spectrum::Spectrum(sf::Sound sound, sf::SoundBuffer sound_buffer,
                   std::vector<sf::Int16> sample_buffer)
    : sound(std::move(sound)), sound_buffer(std::move(sound_buffer)),
      sample_buffer(std::move(sample_buffer)) {
    window = std::make_shared<sf::RenderWindow>(
        sf::VideoMode(WIDTH, HEIGHT), "Music Spectrum",
        sf::Style::Titlebar | sf::Style::Close);
    desktop = std::make_shared<sf::VideoMode>(sf::VideoMode::getDesktopMode());

    fft_ptr = std::make_shared<FFT<sf::Int16>>();
    hud_ptr = std::make_shared<HUD>(window, sound);
}

void Spectrum::run(int opc) {
    opc == 0 ? throw std::invalid_argument("Opção de gráfico inválida!") : 0;

    window->setPosition(
        sf::Vector2i(desktop->width / 2.f - window->getSize().x / 2.f,
                     desktop->height / 2.f - window->getSize().y / 2.f));
    window->setFramerateLimit(60);
    window->setVerticalSyncEnabled(true);

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed) {
                window->close();
            } else if (event.type == sf::Event::KeyPressed) {
                handleEvents(event);
            }
        }

        hud_ptr->run();

        monoSample();
        std::vector<std::complex<float>> spectrum;
        if (sound.getStatus() == sf::SoundSource::Playing) {
            getSampleBuffer();

            std::size_t fft_size = 1;
            while (fft_size < buffer_size) {
                fft_size *= 2;
            }

            spectrum.resize(fft_size, 0);
            handlePlot(opc, spectrum, fft_size);
        }

        sf::sleep(sf::milliseconds(10));
    }
}
