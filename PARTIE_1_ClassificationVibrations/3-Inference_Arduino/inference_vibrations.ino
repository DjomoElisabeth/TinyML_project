/*
  IMU Classifier - Classification des Vibrations
  
  Ce programme utilise l'IMU intégré pour lire les données d'accélération et de gyroscope.
  Une fois qu'un nombre suffisant d'échantillons est collecté, il utilise un modèle TensorFlow Lite (Micro)
  pour classifier le mouvement comme une vibration connue.

  Ce code est conçu pour fonctionner sur une carte Arduino Nano 33 BLE ou Nano 33 BLE Sense.
*/

#include <Arduino_LSM9DS1.h>
#include <TensorFlowLite.h>
#include <tensorflow/lite/micro/all_ops_resolver.h>
#include <tensorflow/lite/micro/micro_error_reporter.h>
#include <tensorflow/lite/micro/micro_interpreter.h>
#include <tensorflow/lite/schema/schema_generated.h>
#include <tensorflow/lite/version.h>

#include "model.h"

// Seuil de détection des vibrations (en G)
const float accelerationThreshold = 1.5; 
const int numSamples = 120;

int samplesRead = numSamples;

// Variables globales pour TensorFlow Lite (Micro)
tflite::MicroErrorReporter tflErrorReporter;

tflite::AllOpsResolver tflOpsResolver;

const tflite::Model* tflModel = nullptr;
tflite::MicroInterpreter* tflInterpreter = nullptr;
TfLiteTensor* tflInputTensor = nullptr;
TfLiteTensor* tflOutputTensor = nullptr;

// Mémoire tampon pour TensorFlow Lite Micro
constexpr int tensorArenaSize = 8 * 1024;
byte tensorArena[tensorArenaSize] __attribute__((aligned(16)));

// Tableau associant l'index de la vibration à un nom
const char* VIBRATIONS[] = {
  "infinity",
  "vibration1"
};

#define NUM_VIBRATIONS (sizeof(VIBRATIONS) / sizeof(VIBRATIONS[0]))

void setup() {   
  Serial.begin(9600);
  while (!Serial);

  // Initialisation de l'IMU
  if (!IMU.begin()) {
    Serial.println("Erreur : Impossible d'initialiser l'IMU !");
    while (1);
  }

  // Affichage des taux d'échantillonnage
  Serial.print("Taux d'échantillonnage de l'accéléromètre = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println(" Hz");
  Serial.print("Taux d'échantillonnage du gyroscope = ");
  Serial.print(IMU.gyroscopeSampleRate());
  Serial.println(" Hz");

  Serial.println();

  // Chargement du modèle TensorFlow Lite
  tflModel = tflite::GetModel(model);
  if (tflModel->version() != TFLITE_SCHEMA_VERSION) {
    Serial.println("Erreur : Modèle incompatible avec TensorFlow Lite !");
    while (1);
  }

  // Création de l'interprète du modèle
  tflInterpreter = new tflite::MicroInterpreter(tflModel, tflOpsResolver, tensorArena, tensorArenaSize, &tflErrorReporter);

  // Allocation de la mémoire pour les tenseurs du modèle
  tflInterpreter->AllocateTensors();

  // Obtention des pointeurs pour les tenseurs d'entrée et de sortie
  tflInputTensor = tflInterpreter->input(0);
  tflOutputTensor = tflInterpreter->output(0);
}

void loop() {
  float aX, aY, aZ, gX, gY, gZ;

  // Attente d'une vibration significative
  while (samplesRead == numSamples) {
    if (IMU.accelerationAvailable()) {
      IMU.readAcceleration(aX, aY, aZ);
      float aSum = fabs(aX) + fabs(aY) + fabs(aZ);

      if (aSum >= accelerationThreshold) {
        samplesRead = 0;
        break;
      }
    }
  }

  // Lecture des échantillons de l'IMU
  while (samplesRead < numSamples) {
    if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {
      IMU.readAcceleration(aX, aY, aZ);
      IMU.readGyroscope(gX, gY, gZ);

      // Normalisation des données de l'IMU pour TensorFlow Lite
      tflInputTensor->data.f[samplesRead * 6 + 0] = (aX + 4.0) / 8.0;
      tflInputTensor->data.f[samplesRead * 6 + 1] = (aY + 4.0) / 8.0;
      tflInputTensor->data.f[samplesRead * 6 + 2] = (aZ + 4.0) / 8.0;
      tflInputTensor->data.f[samplesRead * 6 + 3] = (gX + 2000.0) / 4000.0;
      tflInputTensor->data.f[samplesRead * 6 + 4] = (gY + 2000.0) / 4000.0;
      tflInputTensor->data.f[samplesRead * 6 + 5] = (gZ + 2000.0) / 4000.0;

      samplesRead++;

      if (samplesRead == numSamples) {
        // Exécution de l'inférence avec TensorFlow Lite
        TfLiteStatus invokeStatus = tflInterpreter->Invoke();
        if (invokeStatus != kTfLiteOk) {
          Serial.println("Erreur : Échec de l'inférence !");
          while (1);
          return;
        }

        // Affichage des résultats de classification des vibrations
        for (int i = 0; i < NUM_VIBRATIONS; i++) {
          Serial.print(VIBRATIONS[i]);
          Serial.print(": ");
          Serial.println(tflOutputTensor->data.f[i], 6);
        }
        Serial.println();
      }
    }
  }
}
