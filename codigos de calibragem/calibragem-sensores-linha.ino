// --- DEFINIÇÃO DOS PINOS (Baseado no Robot.ino) ---
#define sensorIzquierdo 2
#define sensorDerecho 3

void setup() {
  // Inicia a comunicação serial
  Serial.begin(9600);
  
  // Configura os pinos dos sensores como entrada
  pinMode(sensorIzquierdo, INPUT);
  pinMode(sensorDerecho, INPUT);
  
  Serial.println("--- Calibrador de Sensores Infravermelhos ---");
  Serial.println("O estado atual será impresso continuamente.");
  Serial.println("Posicione o sensor e gire o parafuso de sensibilidade.");
  Serial.println("-------------------------------------------------");
}

void loop() {
  // Lê o estado atual de ambos os sensores
  int estadoEsqAtual = digitalRead(sensorIzquierdo);
  int estadoDirAtual = digitalRead(sensorDerecho);
  
  // --- Imprime o status do Sensor Esquerdo ---
  Serial.print("ESQUERDO (Pino 2): ");
  if (estadoEsqAtual == LOW) {
    Serial.print("Linha BRANCA (LOW)");
  } else {
    Serial.print("Superfície PRETA (HIGH)");
  }
  
  // --- Imprime um separador ---
  Serial.print("  |  ");
  
  // --- Imprime o status do Sensor Direito ---
  Serial.print("DIREITO (Pino 3): ");
  if (estadoDirAtual == LOW) {
    Serial.println("Linha BRANCA (LOW)");
  } else {
    Serial.println("Superfície PRETA (HIGH)");
  }
  
  // Pequena pausa. 100ms é rápido o suficiente para feedback
  // em tempo real, mas lento o suficiente para não travar o monitor.
  delay(100);
}