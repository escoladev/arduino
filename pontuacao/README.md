# Pontuação - Arduino

Usando Python e comunicação por voz para ativar/controlar os LEDs
no Arduino (com emissão de som através de um alto-falante/buzzer).

### Vídeo

<a href="http://www.youtube.com/watch?feature=player_embedded&v=VU8MLpR6j
" target="_blank"><img src="http://img.youtube.com/vi/VU8MLpR6j/0.jpg" 
alt="IMAGE ALT TEXT HERE" width="540" height="480" border="10" /></a>

https://www.youtube.com/watch?v=VU8MLpR6j-s&feature=youtu.be
## Requirements

- [Python 3.5 >](https://www.python.org/downloads/)

- [Arduino com o firmware do StandardFirmata](https://github.com/MrYsLab/pymata-aio/wiki/Uploading-StandardFirmata-To-Arduino) 

- [Arduino com o firmware FirmataPlus](https://github.com/MrYsLab/pymata-aio/wiki/Uploading-FirmataPlus-to-Arduino)

- [Speech Recognition (Python)](https://pypi.org/project/SpeechRecognition/)


## Material

- Protoboard

- Jumpers

- Buzzer/Alto-falante

- 6x LEDs vermelhos, 2x LEDs verdes, 1x LED Azul.

- 9 resistores de 330 ohm

- Arduino UNO.

## Esquema

Veja imagem abaixo:

<img src="https://raw.githubusercontent.com/jhoonb/arduino-projetos/master/pontuacao/esquema_pontuacao.png" 
height="430" width="519">

## Descrição

Na protoboard: no Centro, um LED que indica que está sendo executado o programa;

lado esquerdo (jogador 1) e direito (jogador 2)


lado esquerdo:

- 3 LEDs vermelhos e 1 verde

do lado direito:

- 3 LEDs vermelhos e 1 verde

cada ponto para o jogador representa 1 LED vermelho aceso.

Quem completar os três LEDs acesos, acende por fim
o LED verde, sinalizando que o jogador venceu.

O ínicio e pontuação é feita através de comando de voz
utilizando o Python e a biblioteca de reconhecimento de voz (Google)

É emitido som através do alto-falante, indicando a vitória.


**PORTAS DIGITAIS**

lado esquerdo - jogador 1

- LEDs vermelhos: 2, 3, 4

- LED verde: 5

**PORTAS DIGITAIS**

lado direito - jogador 2

- LEDs vermelhos: 8, 9, 10
- LED verde: 11

**LED CENTRO** (programa executando): 7

**Alto-falante/Buzzer:** 12




--

_Jhonathan P. Banczek
2019_

[@jhoonb](https://github.com/jhoonb)





