#include "render.hpp"

void Render::handlePlot(std::vector<std::complex<float>> spectrum,
                        std::size_t fft_size) {
    switch (hud_ptr->option) {
    case 1:
        fft_ptr->fftAnalyze(hud_ptr->sample_buffer, 1, spectrum, fft_size);
        spectrum_ptr->viewWaveformFFT();
        break;
    case 2:
        spectrum_ptr->viewWaveform();
        break;
    case 3:
        fft_ptr->fftAnalyze(hud_ptr->sample_buffer, 1, spectrum, fft_size);
        spectrum_ptr->viewWaveformRectFFT();
        break;
    case 4:
        spectrum_ptr->viewWaveformRect();
        break;
    case 5:
        fft_ptr->fftAnalyze(hud_ptr->sample_buffer, 1, spectrum, fft_size);
        spectrum3D_ptr->viewWaveformFFT();
        break;
    case 6:
        spectrum3D_ptr->viewWaveform();
        break;
    default:
        break;
    }
}
