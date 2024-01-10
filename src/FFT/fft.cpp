#include "fft.hpp"

// Função para calcular a amplitude de um número complexo
template <class T> inline float FFT<T>::amp(Float_Complex z) {
    float a = z.real();
    float b = z.imag();
    return sqrtf(a * a + b * b);
}

template <class T>
std::size_t FFT<T>::bitReverse(std::size_t k, std::size_t n) {
    std::size_t reversed = 0;
    for (std::size_t i = 0; i < n; i++) {
        reversed = (reversed << 1) | (k & 1);
        k >>= 1;
    }
    return reversed;
}

template <class T>
void FFT<T>::applyHannWindow(std::vector<T> &in, std::size_t n) {
    for (std::size_t i = 0; i < n; ++i) {
        float t = static_cast<float>(i) / (n - 1);
        float hann = 0.5 - 0.5 * std::cos(2 * M_PI * t);
        in[i] *= hann;
    }
}

template <class T>
void FFT<T>::fftAnalyze(std::vector<T> &in, std::size_t stride,
                        std::vector<std::complex<float>> &out, std::size_t n) {
    applyHannWindow(in, n);

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

template <class T>
void FFT<T>::fft(std::vector<T> &in, std::size_t stride,
                 std::vector<std::complex<float>> &out, std::size_t n) {
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
