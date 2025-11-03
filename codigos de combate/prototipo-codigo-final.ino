// --- DEFINIÇÃO DOS PINOS ---
#define sensorEsquerdo 2
#define sensorDireito 3
// O pino 4 (botão) não é mais usado
#define motorEsquerdo 5
#define motorDireito 6
#define echo 16     // Sensor ultrassônico pino A2
#define trigger 17  // Sensor ultrassônico pino A3

#define distanciaMaxima 10 // Esta será a distância de detecção do robô

// --- BIBLIOTECAS ---
#include <Servo.h>
#include <NewPing.h>

// --- VALORES DE CALIBRAGEM DOS MOTORES (Descobertos no teste) ---
int PARADO_ESQUERDO = 102;
int PARADO_DIREITO = 129;

// --- INICIALIZAÇÃO DAS BIBLIOTECAS ---
Servo servoDireito;   // Inicia um servo com o nome servoDireito
Servo servoEsquerdo; // Inicia um servo com o nome servoEsquerdo
NewPing sonar(trigger, echo, distanciaMaxima); // Inicia o sensor de ultrassom

// --- VARIÁVEIS GLOBAIS ---
boolean modoCombate = true;  // O robô já começa em modo de combate (sem botão)
int estadoSensorDireito;     // Variável que armazena o estado do sensor Direito
int estadoSensorEsquerdo;    // Variável que armazena o estado do sensor Esquerdo
int cm;                      // Variável para medir a distância (em centímetros)
unsigned int uS;             // Variável para medir o tempo do ultrassom

//==================================================================
// SETUP: Roda uma vez quando o robô é ligado
//==================================================================
void setup() {
  // Configura os pinos dos sensores de linha como ENTRADA
  pinMode(sensorDireito, INPUT);
  pinMode(sensorEsquerdo, INPUT);
  
  // Configura os pinos do ultrassom
  pinMode(echo, INPUT);
  pinMode(trigger, OUTPUT);
  
  // "Anexa" os servos aos pinos
  servoDireito.attach(motorDireito);
  servoEsquerdo.attach(motorEsquerdo);
  
  // Inicia o monitor serial (para depuração)
  Serial.begin(9600);
  Serial.println("ROBO PRONTO...");
  Serial.println("Iniciando combate em 5 segundos...");

  // Espera 5 segundos antes de começar (Regra do Sumô)
  delay(5000);
}

//==================================================================
// LOOP: Roda continuamente após o setup
//==================================================================
void loop() {
  delay(50);      // Pequena pausa para estabilizar o programa
  lerSensores();  // Lê todos os sensores

  // O 'modoCombate' é sempre verdadeiro, então executamos a lógica de combate
  
  // --- LÓGICA DE PRIORIDADE CORRIGIDA ---
  
  // 1. PRIORIDADE MÁXIMA: Evitar a linha branca
  // (Sensor LOW significa que detectou a linha branca)
  if (estadoSensorDireito == LOW || estadoSensorEsquerdo == LOW) {
    Evasao(); // Executa a manobra de evasão (dá ré)
  }
  // 2. SEGUNDA PRIORIDADE: Se não viu a linha, procurar inimigo
  // (cm != 0 significa que o sonar detectou um objeto)
  else if (cm != 0) {
    Frente(); // Ataca, movendo-se para frente
  }
  // 3. ÚLTIMA PRIORIDADE: Se não viu a linha E não viu o inimigo
  else {
    GirarDireita(); // Busca o inimigo
  }
}

//==================================================================
// --- FUNÇÕES DO ROBÔ ---
//==================================================================

// --- FUNÇÃO DE LEITURA DOS SENSORES ---
void lerSensores() {
  estadoSensorDireito = digitalRead(sensorDireito);   // Lê o sensor de linha direito
  estadoSensorEsquerdo = digitalRead(sensorEsquerdo); // Lê o sensor de linha esquerdo
  
  // Lê o sensor de ultrassom e converte para centímetros
  uS = sonar.ping();
  cm = sonar.convert_cm(uS);
}

// --- MANOBRAS DE MOVIMENTO ---

void GirarDireita() {
  Serial.println("Buscando Inimigo...");
  servoDireito.write(120);
  servoEsquerdo.write(120);
  delay(50);
}

void GirarEsquerda() {
  servoDireito.write(0);
  servoEsquerdo.write(0);
  delay(50);
}

void Frente() {
  Serial.println("ATACANDO!");
  servoDireito.write(0);
  servoEsquerdo.write(180);
  delay(100);
}

void Re() { // "Atras" em espanhol
  Serial.println("Dando Re...");
  servoDireito.write(180);
  servoEsquerdo.write(0);
  delay(50);
}

void Parar() { // "Parado" em espanhol
  Serial.println("Parando...");
  // USA OS VALORES DE CALIBRAGEM QUE VOCÊ ENCONTROU
  servoDireito.write(PARADO_DIREITO);   // 129
  servoEsquerdo.write(PARADO_ESQUERDO); // 102
  delay(50);
}

void Evasao() {
  Serial.println("Evasao! Linha branca detectada.");
  Parar(); // Para usando os valores calibrados
  delay(100);
  Re(); // Dá ré
  delay(1000); // Continua dando ré por 1 segundo
}
