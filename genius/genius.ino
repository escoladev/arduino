/*
 * pequena modificação da implementação original disponível em:
 * https://meetarduino.wordpress.com/2012/05/27/arduino-genius-jogo-da-memoria/
 * marcosschwaab
 */

//Define as notas
#define NOTA_D4  294
#define NOTA_G4  392
#define NOTA_A4  440
#define NOTA_A5  880

// criando o array para os 4 sons para sortear um som
int tons[4] = { NOTA_A5, NOTA_A4, NOTA_G4, NOTA_D4 };
// Nossa sequência de até 100 itens vai começar vazia.
int sequencia[100] = {};
// Indica a rodada atual que o jogo se encontra.
int rodada_atual = 0;
// Indica o passo atual dentro da sequência, é usado enquanto a sequência
// está sendo reproduzida.
int passo_atual_na_sequencia = 0;

/*
   Indica o pino de áudio, leds e botões.
   Os pinos de leds e botões estão em ordem, relacionados uns aos outros, ou
   seja, o primeiro led está relacionado ao primeiro botão. A ordem destas
   sequências também estão relacionadas a ordem dos tons.
*/
int pinoAltoFalante = 12;
int pinosLeds[4] = { 2, 3, 4, 5 };
int pinosBotoes[4] = { 8, 9, 10, 11 };

// Indica se um botão foi pressionado durante o loop principal.
int botao_pressionado = 0;
// Flag indicando se o jogo acabou.
int perdeu_o_jogo = false;


void setup() {

  // configuração dos modos (input / output) dos pinos
  for (int i = 0; i <= 3; i++) {
    // Definindo o modo dos pinos dos Leds como saída.
    pinMode(pinosLeds[i], OUTPUT);
    // Definindo o modo dos pinos dos Botões como entrada.
    pinMode(pinosBotoes[i], INPUT);
  }

  // Definindo o modo do pino de Áudio como saída.
  pinMode(pinoAltoFalante, OUTPUT);

  // Inicializando o random através de uma leitura da porta analógica.
  // Esta leitura gera um valor variável entre 0 e 1023.
  randomSeed(analogRead(0));
}

/*
   inicializa as variaveis do programa para seu valor padrão,
   pré-definido no início
*/
void inicializa_valores() {
  int sequencia[100] = {};
  rodada_atual = 0;
  passo_atual_na_sequencia = 0;
  perdeu_o_jogo = false;
}

void verifica_se_perdeu() {

  if (perdeu_o_jogo) {
    inicializa_valores();
  }

}

void loop() {
  // Se perdeu o jogo reinicializamos todas as variáveis.
  verifica_se_perdeu();
  // Toca um som de início para anúnicar que o jogo está começando quando é a primeira rodada.
  if (rodada_atual == 0) {
    tocarSomDeInicio();
    delay(500);
  }

  // Chama a função que inicializa a próxima rodada.
  proximaRodada();
  // Reproduz a sequência atual.
  reproduzirSequencia();
  // Aguarda os botões serem pressionados pelo jogador.
  aguardarJogador();

  // Aguarda 1 segundo entre cada jogada.
  delay(1000);
}

// Sorteia um novo item e adiciona na sequência.
void proximaRodada() {
  int numero_sorteado = random(0, 4);
  sequencia[rodada_atual++] = numero_sorteado;
}

// Reproduz a sequência para ser memorizada.
void reproduzirSequencia() {
  for (int i = 0; i < rodada_atual; i++) {
    tone(pinoAltoFalante, tons[sequencia[i]]);
    digitalWrite(pinosLeds[sequencia[i]], HIGH);
    delay(500);
    noTone(pinoAltoFalante);
    digitalWrite(pinosLeds[sequencia[i]], LOW);
    delay(100);
  }
  noTone(pinoAltoFalante);
}

// Aguarda o jogador iniciar sua jogada.
void aguardarJogador() {
  for (int i = 0; i < rodada_atual; i++) {
    aguardarJogada();
    verificarJogada();

    if (perdeu_o_jogo) {
      break;
    }

    passo_atual_na_sequencia++;
  }

  // Redefine a variável para 0.
  passo_atual_na_sequencia = 0;
}

void aguardarJogada() {
  boolean jogada_efetuada = false;
  while (!jogada_efetuada) {
    for (int i = 0; i <= 3; i++) {
      if (digitalRead(pinosBotoes[i]) == HIGH) {
        // Dizendo qual foi o botao pressionado.
        botao_pressionado = i;

        tone(pinoAltoFalante, tons[i]);
        digitalWrite(pinosLeds[i], HIGH);
        delay(300);
        digitalWrite(pinosLeds[i], LOW);
        noTone(pinoAltoFalante);

        jogada_efetuada = true;
      }
    }
    delay(10);
  }
}

void verificarJogada() {
  if (sequencia[passo_atual_na_sequencia] != botao_pressionado) {
    // GAME OVER.
    for (int i = 0; i <= 3; i++) {
      tone(pinoAltoFalante, tons[i]);
      digitalWrite(pinosLeds[i], HIGH);
      delay(200);
      digitalWrite(pinosLeds[i], LOW);
      noTone(pinoAltoFalante);
    }

    tone(pinoAltoFalante, tons[3]);
    for (int i = 0; i <= 3; i++) {
      digitalWrite(pinosLeds[0], HIGH);
      digitalWrite(pinosLeds[1], HIGH);
      digitalWrite(pinosLeds[2], HIGH);
      digitalWrite(pinosLeds[3], HIGH);
      delay(100);
      digitalWrite(pinosLeds[0], LOW);
      digitalWrite(pinosLeds[1], LOW);
      digitalWrite(pinosLeds[2], LOW);
      digitalWrite(pinosLeds[3], LOW);
      delay(100);
    }
    noTone(pinoAltoFalante);
    // finaliza com som de "Mario Bros Death"
    tocarSomPerdeu();

    perdeu_o_jogo = true;
  }
}

void tocarSomDeInicio() {
  tone(pinoAltoFalante, tons[0]);

  for (int i = 0; i <= 3; i++) {
    digitalWrite(pinosLeds[i], HIGH);
  }
  delay(500);
  for (int i = 0; i <= 3; i++) {
    digitalWrite(pinosLeds[i], LOW);
  }
  delay(500);
  noTone(pinoAltoFalante);
}

/*
 * toca um som de "perdeu uma vida" como no Mário Bros
 * https://www.youtube.com/watch?v=cO8xgXcm_hg
 * (tenta pelo menos...)
 */
void tocarSomPerdeu() {

  int mario1[3] = {523, 554, 587};
  int mario2[8] = {998, 698, 698, 698, 659, 587, 523, 330};
  int mario3[4] = {392, 330, 262, 262};

  for (int i = 0; i < 3; i ++) {
    tone(pinoAltoFalante, mario1[i]);
    delay(80);
  }
  delay(80);

  for (int i = 0; i < 8; i ++) {
    tone(pinoAltoFalante, mario2[i]);
    delay(190);
    noTone(pinoAltoFalante);
    delay(10);
  }

  for (int i = 0; i < 3; i ++) {
    tone(pinoAltoFalante, mario3[i]);
    delay(200);
    noTone(pinoAltoFalante);
    delay(10);
  }
  noTone(pinoAltoFalante);
}
