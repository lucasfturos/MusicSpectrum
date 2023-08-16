# Music Spectrum

Visualizador de espectro de audio. Aplicação da transformada de Fourier FFT em conjunto com a fórmula de Euler

Suporta audios no formato WAV, OGG/Vorbis e FLAC.

Desenvolvido em C++ e SFML.

### Tipos de visualização

**Senoidal com FFT**

<img src="https://github.com/lucasfturos/MusicSpectrum/blob/main/img/SineWaveFFT.png" width="350" />

**Senoidal puro**

<img src="https://github.com/lucasfturos/MusicSpectrum/blob/main/img/SineWaveNoFFT.png" width="350" />

**Espectro com FFT**

<img src="https://github.com/lucasfturos/MusicSpectrum/blob/main/img/SpectrumFFT.png" width="350" />

**Espectro puro**

<img src="https://github.com/lucasfturos/MusicSpectrum/blob/main/img/SpectrumFFT.png" width="350" />

## Instalação e como usar

Precisa do cmake, gcc, g++, make e a lib do SFML. Após instalar é só seguir os seguintes passos:

```
git clone https://github.com/lucasfturos/MusicSpectrum.git && cd MusicSpectrum
mkdir assets
mkdir build && build
```
Coloque as músicas antes de executar os próximos comandos.

Após baixar, entrar na pasta, criar e entrar a pasta build, é só compilar:
```
cmake .. && make
```

Para usar coloque um audio na pasta assets e execute como no exemplo abaixo:
```
./MusicSpectrum Espectro FFT assets/nome_audio.wav
```

## Créditos

[SFML](https://www.sfml-dev.org/index.php)

## Referências

Video do Tsoding Daily: [Music Visualizer (Fast Fourier Transform)](https://youtu.be/Xdbk1Pr5WXU)
