# 🧉 Cebador Automático de Mates

Este proyecto es un **cebador automático de mates** desarrollado con Arduino Uno. Utiliza un sensor ultrasónico para detectar el mate, controla una válvula de lavarropas para dispensar agua caliente, y mantiene el agua a la temperatura adecuada mediante una resistencia calefactora. ¡Ideal para los amantes del mate que quieren disfrutar sin interrupciones! 😄

---

## 🛠️ **Características**

- **Detección del mate**: Un sensor ultrasónico **HC-SR04** detecta la presencia del mate.
- **Llenado automático**: Una válvula de lavarropas se activa durante unos segundos para llenar el mate.
- **Control de temperatura**: Detecta si el agua está enfriándose y activa una resistencia calefactora para mantenerla caliente.
- **Automatización completa**: Una vez encendido, el sistema realiza todo automáticamente.

---

## 📋 **Materiales necesarios**

- **Microcontrolador**: Arduino Uno
- **Sensor ultrasónico**: HC-SR04
- **Válvula solenoide**: De lavarropas, compatible con 24V
- **Resistencia calefactora**: Capaz de calentar agua (800W recomendados)
- **Relés**: Para controlar la válvula y la resistencia
- **Sensor de temperatura**: DS18B20
- **Fuente de alimentación**: Suficiente para el Arduino y los componentes
- Cables, protoboard y herramientas de soldadura.

---

## 💻 **Código**

El código del proyecto está disponible en el archivo [**`cebador_de_mates.ino`**](./cebador_de_mates.ino). Contiene las siguientes funcionalidades:

- Leer la distancia del sensor ultrasónico.
- Activar la válvula si el mate está en posición.
- Monitorizar la temperatura del agua y activar la resistencia si es necesario.
- Temporizadores para evitar sobrecalentamiento o llenado excesivo.
