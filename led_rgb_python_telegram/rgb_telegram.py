import os
import telebot
from dataclasses import dataclass

# bot: constantino_bot
# export BOT_API_TOKEN="<chave gerada pelo bot do telegram>"
# configurada como variável ambiente no OS
__token__ = os.environ['BOT_API_TOKEN']

# cores
@dataclass
class RGB:
    nome: str
    r: int
    g: int 
    b: int

cores = { 
    "Branco": RGB("Branco", 255, 255, 255),
    "Azul": RGB("Azul", 0, 0, 255),
    "Vermelho": RGB("Vermelho", 255, 0, 0),
    "Verde": RGB("Verde", 0, 255, 0),
    "Amarelo": RGB("Amarelo", 255, 255, 0),
    "Magenta": RGB("Magenta", 255, 0, 255),
    "Ciano": RGB("Ciano", 0, 255, 255),
    "Preto": RGB("Preto", 0, 0, 0)
}
  
bot = telebot.TeleBot(os.environ['BOT_API_TOKEN'])

print("[Telegram] Escola Padre Constantino - Iniciado!")
print("[Eletiva Missão Transformers!]")
print("aguardando comandos ... ")


menu_inicial = """
Olá! Seja bem-vindo(a) a Escola Padre Constantino de Monte!

Pressione a opção desejada:

/eletiva Eletiva Transformers!

/escola Informações sobre a Escola

...

/menu Voltar para o Menu
"""

menu_escola = """

Informações sobre a Escola

/almoco Qual é o almoço hoje?
/lanche_manha Qual é o lanche da manhã?
/lanche_tarde Qual é o lanche da tarde?
/inep Código Inep da Escola
/fone Telefone da Escola
/email Email institucional da Escola
/github Como isso foi criado?
/sobre Informações sobre a Eletiva

...

/menu voltar para o menu inicial.

"""


def print_info(_id, user, msg):
    s = """
    Id: {},
    Usuário: {},
    msg: {}
    """.format(_id, user, msg)
    print(s)

## ---------------------------  menus

# inicial
@bot.message_handler(commands=['start', 'começar', 'ajuda', 'help', 'menu'])
def inicial(message):
    print_info(message.chat.id, message.chat.username, message.text)
    bot.send_message(
        message.chat.id,
        menu_inicial
    )

# eletiva
@bot.message_handler(commands=['eletiva'])
def eletiva(message):
    print_info(message.chat.id, message.chat.username, message.text)
    markup = telebot.types.ReplyKeyboardMarkup(row_width=2)
    i1 = telebot.types.KeyboardButton('/Branco')
    i2 = telebot.types.KeyboardButton('/Azul')
    i3 = telebot.types.KeyboardButton('/Vermelho')
    i4 = telebot.types.KeyboardButton('/Verde')
    i5 = telebot.types.KeyboardButton('/Amarelo')
    i6 = telebot.types.KeyboardButton('/Magenta')
    i7 = telebot.types.KeyboardButton('/Preto')
    #i8 = telebot.types.KeyboardButton('/Escolher_RGB') # [TODO]
    markup.add(i1, i2, i3, i4, i5, i6, i7)
    #markup.add(i8)
    bot.send_message(message.chat.id, "Escolha uma cor:", reply_markup=markup)

@bot.message_handler(commands=['Branco', 'Azul', 'Vermelho',
'Verde', 'Amarelo', 'Magenta', 'Preto', 'Escolher_RGB'])
def led_cor(message):
    txt = message.text
    txt = txt[1:] # retira o /
    print(txt)
    if txt in cores:
        print(cores[txt])
    # [TODO]
    # Escolher RGB
    # elif txt == "Escolher_RGB":
    #     bot.send_message(message.chat.id, 
    #     "Escolha o valor rgb:" +
    #     "separado por ',' por exemplo: "+
    #     "200, 40, 50" +
    #     ": ")
    # else:
    #     print("manualmente...")
    #     print(txt.strip())


############################################# escola
@bot.message_handler(commands=['escola'])
def escola(message):
    print_info(message.chat.id, message.chat.username, message.text)
    bot.send_message(
        message.chat.id,
        menu_escola
    )

## -------------------------------------------------------
@bot.message_handler(commands=['inep'])
def inep(message):
    print_info(message.chat.id, message.chat.username, message.text)
    bot.send_message(
        message.chat.id,
        "Código INEP: 50018035"
    )

@bot.message_handler(commands=['email', 'e-mail'])
def email(message):
    print_info(message.chat.id, message.chat.username, message.text)
    bot.send_message(
        message.chat.id,
        "E-mail: eepcdm@sed.ms.gov.br"
    )

@bot.message_handler(commands=['fone', 'telefone'])
def fone(message):
    print_info(message.chat.id, message.chat.username, message.text)
    bot.send_message(
        message.chat.id,
        "Telefone: (67) 3454-1045"
    )

#[TODO]
@bot.message_handler(commands=['almoco', 'almoço'])
def almoco(message):
    print_info(message.chat.id, message.chat.username, message.text)
    bot.send_message(
        message.chat.id,
        "O Almoço de hoje é: NÃO SEI."
    )

# [TODO]
@bot.message_handler(commands=['lanche_manha'])
def lanche_manha(message):
    print_info(message.chat.id, message.chat.username, message.text)
    bot.send_message(
        message.chat.id,
        "O lanche de hoje na parte da manhã é: NÃO SEI..."
    )

# [TODO]
@bot.message_handler(commands=['lanche_tarde'])
def lanche_tarde(message):
    print_info(message.chat.id, message.chat.username, message.text)
    bot.send_message(
        message.chat.id,
        "O lanche de hoje na parte da tarde é: NÃO SEI..."
    )

@bot.message_handler(commands=['sobre'])
def sobre(message):
    print_info(message.chat.id, message.chat.username, message.text)
    bot.send_message(
        message.chat.id,
        "Eletiva Transformers: \nProfs.:\n" +
        "- Jhonathan (computação)\n" +
        "- Joice (Física)\n" +
        "- Paula (Química)\n" +
        "Veja os projetos em arduino em: \n" +
        "https://github.com/jhoonb/arduino-projetos/"
    )

# [TODO] colocar link do projeto
@bot.message_handler(commands=['github'])
def github(message):
    print_info(message.chat.id, message.chat.username, message.text)
    bot.send_message(
        message.chat.id,
        "Github do Projeto:\n" +
        "https://github.com/jhoonb/arduino-projetos/tree/master/led_rgb_python_telegram/"
    )

bot.polling()

