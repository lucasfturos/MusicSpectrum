#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <complex>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

const float pi = M_PI;
const int WIDTH = 1000;
const int HEIGHT = 600;
const size_t buffer_size = 1000;

template <typename T>
inline T clamp(T value, T min, T max) {
    return (value < min) ? min : (value > max) ? max : value;
}
