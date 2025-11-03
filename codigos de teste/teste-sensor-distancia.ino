// --- BIBLIOTECAS NECESSÁRIAS ---
#include <NewPing.h>

// --- DEFINIÇÃO DOS PINOS (Baseado no Robot.ino) ---
#define echo 16     // Sensor ultrasonidos pin A2 
#define trigger 17  // Sensor ultrasonidos pin A3 

// Distância máxima para o sensor tentar medir (em cm)
// Vamos usar 200cm para este teste, para que você possa ver objetos de longe.
// (O seu código de robô usa 40cm para a lógica de combate )
#define distanciaMaximaTeste 200 

// --- INICIALIZA A BIBLIOTECA ---
NewPing sonar(trigger, echo, distanciaMaximaTeste);

void setup() {
  Serial.begin(9600); // [cite: 210]
  Serial.println("--- Teste de Distância (Ultrassônico) ---");
  Serial.println("Aproxime e afaste objetos do sensor.");
}

void loop() {
  // Faz a leitura da distância
  unsigned int uS = sonar.ping(); // Envia o "ping" e mede o tempo de retorno [cite: 224]
  
  // Converte o tempo de retorno em centímetros
  int cm = sonar.convert_cm(uS); // [cite: 224]

  // Imprime o resultado no Monitor Serial
  if (cm == 0) {
    // "0" significa que não detectou nada dentro da distanciaMaximaTeste
    Serial.println("Distância: FORA DE ALCANCE (> 200cm)");
  } else {
    Serial.print("Distância: ");
    Serial.print(cm);
    Serial.println(" cm");
  }

  // Espera 200ms antes de fazer a próxima leitura
  delay(200);
}