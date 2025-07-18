# 🎮 Ping Pong com Arduino e Display TFT

## 📜 Sobre o Projeto

Este projeto implementa o clássico jogo Ping Pong utilizando um microcontrolador Arduino, um display TFT colorido e botões para a interação do usuário. É uma demonstração prática de programação para sistemas embarcados e interação hardware-software, ideal para exibir em um portfólio de IoT e programação.

O jogo foi projetado para dois jogadores, onde cada um controla uma raquete através de dois botões (para cima e para baixo). O objetivo é simples: rebater a bola, enganar o adversário e ser o primeiro a atingir a pontuação máxima para vencer.

## ✨ Funcionalidades

- **Jogabilidade para Dois Jogadores**: Controles independentes para cada jogador.  
- **Display TFT Colorido**: Interface gráfica vibrante para o jogo.  
- **Sistema de Pontuação**: O placar é atualizado em tempo real e exibido na tela.  
- **Máquina de Estados**: Gerencia a tela inicial, o jogo, a pausa e a tela de fim de jogo.  
- **Efeitos Sonoros**: Um buzzer emite sons quando um ponto é marcado, aumentando a imersão.  
- **Controle de FPS**: Garante uma animação suave e jogabilidade consistente.

## 🛠️ Hardware Necessário

| Componente                     | Quantidade | Descrição                            |
|-------------------------------|------------|--------------------------------------|
| Arduino (Uno, Nano, etc.)     | 1          | O cérebro do projeto.                |
| Display TFT 1.8" (160x128)    | 1          | Para a visualização do jogo.         |
| Push Buttons (Botões)         | 4          | Para controlar as raquetes.          |
| Buzzer                        | 1          | Para os efeitos sonoros.             |
| Protoboard e Jumpers          | 14         | Para montar e conectar o circuito.   |

## 🔌 Montagem do Circuito

A conexão dos componentes ao Arduino deve seguir a pinagem definida no início do código:

### Display TFT (SPI)

| Função | Pino no Arduino |
|--------|------------------|
| CS     | 10               |
| DC (A0)| 9                |
| RST    | 8                |
| SDA    | 11               |
| SCK    | 13               |
| LED    | 3.3V             |
| VCC    | 5V               |
| GND    | GND              |

### Controles Jogador 1

- Botão Cima: Pino **2**  
- Botão Baixo: Pino **3**

### Controles Jogador 2

- Botão Cima: Pino **4**  
- Botão Baixo: Pino **5**

### Buzzer

- Pino Positivo (+): **6**  
- Pino Negativo (-): **GND**

> 💡 **Observação**: Os botões foram configurados com `INPUT_PULLUP`, ou seja, o resistor de pull-up interno do Arduino é usado. Portanto, conecte os botões entre o pino digital e o **GND**, sem resistores externos.

## 📚 Bibliotecas

Para compilar o código, certifique-se de ter as seguintes bibliotecas instaladas na sua Arduino IDE:

- `<SPI.h>`: Biblioteca padrão para comunicação SPI, usada pelo display.
- `<TFT.h>`: Biblioteca oficial da Arduino para controlar displays TFT.  
  > Acesse o **Gerenciador de Bibliotecas**: `Ferramentas > Gerenciar Bibliotecas...`

## 👨‍💻 Análise do Código

O código é estruturado em torno de uma **máquina de estados finitos** que gerencia o fluxo do jogo.

### 🔹 Constantes e Variáveis Globais

No topo do código estão definidos:
- Pinos de controle
- Constantes do jogo (`PONTUACAO_MAXIMA`)
- Variáveis globais de posição, placar e velocidade

### 🔹 `enum EstadoJogo`

Enumeração que define os possíveis estados do jogo:

- `TELA_INICIAL`: Tela de boas-vindas  
- `JOGANDO`: Estado principal do jogo  
- `PAUSADO`: Jogo congelado  
- `FIM_DE_JOGO`: Exibe o vencedor e finaliza a partida

### 🔹 `setup()`

Executado uma única vez ao ligar o Arduino:
- Inicializa a comunicação serial e o display
- Configura pinos dos botões e do buzzer
- Exibe a tela inicial

### 🔹 `loop()`

Laço principal:
- Um `switch` verifica o `estadoAtual` e executa o trecho apropriado
- No modo `JOGANDO`, o código respeita o `frameDelay` para manter a velocidade constante

### 🔹 Funções Principais

- **`inicializarJogo()`**: Reseta o placar e posiciona elementos no início do jogo  
- **`moverRaquetes()`**: Move as raquetes de acordo com os botões pressionados  
- **`moverBola()`**: Atualiza a posição da bola com base na velocidade  
- **`checarColisoes()`**: Lida com colisões e pontuações  
- **`desenharJogo()`**: Renderiza os elementos na tela  
- **`tocarSomPonto()`**: Usa `tone()` para emitir som ao marcar ponto

## 🚀 Como Jogar

- **Início**: Após ligar o Arduino, será exibida a tela inicial.  
  ➤ Pressione **todos os quatro botões** simultaneamente para iniciar.

- **Controles**:
  - **Jogador 1 (esquerda)**: Botões nos pinos 2 (cima) e 3 (baixo)
  - **Jogador 2 (direita)**: Botões nos pinos 4 (cima) e 5 (baixo)

- **Pausa**: Pressione os **quatro botões ao mesmo tempo** para pausar ou retomar

- **Objetivo**: O primeiro a alcançar **10 pontos** vence  
  ➤ Após a partida, será exibida a tela "GAME OVER" com o nome do vencedor.  
  ➤ Para jogar novamente, reinicie o Arduino.
