#pragma once

#include <cmath>
#include <complex>
#include <cstdint>
#include <vector>

// Constantes
const float pi = M_PI;
using namespace std::complex_literals;
using Float_Complex = std::complex<float>;

/*!
 * Classe template para realizar FFT em dados unidimensionais.
 *
 * Esta classe implementa a Transformada de Fourier Rápida (FFT) para calcular
 * a transformada discreta de Fourier de um sinal unidimensional. Esta
 * implementação de FFT aplica o algoritmo de Cooley-Tukey. Suporta diferentes
 * tipos de dados, como `int`, `short`, `uint8_t`, `uint16_t`, etc.
 */
template <class T> class FFT {
  private:
    inline float amp(Float_Complex z);

    std::size_t bitReverse(std::size_t k, std::size_t n);

    void applyHannWindow(std::vector<T> &in, std::size_t n);
    void applyHammingWindow(std::vector<T> &in, std::size_t n);
    void applyBlackmanWindow(std::vector<T> &in, std::size_t n);
    void applyFlattopWindow(std::vector<T> &in, std::size_t n);

    void fft(std::vector<T> &in, std::size_t stride,
             std::vector<Float_Complex> &out, std::size_t n);

  public:
    void fftAnalyze(std::vector<T> &in, std::size_t stride,
                    std::vector<Float_Complex> &out, std::size_t n);
};

// Instanciações da classe para tipos de dados suportados
template class FFT<int>;
template class FFT<short>;
template class FFT<std::uint8_t>;
template class FFT<std::uint16_t>;
