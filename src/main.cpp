#include "Render/render.hpp"

int main(void) {
    try {
        auto render = std::make_shared<Render>();
        render->run();
    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
