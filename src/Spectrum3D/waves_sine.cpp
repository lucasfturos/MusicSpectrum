#include "spectrum3D.hpp"

void Spectrum3D::viewWaveform() {
    /*
    glm::mat4 mvp = proj_mat * view_mat;
    shader_ptr->bind();
    shader_ptr->setUniformMat4f("uMVP", mvp);
    renderer_ptr->draw(*vao_ptr, *indexbuffer_ptr, *shader_ptr);
    */
    std::cout << "Funcionando viewWaveform 3D\n";
}

void Spectrum3D::viewWaveformFFT() {
    std::cout << "Funcionando viewWaveformFFT 3D\n";
}
