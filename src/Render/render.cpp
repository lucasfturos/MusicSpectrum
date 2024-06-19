#include "render.hpp"
#include "../../external/imgui/imgui_impl_opengl3.h"

/*!
 * Construtor da classe Render.
 *
 * Esta função inicializa os principais objetos usados pela classe Render:
 * - `window`: Janela principal da aplicação.
 * - `desktop`: Modo de exibição do desktop.
 * - `hud_ptr`: Ponteiro compartilhado para a instância da classe HUD.
 * - `fft_ptr`: Ponteiro compartilhado para a instância da classe FFT.
 * - `spectrum_ptr`: Ponteiro compartilhado para a instância da classe Spectrum.
 * - `spectrum3D_ptr`: Ponteiro compartilhado para a instância da classe
 * Spectrum3D.
 */
Render::Render()
    : window(std::make_shared<sf::RenderWindow>(
          sf::VideoMode(WIDTH, HEIGHT), "Music Spectrum",
          sf::Style::Titlebar | sf::Style::Close)),
      desktop(
          std::make_shared<sf::VideoMode>(sf::VideoMode::getDesktopMode())) {

    window->setPosition(
        sf::Vector2i(desktop->width / 2.f - window->getSize().x / 2.f,
                     desktop->height / 2.f - window->getSize().y / 2.f));

    hud_ptr = std::make_shared<HUD>(window);
    fft_ptr = std::make_shared<FFT<sf::Int16>>();
    spectrum_ptr = std::make_shared<Spectrum>(window, hud_ptr, fft_ptr);
    spectrum3D_ptr = std::make_shared<Spectrum3D>(window, hud_ptr, fft_ptr);
}

Render::~Render() { ImGui_ImplOpenGL3_Shutdown(); }

/*!
 * Ajuste da taxa de quadros.
 *
 * Esta função controla a taxa de quadros da aplicação para manter uma
 * renderização suave. Ela calcula o tempo decorrido desde o último frame e,
 * se for menor que a duração desejada, coloca a thread em espera por um
 * determinado tempo para garantir a taxa de quadros.
 *
 * `prev_time`: Referência para o tempo do frame anterior.
 */
void Render::frameRate(time_point<high_resolution_clock> &prev_time) {
    auto current_time = high_resolution_clock::now();
    auto elapsed_time =
        duration_cast<duration<double>>(current_time - prev_time);

    if (elapsed_time.count() < frame_duration) {
        auto sleep_duration =
            duration<double>(frame_duration - elapsed_time.count());
        std::this_thread::sleep_for(
            duration_cast<milliseconds>(sleep_duration));
    }

    prev_time = high_resolution_clock::now();
}

/*!
 * Loop principal da aplicação.
 *
 * Esta função é o loop principal da aplicação e é responsável por:
 * - Gerenciar eventos da janela e da HUD.
 * - Chamar os métodos `run` de HUD, Spectrum e Spectrum3D para realizar a
 *   atualização e renderização.
 * - Controlar a taxa de quadros da aplicação.
 */
void Render::run() {
    ImGui_ImplOpenGL3_Init();
    window->setVerticalSyncEnabled(true);
    auto prev_time = high_resolution_clock::now();

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            switch (event.type) {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::KeyPressed:
                hud_ptr->handleEvents(event);
                break;
            case sf::Event::MouseWheelMoved:
                spectrum3D_ptr->getWhellDelta(event.mouseWheel.delta);
                break;
            default:
                break;
            }
        }

        ImGui::SFML::Update(*window, clock.restart());

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        window->clear();

        ImGui_ImplOpenGL3_NewFrame();

        hud_ptr->run();
        window->pushGLStates();
        spectrum_ptr->run(std::bind(&Render::handlePlot, this,
                                    std::placeholders::_1,
                                    std::placeholders::_2));
        window->popGLStates();

        spectrum3D_ptr->run(std::bind(&Render::handlePlot, this,
                                      std::placeholders::_1,
                                      std::placeholders::_2));

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window->display();

        frameRate(prev_time);
    }
}
