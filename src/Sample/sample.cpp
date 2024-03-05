#include "sample.hpp"

/*
 * Construtor da classe Sample.
 *
 * Armazena o ponteiro compartilhado para a instância HUD.
 *
 * `hud`: Ponteiro compartilhado para a instância da classe HUD.
 */
Sample::Sample(std::shared_ptr<HUD> hud) : hud_ptr(hud) {}

/*
 * Converte amostras de áudio estéreo para mono e as armazena no
 * buffer de amostras do objeto HUD.
 *
 * O método verifica se o buffer de som da HUD possui dois canais (estéreo)
 * e, caso positivo, realiza a conversão para mono (média dos canais
 * esquerdo e direito) e armazena os valores no buffer de amostras.
 */
void Sample::monoSample() {
    if (hud_ptr->sound_buffer.getChannelCount() == 2) {
        const sf::Int16 *samples = hud_ptr->sound_buffer.getSamples();
        hud_ptr->sample_buffer.reserve(buffer_size);
        for (std::size_t i = 0; i < buffer_size; ++i) {
            sf::Int16 mono_sample =
                static_cast<sf::Int16>((samples[i * 2] + samples[i * 2 + 1]) / 2);
            hud_ptr->sample_buffer.push_back(mono_sample);
        }
    }
}

/*
 * Pega o buffer de amostras do objeto HUD, considerando a
 * posição de reprodução atual e o tamanho do buffer.
 *
 * O método calcula o índice inicial e final do buffer de amostras com base
 * na posição de reprodução do som e na taxa de amostragem do buffer de som.
 * Em seguida, copia os valores das amostras do buffer de som para o buffer
 * de amostras da HUD, considerando o tamanho do buffer e o índice final
 * calculado. Valores fora do intervalo válido são preenchidos com zeros.
 */
void Sample::getSampleBuffer() {
    std::size_t sample_count = hud_ptr->sound.getBuffer()->getSampleCount();
    std::size_t buffer_start =
        hud_ptr->sound.getPlayingOffset().asSeconds() * hud_ptr->sound.getBuffer()->getSampleRate();
    std::size_t buffer_end = buffer_start + buffer_size;

    if (buffer_end >= sample_count) {
        buffer_end = sample_count;
    }

    const sf::Int16 *samples = hud_ptr->sound.getBuffer()->getSamples();
    for (std::size_t j = 0; j < buffer_size; ++j) {
        if (buffer_start + j < buffer_end) {
            hud_ptr->sample_buffer[j] =
                (samples[buffer_start + j * 2] + samples[buffer_start + j * 2 + 1]) / 2;
        } else {
            hud_ptr->sample_buffer[j] = 0;
        }
    }
}
