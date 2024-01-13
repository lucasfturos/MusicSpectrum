#include "../HUD/hud.hpp"
#include "../Spectrum/spectrum.hpp"
#include "../util.hpp"

class Render {
  private:
    sf::Clock clock;
    std::shared_ptr<sf::VideoMode> desktop;
    std::shared_ptr<sf::RenderWindow> window;

    std::shared_ptr<HUD> hud_ptr;
    std::shared_ptr<Spectrum> spectrum_ptr;

    void toggleMusicPlayback();
    void handleEvents(sf::Event &event);

  public:
    void run();
    Render();
};
