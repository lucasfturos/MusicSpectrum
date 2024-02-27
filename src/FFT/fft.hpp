#pragma once

#include <cmath>
#include <complex>
#include <cstdint>
#include <vector>

// Constantes
const float pi = M_PI;
using namespace std::complex_literals;
using Float_Complex = std::complex<float>;

/*
 * Classe template para realizar FFT em dados unidimensionais.
 * Esta classe implementa a Transformada de Fourier Rápida (FFT) para calcular
 * a transformada discreta de Fourier de um sinal unidimensional.
 * Suporta diferentes tipos de dados, como `int`, `short`, `uint8_t`,
 * `uint16_t`, etc.
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
             std::vector<std::complex<float>> &out, std::size_t n);

  public:
    /*
     * Realiza a análise de espectro dos dados de entrada usando a FFT.
     * Calcula o espectro considerando diferentes frequências dentro do
     * intervalo de frequências de interesse e armazena o resultado no vetor de
     * números complexos `out`. Antes de calcular a FFT, é aplicada uma janela
     * aos dados de entrada para reduzir o vazamento espectral. O resultado é
     * normalizado dividindo pelo valor máximo de amplitude encontrado durante
     * a análise de frequência.
     * @param in Referência ao vetor de dados de entrada.
     * @param stride O passo entre os elementos do vetor de entrada.
     * @param out Referência ao vetor de números complexos para armazenar o
     * espectro calculado.
     * @param n Tamanho do vetor de dados de entrada e saída.
     */
    void fftAnalyze(std::vector<T> &in, std::size_t stride,
                    std::vector<std::complex<float>> &out, std::size_t n);
};

// Instanciações da classe para tipos de dados suportados
template class FFT<int>;
template class FFT<short>;
template class FFT<std::uint8_t>;
template class FFT<std::uint16_t>;
