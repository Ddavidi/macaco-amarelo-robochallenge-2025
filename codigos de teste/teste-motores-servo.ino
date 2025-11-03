//==================================================================
// CÓDIGO DE TESTE - CICLO DE MOTORES
//
// Testa o ciclo de movimento (Frente, Parado, Ré) utilizando
// os valores de calibragem de parada personalizados.
//==================================================================

// --- Bibliotecas ---
#include <Servo.h>     // Biblioteca para controle dos servos

// --- Mapeamento de Pinos do Hardware ---
#define motorEsquerdo 5   // Pino de sinal do motor esquerdo
#define motorDireito 6    // Pino de sinal do motor direito

// --- Objetos Servo ---
Servo servoEsquerdo; // Objeto para o servo esquerdo
Servo servoDireito;  // Objeto para o servo direito

// --- Valores de Calibragem (Descobertos via Teste) ---
int PARADO_ESQ = 102; // Ponto de parada (ponto neutro) do motor esquerdo (Pino 5)
int PARADO_DIR = 129; // Ponto de parada (ponto neutro) do motor direito (Pino 6)

// --- Valores de Movimento (Baseado na lógica do robô) ---
// Função Frente: esquerdo=180, direito=0
int FRENTE_ESQ = 180;
int FRENTE_DIR = 0;

// Função Ré: esquerdo=0, direito=180
int RE_ESQ = 0;
int RE_DIR = 180;


//==================================================================
// SETUP: Executado uma vez quando o robô é ligado
//==================================================================
void setup() {
  // "Anexa" os objetos servo aos seus respectivos pinos de sinal
  servoEsquerdo.attach(motorEsquerdo);
  servoDireito.attach(motorDireito);

  // Inicia a comunicação serial (para mensagens de depuração)
  Serial.begin(9600);
  Serial.println("--- Teste de Ciclo com Calibracao Correta ---");
  Serial.print("Ponto Parado Esq (Pino 5): ");
  Serial.println(PARADO_ESQ);
  Serial.print("Ponto Parado Dir (Pino 6): ");
  Serial.println(PARADO_DIR);

  // Garante que o robô comece PARADO usando os valores calibrados
  Serial.println("Iniciando PARADO por 3 segundos...");
  servoEsquerdo.write(PARADO_ESQ);
  servoDireito.write(PARADO_DIR);
  delay(3000); 
}

//==================================================================
// LOOP: Executado continuamente após o setup
//==================================================================
void loop() {
  // --- 1. MOVER PARA FRENTE ---
  Serial.println("Movendo PARA FRENTE por 3 segundos...");
  servoEsquerdo.write(FRENTE_ESQ); // 180
  servoDireito.write(FRENTE_DIR);   // 0
  delay(3000); // Duração da manobra

  // --- 2. PARAR (CALIBRADO) ---
  Serial.println("PARANDO (Calibrado) por 2 segundos...");
  servoEsquerdo.write(PARADO_ESQ); // 102
  servoDireito.write(PARADO_DIR); // 129
  delay(2000); // Duração da manobra

  // --- 3. MOVER PARA TRÁS (RÉ) ---
  Serial.println("Movendo PARA TRAS (Re) por 3 segundos...");
  servoEsquerdo.write(RE_ESQ); // 0
  servoDireito.write(RE_DIR); // 180
  delay(3000); // Duração da manobra

  // --- 4. PARAR (CALIBRADO) ---
  Serial.println("PARANDO (Calibrado) por 2 segundos...");
  servoEsquerdo.write(PARADO_ESQ); // 102
  servoDireito.write(PARADO_DIR); // 129
  delay(2000); // Duração da manobra

  // O loop reinicia
  Serial.println("--- Reiniciando o ciclo ---");
}
