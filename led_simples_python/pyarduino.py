import time
from pyfirmata import Arduino, util

cor = {'amarelo': 12, 'vermelho': 10, 'verde': 11}

# [porta no linux = /dev/tty... ], 
# no windows usar "COM4", "COM3"...
board = Arduino("/dev/ttyACM0")


print("""
--------------------------------------------
\t Controlando porta digital com Python


Lista de cores: verde, amarelo, vermelho
outra valor o programa é finalizado;

--------------------------------------------
	""")

while True:
	valor = input("Digite a cor: ")
	valor = valor.lower()

	if valor in cor:
		board.digital[cor[valor]].write(1)
		time.sleep(3)
		board.digital[cor[valor]].write(0)
	else:
		break

print('fim do programa')

