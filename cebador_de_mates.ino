// Definir los pines
const int triggerPin = 2;
const int echoPin = 3;
const int ledPin = 13;
const int relayPin = 12;

// Variables para la distancia y el tiempo
long duration;
float distance;
unsigned long timeUnderThreshold = 0;
bool ledBlinking = false;
unsigned long blinkStartTime;
const float thresholdDistance = 5.80; // distancia umbral en cm
const unsigned long thresholdTime = 5000; // tiempo umbral en milisegundos
const unsigned long blinkDuration = 1000; // tiempo de parpadeo en milisegundos
const unsigned long relayActiveTime = 2800; // tiempo de activación del relé

bool relayActivated = false; // Estado del relé
bool distanceIncreased = true; // Indicador de alejamiento, iniciar en true para la primera vez
float lastRelayActivationDistance = 0; // Última distancia al activar el relé

void setup() {
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  
  digitalWrite(ledPin, LOW); // LED apagado al inicio
  digitalWrite(relayPin, HIGH); // Relé inicialmente en estado "abierto" (NO)

  Serial.begin(9600); // Iniciar el monitor serie
}

void loop() {
  // Medir la distancia
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.0343) / 2; // Convertir tiempo a distancia

  // Mostrar la distancia en el monitor serie
  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Verificar si la distancia está por debajo del umbral
  if (distance < thresholdDistance) {
    // Si está debajo del umbral, iniciar el temporizador
    if (timeUnderThreshold == 0 && !ledBlinking) {
      timeUnderThreshold = millis(); // Iniciar el tiempo
    }

    // Si ha pasado el tiempo umbral con la distancia baja y el relé no está activado
    if (millis() - timeUnderThreshold >= thresholdTime && !relayActivated && distanceIncreased) {
      // Activar el LED y "cerrar" el relé (inverso: poner en LOW para cerrarlo)
      digitalWrite(ledPin, HIGH);
      digitalWrite(relayPin, LOW); // Relé activado (cerrado)
      delay(relayActiveTime);

      // "Abrir" el relé (inverso: poner en HIGH para abrirlo)
      digitalWrite(relayPin, HIGH);

      // Guardar la distancia en la que se activó el relé
      lastRelayActivationDistance = distance;
      relayActivated = true; // Marcar que el relé fue activado
      distanceIncreased = false; // Resetear el indicador de alejamiento

      // Iniciar el parpadeo del LED durante 30 segundos
      ledBlinking = true;
      blinkStartTime = millis();
      timeUnderThreshold = 0; // Resetear el tiempo
    }
  } else {
    // Si la distancia es mayor al umbral, reiniciar el tiempo y marcar alejamiento
    timeUnderThreshold = 0;

    // Si la distancia aumenta lo suficiente desde la última activación, permitir una nueva activación
    if (relayActivated && distance > thresholdDistance) {
      distanceIncreased = true; // Marcar que la distancia ha aumentado lo suficiente
      relayActivated = false; // Resetear el estado del relé
    }
  }

  // Si está en el modo de parpadeo
  if (ledBlinking) {
    unsigned long currentTime = millis();
    
    // Verificar si el tiempo de parpadeo ha terminado
    if (currentTime - blinkStartTime < blinkDuration) {
      // Hacer que el LED parpadee
      if ((currentTime / 500) % 2 == 0) {
        digitalWrite(ledPin, HIGH);
      } else {
        digitalWrite(ledPin, LOW);
      }
    } else {
      // Terminar el parpadeo después de 30 segundos
      ledBlinking = false;
      digitalWrite(ledPin, LOW); // Asegurarse de que el LED esté apagado
    }
  } else {
    // Solo cerrar el relé si el LED NO está parpadeando
    digitalWrite(relayPin, HIGH); // Mantener el relé abierto cuando no está parpadeando
  }

  delay(100); // Pequeño retraso para evitar lecturas inestables
}  
