// Incluindo a biblioteca para o sensor de temperatura
#include <Wire.h>
#include <Adafruit_MLX90614.h>

// Definindo os pinos de controle
const int pinMotorVentilador = 9;
const int pinLEDEmergencia = 8;
const int pinBuzina = 7;
const int pinSensorTemperatura = A0;

// Inicializando o sensor de temperatura
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  // Inicializando os pinos de controle como saídas
  pinMode(pinMotorVentilador, OUTPUT);
  pinMode(pinLEDEmergencia, OUTPUT);
  pinMode(pinBuzina, OUTPUT);

  // Inicializando a comunicação serial
  Serial.begin(9600);

  // Inicializando o sensor de temperatura
  mlx.begin();
}

void loop() {
  // Lendo a temperatura em graus Celsius
  float temperatura = mlx.readObjectTempC();

  // Imprimindo a temperatura no monitor serial
  Serial.print("Temperatura: ");
  Serial.println(temperatura);

  // Verificando as condições e realizando as ações correspondentes
  if (temperatura >= 30) {
    // Acionando o motor do ventilador
    digitalWrite(pinMotorVentilador, HIGH);
  } else {
    // Desligando o motor do ventilador
    digitalWrite(pinMotorVentilador, LOW);
  }

  if (temperatura > 50) {
    // Acionando o LED vermelho e a buzina em caso de emergência
    digitalWrite(pinLEDEmergencia, HIGH);
    tone(pinBuzina, 1000); // Frequência de 1000 Hz na buzina
  } else {
    // Desligando o LED vermelho e a buzina
    digitalWrite(pinLEDEmergencia, LOW);
    noTone(pinBuzina);
  }

  // Aguardando um intervalo de tempo (ajuste conforme necessário)
  delay(1000);
}
