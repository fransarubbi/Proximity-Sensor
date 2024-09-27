// Definición de pines
const int trigger = 2;
const int echo = 0;
const int buz = 32;
const int ledRojo = 33;
const int ledAmarillo = 25;
const int ledVerde = 26;
const int potenciometro = 35;  //ADC 


// Variables 
float tiempo;
float distancia;
unsigned long previousMillis = 0; //variable para almacenar el último tiempo registrado
int potValue = 0;
int pwmValue = 0;


void setup() {
  Serial.begin(115200);
  //configura el sensor de ultrasonido y el buzzer
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(buz, OUTPUT);

  //configura los pines de salida para los LEDs
  pinMode(ledRojo, OUTPUT);
  pinMode(ledAmarillo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
}


void loop() {
  distancia = medirDistancia();
  controlarBuzzer(distancia);
  encenderLed(distancia);
  
  // Enviar la distancia a través del puerto serie
  Serial.println(distancia);
}


//función para medir la distancia con el sensor de ultrasonido HC-SR04
float medirDistancia() {
  float sumaDistancias = 0;  //acumulador
  int numLecturas = 5; //número de lecturas a promediar (para mas precision en medidas)
    
  for (int i = 0; i < numLecturas; i++) {
    //enviamos un pulso al pin trigger
    digitalWrite(trigger, LOW);
    delayMicroseconds(5);
    digitalWrite(trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger, LOW);

    //medimos el tiempo del eco
    tiempo = pulseIn(echo, HIGH);
        
    //calculamos la distancia en centímetros
    float distanciaCalculada = (tiempo * 0.034) / 2;   //0.034 es la velocidad del sonido en cm/µs
    sumaDistancias += distanciaCalculada;
    delay(10); //breve pausa entre lecturas
  }
    
  return sumaDistancias / numLecturas; //retorna el promedio
}


//función para controlar el buzzer en función de la distancia
void controlarBuzzer(float distancia) {
  unsigned long currentMillis = millis();

  //control de alerta por distancia
  //tone(pin, frecuencia)  --> cuanto mas lejos este, menor frecuencia (mas grave)
  //utiliza un temporizador para evitar que el buzzer suene continuamente y que suene mas rapido o lento
  //dependiendo de la distancia. Si la distancia está dentro de un rango específico, el buzzer emitirá un tono diferente.
  if (distancia <= 20 && distancia > 15) {
    if (currentMillis - previousMillis >= 300) { 
      tone(buz, 750);  
      previousMillis = currentMillis;
    }
  } else if (distancia <= 15 && distancia > 10) {
    if (currentMillis - previousMillis >= 250) { 
      tone(buz, 1000);  
      previousMillis = currentMillis;
    }
  } else if (distancia <= 10 && distancia > 8) {
    if (currentMillis - previousMillis >= 200) { 
      tone(buz, 1250);  
      previousMillis = currentMillis;
    }
  } else if (distancia <= 8 && distancia > 5) {
    if (currentMillis - previousMillis >= 150) { 
      tone(buz, 1500);  
      previousMillis = currentMillis;
    }
  } else if (distancia <= 5 && distancia > 3) {
    if (currentMillis - previousMillis >= 100) { 
      tone(buz, 1750);  
      previousMillis = currentMillis;
    }
  } else if (distancia <= 3) {
    if (currentMillis - previousMillis >= 50) { 
      tone(buz, 2000);  
      previousMillis = currentMillis;
    }
  } else {
    noTone(buz); //apaga el buzzer si no hay nada
  }
}


//función para controlar los LEDs según la distancia usando PWM manual
void encenderLed(float distancia) {
  //leer el valor del potenciómetro (de 0 a 4095)
  potValue = analogRead(potenciometro);
  
  //mapear el valor del potenciómetro a un rango PWM (de 0 a 255)
  pwmValue = map(potValue, 0, 4095, 0, 255);

  //implementación manual de PWM para los LEDs
  for (int i = 0; i < 255; i++) {
    if (i < pwmValue) {
      if (distancia <= 20 && distancia > 10) {
        //encender solo el LED verde
        digitalWrite(ledVerde, HIGH);
        digitalWrite(ledAmarillo, LOW);
        digitalWrite(ledRojo, LOW);
      }
      else if (distancia <= 10 && distancia > 4) {
        //encender solo el LED amarillo
        digitalWrite(ledAmarillo, HIGH);
        digitalWrite(ledVerde, LOW);
        digitalWrite(ledRojo, LOW);
      }
      else if (distancia <= 4) {
        //encender solo el LED rojo
        digitalWrite(ledRojo, HIGH);
        digitalWrite(ledAmarillo, LOW);
        digitalWrite(ledVerde, LOW);
      }
    } else {
      //apagar todos los LEDs
      digitalWrite(ledRojo, LOW);
      digitalWrite(ledAmarillo, LOW);
      digitalWrite(ledVerde, LOW);
    }
    delayMicroseconds(100); //controlar la frecuencia del ciclo PWM
  }
}
