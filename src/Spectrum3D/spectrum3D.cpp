#include "spectrum3D.hpp"
#include "../../external/imgui/imgui_impl_opengl3.h"

Spectrum3D::Spectrum3D(std::shared_ptr<sf::RenderWindow> win,
                       std::shared_ptr<HUD> hud,
                       std::shared_ptr<Spectrum> spectrum,
                       std::shared_ptr<FFT<sf::Int16>> fft)
    : window(win), hud_ptr(hud), spectrum_ptr(spectrum), fft_ptr(fft),
      proj_mat(
          glm::perspective(glm::radians(60.0f), 4.0f / 3.0f, 0.1f, 100.0f)),
      view_mat(glm::lookAt(glm::vec3(0.0f, 0.0f, 1.6f),
                           glm::vec3(0.0f, 0.1f, 0.0f),
                           glm::vec3(0.0f, 1.0f, 0.0f))) {
    glewExperimental = GL_TRUE;
    GLenum error = glewInit();
    if (error != GLEW_OK) {
        throw std::runtime_error(
            std::string("Error: ") +
            reinterpret_cast<const char *>(glewGetErrorString(error)));
    }

    std::cout << "GLEW version: " << glewGetString(GLEW_VERSION) << "\n";
    std::cout << "GL version: " << glGetString(GL_VERSION) << '\n';

    if (!window->setActive(true)) {
        throw std::runtime_error("Failed to set window to active");
    }

    ImGui_ImplOpenGL3_Init();
    renderer_ptr = std::make_unique<Renderer>();
    initOpenGL();
}

Spectrum3D::~Spectrum3D() {
    ImGui_ImplOpenGL3_Shutdown();
}

void Spectrum3D::run(
    std::function<void(std::vector<std::complex<float>>, std::size_t)>
        handlePlot) {
    spectrum_ptr->monoSample();
    std::vector<std::complex<float>> spectrum;

    if (hud_ptr->sound.getStatus() == sf::SoundSource::Playing) {
        spectrum_ptr->getSampleBuffer();

        std::size_t fft_size = 1;
        while (fft_size < buffer_size) {
            fft_size *= 2;
        }

        spectrum.resize(fft_size, 0);

        handlePlot(spectrum, fft_size);
    }
    shader_ptr->unbind();
}
