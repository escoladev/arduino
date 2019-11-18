## LED simples usando comunicação através do Python

Arduino: 

- Carregue o firmware do protocolo firmata para o Arduino:
Arduino IDE > Arquivo > Exemplos > Firmata > StandardFirmata


Python:

- instale a biblioteca pyfirmata:
```pip3 install pyfirmata```

- execute o programa ```pyarduino.py```

No código dentro de ```pyarduino.py``` não esqueça
de informar a porta que está se comunicando com o arduino:

```python
# ttyACM0 no Linux
# COMx no Windows (x é o número, 1,2,3,4...)
board = Arduino("/dev/ttyACM0")
```

Siga o exemplo do esquema abaixo:

<img src="https://raw.githubusercontent.com/jhoonb/arduino-projetos/master/led_simples_python/esquema_led_simples_python.png" 
height="489" width="539">