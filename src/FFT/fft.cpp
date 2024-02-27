#include "fft.hpp"

// Função para calcular a amplitude de um número complexo
template <class T> inline float FFT<T>::amp(Float_Complex z) {
    /*
     * Calcula a amplitude (módulo) de um número complexo `z`.
     *
     * @param z Um número complexo do tipo `std::complex<float>`.
     * @return A amplitude (módulo) do número complexo `z`, calculada como a
     * raiz quadrada da soma dos quadrados das partes real e imaginária.
     */
    float a = z.real();
    float b = z.imag();
    return sqrtf(a * a + b * b);
}

// Função para reversão de bits
template <class T>
std::size_t FFT<T>::bitReverse(std::size_t k, std::size_t n) {
    /*
     * Realiza a reversão de bits de um índice `k` em um número
     * binário de `n` bits.
     *
     * @param k O índice a ser revertido.
     * @param n O número de bits do índice `k`.
     * @return O índice `k` com seus bits revertidos.
     */
    std::size_t reversed = 0;
    for (std::size_t i = 0; i < n; i++) {
        reversed = (reversed << 1) | (k & 1);
        k >>= 1;
    }
    return reversed;
}

// Funções para aplicar diferentes janelas

// Janela de Hann
template <class T>
void FFT<T>::applyHannWindow(std::vector<T> &in, std::size_t n) {
    /*
     * Aplica a janela de Hann aos dados de entrada `in` com tamanho `n`.
     *
     * @param in Uma referência a um vetor de dados de entrada do tipo `T`.
     * @param n O tamanho do vetor de dados de entrada.
     */
    for (std::size_t i = 0; i < n; ++i) {
        float t = static_cast<float>(i) / (n - 1);
        float hann = 0.5 - 0.5 * std::cos(2 * pi * t);
        in[i] *= hann;
    }
}

// Janela de Hamming
template <class T>
void FFT<T>::applyHammingWindow(std::vector<T> &in, std::size_t n) {
    /*
     * Aplica a janela de Hamming aos dados de entrada `in` com tamanho `n`.
     *
     * @param in Uma referência a um vetor de dados de entrada do tipo `T`.
     * @param n O tamanho do vetor de dados de entrada.
     */
    for (std::size_t i = 0; i < n; ++i) {
        float t = static_cast<float>(i) / (n - 1);
        float hamming = 0.54 - 0.46 * std::cos(2 * pi * t);
        in[i] *= hamming;
    }
}

// Janela de Blackman
template <class T>
void FFT<T>::applyBlackmanWindow(std::vector<T> &in, std::size_t n) {
    /*
     * Aplica a janela de Blackman aos dados de entrada `in` com tamanho `n`.
     *
     * @param in Uma referência a um vetor de dados de entrada do tipo `T`.
     * @param n O tamanho do vetor de dados de entrada.
     */
    for (std::size_t i = 0; i < n; ++i) {
        float t = static_cast<float>(i) / (n - 1);
        float blackman =
            0.42 + 0.5 * std::cos(2 * pi * t) + 0.8 * std::cos(4 * pi * t);
        in[i] *= blackman;
    }
}

// Janela de Flattop
template <class T>
void FFT<T>::applyFlattopWindow(std::vector<T> &in, std::size_t n) {
    /*
     * Aplica a janela de Flattop aos dados de entrada `in` com tamanho `n`.
     *
     * @param in Uma referência a um vetor de dados de entrada do tipo `T`.
     * @param n O tamanho do vetor de dados de entrada.
     */
    for (std::size_t i = 0; i < n; ++i) {
        float t = static_cast<float>(i) / (n - 1);
        float flattop =
            1 - 1.93 * std::cos(2 * pi * t) + 1.29 * std::cos(4 * pi * t) -
            0.388 * std::cos(6 * pi * t) + 0.032 * std::cos(8 * pi * t);
        in[i] *= flattop;
    }
}

// Função recursiva para realizar a FFT
template <class T>
void FFT<T>::fft(std::vector<T> &in, std::size_t stride,
                 std::vector<std::complex<float>> &out, std::size_t n) {
    /*
     * Realiza a Transformada Rápida de Fourier (FFT) nos dados de entrada.
     *
     * @param in Uma referência a um vetor de dados de entrada do tipo `T`.
     * @param stride O passo entre os elementos do vetor de entrada.
     * @param out Uma referência a um vetor de número complexo do tipo
     * `std::complex<float>` para armazenar a saída da FFT.
     * @param n O tamanho do vetor de dados de entrada e saída.
     */
    if (n == 1) {
        out[0] = in[0];
        return;
    }

    std::vector<T> in_reversed(n, 0);
    for (std::size_t k = 0; k < n; k++) {
        std::size_t rev_k = bitReverse(k, static_cast<std::size_t>(log2(n)));
        in_reversed[k] = in[rev_k * stride];
    }

    std::vector<std::complex<float>> out_reversed(n / 2, 0);
    fft(in_reversed, stride * 2, out_reversed, n / 2);

    for (std::size_t k = 0; k < n / 2; k++) {
        float t = static_cast<float>(k) / n;
        std::complex<float> v = exp(-2.f * 1if * pi * t) * out_reversed[k];
        std::complex<float> e = out_reversed[k];
        out[k] = e + v;
        out[k + n / 2] = e - v;
    }
}

// Função principal para análise de espectro
template <class T>
void FFT<T>::fftAnalyze(std::vector<T> &in, std::size_t stride,
                        std::vector<std::complex<float>> &out, std::size_t n) {
    /*
     * Realiza a análise do espectro dos dados de entrada usando a Transformada
     * Rápida de Fourier (FFT) e armazena o resultado em `out`.
     *
     * @param in Uma referência a um vetor de dados de entrada do tipo `T`.
     * @param stride O passo entre os elementos do vetor de entrada.
     * @param out Uma referência a um vetor de números complexos do tipo
     * `std::complex<float>` para armazenar o espectro calculado.
     * @param n O tamanho do vetor de dados de entrada e saída.
     */
    applyHammingWindow(in, n);
    // applyHannWindow(in, n);
    // applyBlackmanWindow(in, n);
    // applyFlattopWindow(in, n);

    std::vector<std::complex<float>> complex_output(n, 0.0f);

    fft(in, stride, complex_output, n);

    float step = 1.06;
    float lowf = 1.0f;
    std::size_t m = 0;
    float max_amp = 1.0f;

    for (float f = lowf; static_cast<std::size_t>(f) < n / 2;
         f = std::ceil(f * step)) {
        float f1 = std::ceil(f * step);
        float a = 0.0f;
        for (std::size_t q = static_cast<std::size_t>(f);
             q < n / 2 && q < static_cast<std::size_t>(f1); ++q) {
            float b = amp(complex_output[q]);
            if (b > a)
                a = b;
        }
        if (max_amp < a)
            max_amp = a;
        out[m++] = a;
    }

    for (std::size_t i = 0; i < n / 2; ++i) {
        out[i] /= max_amp;
    }
}
