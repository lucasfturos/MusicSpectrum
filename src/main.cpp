#include "Spectrum/spectrum.hpp"

int main(void) {
    try {
        auto spectrum = std::make_shared<Spectrum>();
        spectrum->run();
    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
