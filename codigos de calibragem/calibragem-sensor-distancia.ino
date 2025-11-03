// --- BIBLIOTECAS NECESSÁRIAS ---
#include <NewPing.h>

// --- DEFINIÇÃO DOS PINOS (Baseado no Robot.ino) ---
#define echo 16     // Sensor ultrasonidos pin A2
#define trigger 17  // Sensor ultrasonidos pin A3

// Distância máxima que o sensor vai tentar ler.
// Podemos usar um valor alto aqui para o teste (ex: 200cm).
#define distanciaMaximaHardware 200 

// --- INICIALIZA A BIBLIOTECA ---
NewPing sonar(trigger, echo, distanciaMaximaHardware);

// --- Variável de Calibração ---
// Esta é a distância que você vai ajustar
int distanciaAtaque = 20; // Começa com um valor padrão de 20 cm

void setup() {
  Serial.begin(9600);
  Serial.println("--- Calibrador de Distância de Ataque ---");
  Serial.println("Digite uma nova distância (ex: 25, 30, 15) e aperte Enter.");
  Serial.print("Distância de ataque inicial: ");
  Serial.print(distanciaAtaque);
  Serial.println(" cm");
  Serial.println("----------------------------------------");
}

void loop() {
  
  // 1. Verifica se você digitou uma nova distância no Monitor Serial
  if (Serial.available() > 0) {
    int novoValor = Serial.parseInt(); // Lê o número que você digitou
    
    // Limpa qualquer texto extra (como o "Enter")
    while(Serial.available()) Serial.read(); 
    
    if (novoValor > 0) {
      distanciaAtaque = novoValor; // Atualiza a distância de ataque
      Serial.println("----------------------------------------");
      Serial.print("--- NOVA DISTÂNCIA DE ATAQUE: ");
      Serial.print(distanciaAtaque);
      Serial.println(" cm ---");
    }
  }

  // 2. Faz a leitura do sensor
  unsigned int uS = sonar.ping();
  int cm = sonar.convert_cm(uS);

  // 3. Imprime o status atual
  Serial.print("Medição Atual: ");
  if (cm == 0) {
    Serial.print("FORA DE ALCANCE");
  } else {
    Serial.print(cm);
    Serial.print(" cm");
  }

  Serial.print(" | ");
  Serial.print("Dist. Ataque: ");
  Serial.print(distanciaAtaque);
  Serial.print(" cm");

  // 4. Imprime a DECISÃO (Ataque ou Busca)
  // Esta é a lógica que você usará no seu robô
  Serial.print(" | Decisão: ");
  if (cm == 0) {
    // cm=0 significa "nada detectado" (além de distanciaMaximaHardware)
    Serial.println("BUSCANDO");
  } else if (cm <= distanciaAtaque) {
    // Detectou algo DENTRO da sua distância de ataque
    Serial.println("ATACAR!");
  } else {
    // Detectou algo, mas está FORA da sua distância de ataque
    Serial.println("BUSCANDO (Inimigo Longe)");
  }

  // Pausa para não poluir o monitor
  delay(300);
}