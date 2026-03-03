```cpp
#include <Servo.h>

Servo myservo;

const int trigPin = 2;
const int echoPin = 4;

const int mediciones = 600;
const float anguloMax = 360.0;
const float pasoAngulo = anguloMax / mediciones;

long duracion;
float distancia;

//Tiempo total que tarda el servo en una vuelta completa
//const unsigned long tiempoVuelta = 8300;//ms
//const unsigned long tiempoPaso = tiempoVuelta / mediciones;

const unsigned long tiempoVueltaHorario = 5350;
const unsigned long tiempoVueltaAntihorario = 5000;

void setup() {
  myservo.attach(8);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(115200);
}

float medirDistancia(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duracion = pulseIn(echoPin, HIGH, 30000);

  if (duracion == 0) return -1;

  return duracion * 0.0343 / 2.0;//cm
}

void loop() {
  //Giro sentido horario
  unsigned long tiempoPaso = tiempoVueltaHorario / mediciones;
  myservo.write(101);

  for (int i = 0; i < mediciones; i++){
    float angulo = i * pasoAngulo;
    distancia = medirDistancia();

    Serial.print(angulo, 1);
    Serial.print(",");
    Serial.println(distancia, 1);

    delay(tiempoPaso);
  }

  myservo.write(91);
  delay(500);

  tiempoPaso = tiempoVueltaAntihorario / mediciones;
  myservo.write(86);

  for (int i = mediciones; i > 0; i--){
    float angulo = i * pasoAngulo;
    distancia = medirDistancia();

    Serial.print(angulo, 1);
    Serial.print(",");
    Serial.println(distancia, 1);

    delay(tiempoPaso);
  }

  myservo.write(91);
  delay(500);
}
```