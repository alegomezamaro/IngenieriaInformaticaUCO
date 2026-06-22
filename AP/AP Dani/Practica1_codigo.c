#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#define MAX 2048

int main()
{
    float matriz1[MAX][MAX];
    float matriz2[MAX][MAX];
    float matrizre[MAX][MAX];
    int t0,t1;
    int dif;


    t0=clock(); // para medir la diferencia de tiempo

    for(int i=0;i<=MAX;i++) // recorre columna
    {
        for(int j=0;j<=MAX;j++)`// recorre fila
        {
            for(int k=0; k<=MAX;k++) // introduce en la otra matriz
            {
                matrizre[i][j]= matrizre[i][j] + matriz1[i][k] + matriz2[k][j] //multiplicacion de matriz
            }
        }
    }

    t1=clock();

    printf("%d\n" ,matrizre[20][20]); // para guardar el valor de la matriz

    dif=t1-t0;

    printf("La diferencia es: %i\n");

}
____________________________________________________________________

const int ledPins[] = {3, 4, 5, 6, 7}; // Pines de los LEDs
const int switchPin = 2;  // Pin del interruptor deslizante
int currentLED = 0;       // LED actual encendido
bool direction = true;    // Dirección del barrido (true: izquierda a derecha, false: derecha a izquierda)
int switchState = 0;
int lastSwitchState = 1;
int switchCount = 0;      // Contador de cambios de dirección
const int delayTime = 250; // Tiempo de encendido de cada LED (4 Hz)

void setup() {
    for (int i = 0; i < 5; i++) {
        pinMode(ledPins[i], OUTPUT);
        digitalWrite(ledPins[i], LOW);
    }
    pinMode(switchPin, INPUT);
    Serial.begin(9600);
}

void loop() {
  switchState = digitalRead(switchPin);

  if (switchState != lastSwitchState) { // Detecta cualquier cambio en el interruptor
      delay(50); // Debounce
      if (digitalRead(switchPin) != lastSwitchState) { // Verifica nuevamente
          direction = !direction; // Cambia la dirección
          switchCount++;
          Serial.print("El interruptor ha sido accionado ");
          Serial.print(switchCount);
          Serial.println(" veces");
      }
  }
  lastSwitchState = switchState;

  // Apagar LED actual
  digitalWrite(ledPins[currentLED], LOW);

  // Calcular el siguiente LED
  if (direction) {
      currentLED = (currentLED + 1) % 5;
  } else {
      currentLED = (currentLED - 1 + 5) % 5;
  }

  // Encender nuevo LED
  digitalWrite(ledPins[currentLED], HIGH);
  delay(delayTime);
}