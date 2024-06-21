# Music Spectrum

Visualizador de espectro de áudio com transformada de Fourier rápida (FFT) e fórmula de Euler

## Descrição

Music Spectrum é um aplicativo que permite visualizar o espectro de frequência de arquivos de áudio em tempo real. O programa utiliza a transformada de Fourier rápida (FFT) para calcular o espectro de frequência e a fórmula de Euler para gerar visualizações vibrantes e interativas.

## Funcionalidades

-   Suporte para arquivos WAV e FLAC
-   Vários tipos de visualização de espectro:
    -   Senoidal com FFT
    -   Senoidal puro
    -   Espectro com FFT
    -   Espectro puro
    -   Senóide 3D com FFT
    -   Senóide 3D puro
-   Controles de reprodução
-   HUD do player com ImGui

## Screenshot

Algumas fotos do ambiente do programa.

### Tela do programa

<div style="width:70%;">

![](/assets/img/Screenshot/WindowSoftware.png)

</div>

### Tipos de visualização

**Senoidal com FFT**

<div style="width:70%;">

![](/assets/img/Screenshot/SineWaveFFT.png)

</div>

**Senoidal puro**

<div style="width:70%;">

![](/assets/img/Screenshot/SineWaveNoFFT.png)

</div>

**Espectro com FFT**

<div style="width:70%;">

![](/assets/img/Screenshot/SpectrumFFT.png)

</div>

**Espectro puro**

<div style="width:70%;">

![](/assets/img/Screenshot/SpectrumNoFFT.png)

</div>

**Senoide 3D com FFT**

<div style="width:70%;">

![](/assets/img/Screenshot/WaveFFT3D.gif)

</div>

**Senoide 3D Puro**

<div style="width:70%;">

![](/assets/img/Screenshot/WaveNoFFT3D.gif)

</div>

## Instalação e Execução

Detalhes logo abaixo:

### Requisitos

-   CMake
-   GCC/G++
-   Make
-   SFML
-   OpenGL
-   GLEW
-   GLM

### Instruções:

1. Clone o repositório:

```
git clone https://github.com/lucasfturos/MusicSpectrum.git && cd MusicSpectrum
```

2. Crie a pasta build:

```
mkdir build && cd build
```

3. Compile o programa:

```
cmake .. && make -j4
```

4. Execute o programa:

```
./src/MusicSpectrum
```

## Teclas

Teclas de funções do programa:

-   Use <kbd>space</kbd> para dar Play/Pause no áudio
-   Use <kbd>↵</kbd> para dar Stop no áudio
-   Use <kbd>M</kbd> para dar Mute no áudio
-   Use <kbd>↑</kbd> ou <kbd>↓</kbd> para Aumentar ou Diminuir o volume
-   Use <kbd>←</kbd> ou <kbd>→</kbd> para Avançar ou Retroceder a música
-   Use <kbd>,</kbd> ou <kbd>.</kbd> para Voltar ou pular para a Próxima música
-   Use <kbd>Esc</kbd> para Sair do programa.

## Créditos

Créditos de Bibliotecas e Icones usados no programa:

1. [SFML](https://www.sfml-dev.org/index.php)
2. [Dear ImGUI](https://github.com/ocornut/imgui)
3. [ImGUI-SFML](https://github.com/SFML/imgui-sfml)
4. [ImGuiFileDialog](https://github.com/aiekick/ImGuiFileDialog)
5. [FlatIcon](https://www.flaticon.com/)
6. [SVG Repo](https://www.svgrepo.com/)

## Documentação

A documentação do projeto pode ser acessada através do link disponível na seção 'About' do repositório.

## Referências

1. As coordenadas paramétricas da fita de Möbius: [Möbius strip - Sweeping a line segment](https://en.wikipedia.org/wiki/M%C3%B6bius_strip#Sweeping_a_line_segment)
2. Video do Tsoding Daily: [Music Visualizer (Fast Fourier Transform)](https://youtu.be/Xdbk1Pr5WXU)
3. Tutorial para criar uma docs: [CMake-Episode 026: Generating the documentation with Doxygen: doxygen_add_doc | CMake Starts Here](https://youtu.be/_IJZqf_kJ8A?si=B5-FVa62y-6MhmDS)
4. Repositório com configurações do Doxygen: [SCINE: Common CMake Files](https://github.com/qcscine/cmake)

## License

Este projeto está licenciado sob a licença MIT. Consulte o arquivo LICENSE para mais informações.
