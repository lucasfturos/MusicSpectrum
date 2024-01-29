#include "spectrum3D.hpp"

void Spectrum3D::handleMouse() {
    static sf::Vector2i prev_pos;
    static bool first_click = true;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        sf::Vector2i curr_pos = sf::Mouse::getPosition();
        if (first_click) {
            prev_pos = curr_pos;
            first_click = false;
        } else {
            sf::Vector2i delta = curr_pos - prev_pos;
            float angle = atan2(delta.y, delta.x);

            view_mat = glm::rotate(view_mat, glm::radians(angle),
                                   glm::vec3(1.0f, 0.0f, 0.0f));
            prev_pos = curr_pos;
        }
    } else {
        first_click = true;
    }
}
