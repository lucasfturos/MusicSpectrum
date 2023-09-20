#pragma once

#include "../music_espectro.hpp"

using namespace std::complex_literals;
using Float_Complex = std::complex<float>;

class FFT {
  private:
    std::size_t bitReverse(std::size_t k, std::size_t n);
    void applyHannWindow(std::vector<sf::Int16> &in, size_t n);
    void fft(std::vector<sf::Int16> &in, size_t stride,
             std::vector<std::complex<float>> &out, size_t n);
    inline float amp(Float_Complex z);

  public:
    void fftAnalyze(std::vector<sf::Int16> &in, size_t stride,
                    std::vector<std::complex<float>> &out, size_t n);
};

// Função para calcular a amplitude de um número complexo
inline float FFT::amp(Float_Complex z) {
    float a = z.real();
    float b = z.imag();
    return logf(a * a + b * b);
}
