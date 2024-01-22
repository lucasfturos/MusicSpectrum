#pragma once

#include <cmath>
#include <complex>
#include <cstdint>
#include <vector>

const float pi = M_PI;
using namespace std::complex_literals;
using Float_Complex = std::complex<float>;

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
    FFT<T>() = default;
    void fftAnalyze(std::vector<T> &in, std::size_t stride,
                    std::vector<std::complex<float>> &out, std::size_t n);
};

template class FFT<int>;
template class FFT<short>;
template class FFT<std::uint8_t>;
template class FFT<std::uint16_t>;
