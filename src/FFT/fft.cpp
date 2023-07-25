#include "fft.hpp"

std::size_t FFT::bitReverse(std::size_t k, std::size_t n) {
    std::size_t reversed = 0;
    for (std::size_t i = 0; i < n; i++) {
        reversed = (reversed << 1) | (k & 1);
        k >>= 1;
    }
    return reversed;
}

void FFT::fft(std::vector<sf::Int16> &in, size_t stride,
              std::vector<std::complex<float>> &out, size_t n) {
    if (n == 1) {
        out[0] = in[0];
        return;
    }

    std::vector<sf::Int16> in_reversed(n, 0);
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
