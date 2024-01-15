#include "spectrum.hpp"

Spectrum::Spectrum() {
    window = std::make_shared<sf::RenderWindow>(
        sf::VideoMode(WIDTH, HEIGHT), "Music Spectrum",
        sf::Style::Titlebar | sf::Style::Close);
    desktop = std::make_shared<sf::VideoMode>(sf::VideoMode::getDesktopMode());
    window->setPosition(
        sf::Vector2i(desktop->width / 2.f - window->getSize().x / 2.f,
                     desktop->height / 2.f - window->getSize().y / 2.f));

    hud_ptr = std::make_shared<HUD>(window);
    fft_ptr = std::make_shared<FFT<sf::Int16>>();
}

void Spectrum::handlePlot(std::vector<std::complex<float>> spectrum,
                          std::size_t fft_size) {
    switch (hud_ptr->option) {
    case 1:
        fft_ptr->fftAnalyze(hud_ptr->sample_buffer, 1, spectrum, fft_size);
        viewFormWaveFFT();
        break;
    case 2:
        viewFormWave();
        break;
    case 3:
        fft_ptr->fftAnalyze(hud_ptr->sample_buffer, 1, spectrum, fft_size);
        viewFormWaveRectFFT();
        break;
    case 4:
        viewFormWaveRect();
        break;
    default:
        break;
    }
}

void Spectrum::run() {
    window->setVerticalSyncEnabled(true);
    window->setFramerateLimit(60);

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed) {
                window->close();
            } else if (event.type == sf::Event::KeyPressed) {
                hud_ptr->handleEvents(event);
            }
        }

        ImGui::SFML::Update(*window, clock.restart());

        window->clear();

        hud_ptr->run();

        monoSample();
        std::vector<std::complex<float>> spectrum;

        if (hud_ptr->sound.getStatus() == sf::SoundSource::Playing) {
            getSampleBuffer();

            std::size_t fft_size = 1;
            while (fft_size < buffer_size) {
                fft_size *= 2;
            }

            spectrum.resize(fft_size, 0);

            handlePlot(spectrum, fft_size);
        }
        sf::sleep(sf::milliseconds(10));

        window->display();
    }
}
