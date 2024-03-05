#include "timer.hpp"

/*
 * `Construtor padrão.`
 *
 * Inicia o timer automaticamente no momento da construção.
 */
Timer::Timer() : beg_(clock_::now()) {}

/*
 * `Destrutor padrão.`
 *
 * Automaticamente reseta o timer para garantir que o objeto não mantenha
 * referências desnecessárias a dados após sua destruição.
 */
Timer::~Timer() { reset(); }

/*
 * Reinicia o timer, marcando o tempo atual como o novo ponto de
 * início para medição.
 */
void Timer::reset() { beg_ = clock_::now(); }

/**
 * Obtém o tempo decorrido desde o início do timer ou o último
 * reset, em segundos.
 *
 * `returno`: O tempo decorrido em segundos como um valor `float`.
 */
float Timer::elapsed() const {
    return std::chrono::duration_cast<second_>(clock_::now() - beg_).count();
}