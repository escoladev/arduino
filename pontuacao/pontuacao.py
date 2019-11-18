"""
Jhonathan P. Banczek - 2019

github.com/jhoonb

PORTAS DIGITAIS
lado esquerdo - jogador 1.
leds vermelhos: 2,3,4
led verde: 5

PORTAS DIGITAIS
lado direito - jogador 2
leds vermelhos: 8,9,10
led verde: 11

LED JOGO EXECUTANDO: 7

Alto Falante/buzzer/speaker: porta: 12
"""

from pymata_aio.pymata3 import PyMata3
from pymata_aio.constants import Constants
import speech_recognition as sr


def verificar_comando(frase, tipo, quantidade=2):
	
	# palavras para verificar as condições
	comandos = {
	'iniciar': ('iniciar', 'jogo', 
		'game', 'começar', 'inicie', 'comece', 'sim'),

	'jogador_1': ('ponto, jogador', 'um', '1', 'o', 
		'para', 'usuario', 'usuário'),

	'jogador_2': ('ponto', 'jogador', 'dois', '2', 'o', 
		'para', 'usuario', 'usuario')
	}

	qnt = 0
	for palavra in comandos[tipo]:
		if palavra in frase:
			qnt += 1
			print(palavra)

	if qnt >= quantidade:
		if tipo == 'jogador_1':
			if 'um' in frase or '1' in frase:
				return True
			return False

		if tipo == 'jogador_2':
			if '2' in frase or 'dois' in frase:
				return True
			return False

		return True

	return False



class Pontuacao:
	"""
	Uso:

	p = Pontuacao()
	p.play()

	"""

	# placa do arduino
	board = PyMata3()
	# instância de speech_recognition
	microfone = sr.Recognizer()

	def __init__(self):

		# jogadores
		self.jogador_1 = 0
		self.jogador_2 = 0
		self.vencedor = None

		# leds / portas
		self.led_em_jogo = 7
		self.leds_jogador_1 = (2, 3, 4, 5)
		self.leds_jogador_2 = (8, 9, 10, 11)
		# altofalante
		self.alto_falante = 12

		# setup pinagem
		self.board.set_pin_mode(self.led_em_jogo, Constants.OUTPUT)	
		for led in self.leds_jogador_1 + self.leds_jogador_2:
			self.board.set_pin_mode(led, Constants.OUTPUT)

		# configurações do mic
		self.microfone.dynamic_energy_threshold = True
		self.microfone.pause_threshold = 0.8


	def leds_vitoria(self):

		print("\t ", self.leds_vencedor())
		print('\t ', self.vencedor)

		# toca as seguintes notas 2x, depois 1x ao contŕario
		# C4, D4, E4, F4, G4, A4, B4, C5, D5, E5, F5
		notas = [262, 294, 330, 349, 392, 440, 
		494, 523, 587, 659, 698]
		for i in range(3):
			if i == 2: notas.reverse()
			for n in notas:
				self.board.play_tone(self.alto_falante, 
					Constants.TONE_TONE, n, None)
				self.board.sleep(0.1)
		# silencia
		self.board.play_tone(self.alto_falante, 
			Constants.TONE_NO_TONE, 0, 0)

		for i in range(7):
			for porta in self.leds_vencedor():
				self.board.digital_write(porta, 1)
				self.board.sleep(0.1)
				self.board.digital_write(porta, 0)

		for i in range(20):
			for porta in self.leds_vencedor():
				self.board.digital_write(porta, 0)
			
			self.board.sleep(0.1)	
			for porta in self.leds_vencedor():
				self.board.digital_write(porta, 1)
			self.board.sleep(0.1)


	def leds_vencedor(self):
		if self.vencedor == 'jogador_1':
			return self.leds_jogador_1
		return self.leds_jogador_2


	def reiniciar_valores(self):
		
		self.vencedor = None
		self.jogador_1 = 0
		self.jogador_2 = 0
		# led jogo em execucao
		self.board.digital_write(self.led_em_jogo, 1)

		# apaga todos os leds
		for porta in self.leds_jogador_1 + self.leds_jogador_2:
			self.board.digital_write(porta, 0)
		# alto-falante off
		self.board.play_tone(self.alto_falante, 
			Constants.TONE_NO_TONE, 0, 0)


	def ouvir_microfone(self, mensagem='COMANDO DE VOZ'):

		with sr.Microphone() as source:
			self.microfone.adjust_for_ambient_noise(source)

			print(mensagem)
			audio = self.microfone.listen(source)
			try:
				frase = self.microfone.recognize_google(audio, 
					language='pt-BR')
				print("[comando]: " + frase.upper())
				frase = frase.lower()
			except: # sr.UnkownValueError
				print("[comando]: não reconhecido - repita.")
				frase = None
		return frase


	def play(self):

		while True:
			# led desligado enquanto nao iniciar 
			self.board.digital_write(self.led_em_jogo, 0)

			mensagem = 'COMANDO DE VOZ: INICIAR?'
			comando = self.ouvir_microfone(mensagem)
			# não reconheceu - repete.
			if not comando:
				continue
			# se reconheceu, porém frase não é pra iniciar, finaliza
			if not verificar_comando(comando, 'iniciar', 2):
				break

			self.reiniciar_valores()

			while True:
				if self.vencedor:
					print("{} VENCEU!".format(self.vencedor.upper()))
					self.leds_vitoria()
					self.reiniciar_valores()
					break

				mensagem = 'COMANDO DE VOZ: PONTO PARA?'
				comando = self.ouvir_microfone(mensagem)
				# não reconheceu - repete.
				if not comando:
					continue

				if verificar_comando(comando, 'jogador_1', 3):
					self.jogador_1 += 1
				elif verificar_comando(comando, 'jogador_2', 3):
					self.jogador_2 += 1
				else:
					print('[OPÇÃO NAO RECONHECIDA]', comando)

				# jogador 1
				if self.jogador_1 == 1:
					self.board.digital_write(2, 1)
				elif self.jogador_1 == 2:
					self.board.digital_write(3, 1)
				elif self.jogador_1 == 3:
					self.board.digital_write(4, 1)
					self.board.digital_write(5, 1)
					self.vencedor = 'jogador_1'
				else: 
					pass
				# jogador 2
				if self.jogador_2 == 1:
					self.board.digital_write(8, 1)
				elif self.jogador_2 == 2:
					self.board.digital_write(9, 1)
				elif self.jogador_2 == 3:
					self.board.digital_write(10, 1)
					self.board.digital_write(11, 1)
					self.vencedor = 'jogador_2'
				else:
					pass


def main():
	p = Pontuacao()
	p.play()


if __name__ == '__main__':
	main()

