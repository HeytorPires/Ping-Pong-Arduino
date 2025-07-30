#include <SPI.h>
#include <TFT.h>

// Pinos do display
#define cs   10
#define dc   9
#define rst  8

// Pinos dos botões
#define btn_p1_up   2
#define btn_p1_down 3
#define btn_p2_up   4
#define btn_p2_down 5

TFT TFTScreen = TFT(cs, dc, rst);

// Tela
int telaLargura = 160;
int telaAltura = 128;

// Raquetes
int raqueteLargura = 4;
int raqueteAltura = 30;
int raquete1_Y;
int raquete2_Y;
int raquete_velocidade = 4;

// Bola
int bola_X, bola_Y;
int bola_antigaX, bola_antigaY;
int bola_tamanho = 4;
int velocidade_X = 2;
int velocidade_Y = 2;

// Placar
int placar1 = 0, placar2 = 0;
int ultimoPlacar1 = -1, ultimoPlacar2 = -1;

// Controle de tempo (FPS)
unsigned long lastUpdateTime = 0;
const unsigned long frameDelay = 30; // Aproximadamente 60 FPS

void setup() {
  Serial.begin(9600);
  TFTScreen.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV2); // Máxima velocidade SPI no UNO
  TFTScreen.background(0, 0, 0);
  TFTScreen.setTextSize(2);

  pinMode(btn_p1_up, INPUT);
  pinMode(btn_p1_down, INPUT);
  pinMode(btn_p2_up, INPUT);
  pinMode(btn_p2_down, INPUT);

  raquete1_Y = (telaAltura / 2) - (raqueteAltura / 2);
  raquete2_Y = (telaAltura / 2) - (raqueteAltura / 2);

  resetarBola();
  desenharTudo(true); // Desenha tudo inicialmente
}

void loop() {
  unsigned long now = millis();

  if (now - lastUpdateTime >= frameDelay) {
    lastUpdateTime = now;

    moverRaquetes();

    // Salvar posição antiga da bola
    bola_antigaX = bola_X;
    bola_antigaY = bola_Y;

    // Mover bola
    bola_X += velocidade_X;
    bola_Y += velocidade_Y;

    checarColisoes();

    desenharTudo(false); // Atualiza apenas o necessário
  }
}

void moverRaquetes() {
  if (digitalRead(btn_p1_up) == HIGH && raquete1_Y > 0)
    raquete1_Y -= raquete_velocidade;
  if (digitalRead(btn_p1_down) == HIGH && raquete1_Y < telaAltura - raqueteAltura)
    raquete1_Y += raquete_velocidade;
  if (digitalRead(btn_p2_up) == HIGH && raquete2_Y > 0)
    raquete2_Y -= raquete_velocidade;
  if (digitalRead(btn_p2_down) == HIGH && raquete2_Y < telaAltura - raqueteAltura)
    raquete2_Y += raquete_velocidade;
}

void checarColisoes() {
  // Paredes
  if (bola_Y <= 0 || bola_Y >= telaAltura - bola_tamanho)
    velocidade_Y = -velocidade_Y;

  // Raquete 1
  if (bola_X <= raqueteLargura &&
      bola_Y > raquete1_Y && bola_Y < raquete1_Y + raqueteAltura)
    velocidade_X = -velocidade_X;

  // Raquete 2
  if (bola_X >= telaLargura - raqueteLargura - bola_tamanho &&
      bola_Y > raquete2_Y && bola_Y < raquete2_Y + raqueteAltura)
    velocidade_X = -velocidade_X;

  // Pontuação
  if (bola_X < 0) {
    placar2++;
    resetarBola();
  }

  if (bola_X > telaLargura) {
    placar1++;
    resetarBola();
  }
}

void resetarBola() {
  bola_X = telaLargura / 2;
  bola_Y = telaAltura / 2;
  velocidade_X = -velocidade_X;
  delay(500); // pequena pausa para reinício
}

void desenharTudo(bool inicial) {
  // Apaga bola antiga
  if (!inicial) {
    TFTScreen.stroke(0, 0, 0);
    TFTScreen.rect(bola_antigaX, bola_antigaY, bola_tamanho, bola_tamanho);
  }

  // Apaga raquetes antigas (coluna inteira)
  if (!inicial) {
    TFTScreen.stroke(0, 0, 0);
    TFTScreen.rect(0, 0, raqueteLargura, telaAltura);
    TFTScreen.rect(telaLargura - raqueteLargura, 0, raqueteLargura, telaAltura);
  }

  // Desenha raquetes
  TFTScreen.stroke(255, 255, 255);
  TFTScreen.rect(0, raquete1_Y, raqueteLargura, raqueteAltura);
  TFTScreen.rect(telaLargura - raqueteLargura, raquete2_Y, raqueteLargura, raqueteAltura);

  // Desenha bola
  TFTScreen.rect(bola_X, bola_Y, bola_tamanho, bola_tamanho);

  // Atualiza placar somente se mudou ou no início
  if (placar1 != ultimoPlacar1 || placar2 != ultimoPlacar2 || inicial) {
    TFTScreen.stroke(0, 0, 0);
    TFTScreen.setTextSize(2);
    TFTScreen.setCursor(telaLargura / 2 - 20, 5);
    TFTScreen.print("00");
    TFTScreen.setCursor(telaLargura / 2 + 10, 5);
    TFTScreen.print("00");

    TFTScreen.stroke(255, 255, 255);
    TFTScreen.setCursor(telaLargura / 2 - 20, 5);
    TFTScreen.print(placar1);
    TFTScreen.setCursor(telaLargura / 2 + 10, 5);
    TFTScreen.print(placar2);

    ultimoPlacar1 = placar1;
    ultimoPlacar2 = placar2;
  }
}
