# Music Spectrum

Visualizador de espectro de audio. Aplicação da transformada de Fourier FFT em conjunto com a fórmula de Euler

Suporta audios no formato WAV, OGG/Vorbis e FLAC.

Desenvolvido em C++ e SFML.

### Tipos de visualização


**Senoidal com FFT**

<p align="center">
<img src="https://github.com/lucasfturos/MusicSpectrum/blob/main/img/SineWaveFFT.png" width="70%" />
</p>

**Senoidal puro**

<p align="center">
<img src="https://github.com/lucasfturos/MusicSpectrum/blob/main/img/SineWaveNoFFT.png" width="70%" />
</p>

**Espectro com FFT**

<p align="center">
<img src="https://github.com/lucasfturos/MusicSpectrum/blob/main/img/SpectrumFFT.png" width="70%" />
</p>

**Espectro puro**

<p align="center">
<img src="https://github.com/lucasfturos/MusicSpectrum/blob/main/img/SpectrumNoFFT.png" width="70%" />
</p>

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

## Teclas

- Use <kbd>space</kbd> para dar Play/Pause no áudio
- Use <kbd>enter</kbd> para dar Stop no áudio
- Use <kbd>up</kbd> ou <kbd>down</kbd> para Aumentar ou Diminuir o volume
- Use <kbd>q</kbd> para Sair do programa.

## Créditos

[SFML](https://www.sfml-dev.org/index.php)

## Referências

Video do Tsoding Daily: [Music Visualizer (Fast Fourier Transform)](https://youtu.be/Xdbk1Pr5WXU)
