# Music Spectrum

Visualizador de espectro de audio. Aplicação da transformada de Fourier FFT em conjunto com a fórmula de Euler

Suporta audios no formato WAV e FLAC.

Desenvolvido em C++ com a biblioteca SFML.

## Screenshot

Algumas fotos do ambiente do programa.

<details><summary>Show</summary>

### Tela do programa

<p align="center">
<img src="/assets/img/Screenshot/WindowSoftware.png" width="70%" />
</p>

### Tipos de visualização


**Senoidal com FFT**

<p align="center">
<img src="/assets/img/Screenshot/SineWaveFFT.png" width="70%" />
</p>

**Senoidal puro**

<p align="center">
<img src="/assets/img/Screenshot/SineWaveNoFFT.png" width="70%" />
</p>

**Espectro com FFT**

<p align="center">
<img src="/assets/img/Screenshot/SpectrumFFT.png" width="70%" />
</p>

**Espectro puro**

<p align="center">
<img src="/assets/img/Screenshot/SpectrumNoFFT.png" width="70%" />
</p>

**Senoide 3D com FFT**
<p align="center">
<img src="/assets/img/Screenshot/WaveFFT3D.gif" width="70%" />
</p>

</details>

## Instalação e Execução 

Instalação, dependências e uso do programa:

<details><summary>Show</summary>

Para rodar o programa é necessário ter instalado o cmake, gcc, g++, make, a biblioteca do SFML e o OpenGL. Após instalar elas, é só seguir os seguintes passos:

```
git clone https://github.com/lucasfturos/MusicSpectrum.git && cd MusicSpectrum
mkdir assets
mkdir build && build
```

Após baixar, entrar na pasta raiz do projeto, criar e entrar na pasta build, é só compilar:
```
cmake .. && make -j4
```

Para usar execute como no exemplo abaixo:
```
./src/MusicSpectrum
```

</details>

## Teclas

Teclas de funções do programa:

<details><summary>Show</summary>

- Use <kbd>space</kbd> para dar Play/Pause no áudio
- Use <kbd>↵</kbd> para dar Stop no áudio
- Use <kbd>M</kbd> para dar Mute no áudio
- Use <kbd>↑</kbd> ou <kbd>↓</kbd> para Aumentar ou Diminuir o volume
- Use <kbd>←</kbd> ou <kbd>→</kbd> para Avançar ou Retroceder a música
- Use <kbd>,</kbd> ou <kbd>.</kbd> para Voltar ou pular para a Próxima música
- Use <kbd>Q</kbd> para Sair do programa.

</details>

## Créditos

Créditos de Bibliotecas e Icones usados no programa:

<details><summary>Show</summary>

[SFML](https://www.sfml-dev.org/index.php)

[Dear ImGUI](https://github.com/ocornut/imgui)

[ImGUI-SFML](https://github.com/SFML/imgui-sfml)

[ImGuiFileDialog](https://github.com/aiekick/ImGuiFileDialog)

[FlatIcon - Icon Play](https://www.flaticon.com/br/icones-gratis/botao-play)

[FlatIcon - Icon Pause](https://www.flaticon.com/br/icones-gratis/pausa)

[FlatIcon - Icon Stop](https://www.flaticon.com/br/icones-gratis/pare)

[FlatIcon - Icon Volume](https://www.flaticon.com/br/icones-gratis/volume)

[FlatIcon - Icon Mute](https://www.flaticon.com/br/icones-gratis/silencio)

[FlatIcon - Icon Foward](https://www.flaticon.com/br/icones-gratis/jogar)

[FlatIcon - Icon Backward](https://www.flaticon.com/br/icones-gratis/rebobinar)

[FlatIcon - Icon Next](https://www.flaticon.com/br/icones-gratis/proximo)

[FlatIcon - Icon Back](https://www.flaticon.com/br/icones-gratis/rebobinar)

</details>

## Referências

Video do Tsoding Daily: [Music Visualizer (Fast Fourier Transform)](https://youtu.be/Xdbk1Pr5WXU)
