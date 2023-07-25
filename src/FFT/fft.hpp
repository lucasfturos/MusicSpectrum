#pragma once

#include "../music_espectro.hpp"

using namespace std::complex_literals;

class FFT {
  private:
    std::size_t bitReverse(std::size_t k, std::size_t n);

  public:
    void fft(std::vector<sf::Int16> &in, size_t stride,
                    std::vector<std::complex<float>> &out, size_t n);
};
