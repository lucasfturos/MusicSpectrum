#pragma once

#include <chrono>
#include <thread>

/*!
 * Classe simples para medir tempo decorrido.
 *
 * A classe `Timer` fornece métodos para iniciar, resetar e obter o tempo
 * decorrido desde o início ou último reset.
 */
class Timer {
  public:
    Timer();
    ~Timer();
    void reset();
    float elapsed() const;

  private:
    typedef std::chrono::high_resolution_clock clock_;
    typedef std::chrono::duration<float, std::ratio<1>> second_;
    std::chrono::time_point<clock_> beg_;
};