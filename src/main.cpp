#include "Spectrum/spectrum.hpp"

sf::Sound sound;
sf::SoundBuffer sound_buffer;
std::vector<sf::Int16> sample_buffer;

struct Option {
    std::string waveform;
    std::string fft;
    std::string args;

    bool operator<(const Option &other) const {
        if (waveform != other.waveform)
            return waveform < other.waveform;
        if (fft != other.fft)
            return fft < other.fft;
        return args < other.args;
    }
};

int main(int argc, char *argv[]) {
    try {
        if (argc < 2) {
            throw std::invalid_argument(
                "Exemplo de entrada: Espectro NoFFT assets/nome_musica.wav");
        }

        std::map<Option, int> option_spectrum{
            {{"Senoide", "FFT", argv[3]}, 1},
            {{"Senoide", "NoFFT", argv[3]}, 2},
            {{"Espectro", "FFT", argv[3]}, 3},
            {{"Espectro", "NoFFT", argv[3]}, 4},
        };
        Option selected_option{argv[1], argv[2], argv[3]};
        int opc = option_spectrum[selected_option];

        sample_buffer.reserve(buffer_size);
        if (!sound_buffer.loadFromFile(selected_option.args)) {
            throw std::invalid_argument("Erro ao carregar a música!!");
        }
        sound.setBuffer(sound_buffer);

        auto spectrum =
            std::make_shared<Spectrum>(sound, sound_buffer, sample_buffer);

        spectrum->run(opc);
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
}
