/*
  Capture IMU (Inertial Measurement Unit)
  Ce programme utilise l’IMU  intégré pour lire les données
  d’accélération et de gyroscope du module.

  Lorsque l’IMU détecte un mouvement significatif (en fonction de la valeur du Threshold) , il commence à collecter 
  les données et les affiche dans le Moniteur Série.

  Vous pouvez également utiliser le "Serial Plotter" pour visualiser les données sous forme de graphique.

  Matériel requis :
  - Carte Arduino Nano 33 BLE ou Arduino Nano 33 BLE Sense.
*/

#include <Arduino_LSM9DS1.h> // Inclut la bibliothèque pour le capteur IMU

const float accelerationThreshold = 1.5; // Seuil de mouvement significatif (en G)
const int numSamples = 120; // Nombre d’échantillons à capturer

int samplesRead = numSamples; // Variable pour suivre les échantillons lus

void setup() {
  Serial.begin(9600); // Initialise la communication série avec une vitesse de 9600 bauds
  while (!Serial); // Attendre que le Moniteur Série soit prêt 

  if (!IMU.begin()) { // Vérifie si le capteur IMU s'initialise correctement
    Serial.println("Échec de l'initialisation de l'IMU !");
    while (1); // Boucle infinie en cas d’échec
  }

  // Affiche l'entête des données en format CSV (valeurs séparées par des virgules)
  Serial.println("aX,aY,aZ,gX,gY,gZ");
}

void loop() {
  float aX, aY, aZ, gX, gY, gZ; // Variables pour stocker les valeurs des capteurs

  // Attendre un mouvement significatif avant de commencer la capture des données
  while (samplesRead == numSamples) { // Si tous les échantillons ont été lus, on attend un nouveau mouvement
    if (IMU.accelerationAvailable()) { // Vérifie si des données d’accélération sont disponibles
      IMU.readAcceleration(aX, aY, aZ); // Lit les valeurs d’accélération

      // Calcule la somme des valeurs absolues des axes X, Y et Z
      float aSum = fabs(aX) + fabs(aY) + fabs(aZ);

      // Vérifie si la somme dépasse le seuil défini
      if (aSum >= accelerationThreshold) {
        samplesRead = 0; // Réinitialise le compteur d'échantillons lus
        break; // Sort de la boucle pour commencer la capture
      }
    }
  }

  // Capturer les échantillons de l’IMU après détection du mouvement
  while (samplesRead < numSamples) { // Tant que nous n’avons pas collecté tous les échantillons
    if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) { // Vérifie si les données sont disponibles
      IMU.readAcceleration(aX, aY, aZ); // Lit l’accélération
      IMU.readGyroscope(gX, gY, gZ); // Lit les valeurs du gyroscope

      samplesRead++; // Incrémente le compteur d'échantillons lus

      // Affiche les valeurs lues en format CSV
      Serial.print(aX, 3); Serial.print(',');
      Serial.print(aY, 3); Serial.print(',');
      Serial.print(aZ, 3); Serial.print(',');
      Serial.print(gX, 3); Serial.print(',');
      Serial.print(gY, 3); Serial.print(',');
      Serial.print(gZ, 3);
      Serial.println(); // Passe à la ligne suivante

      if (samplesRead == numSamples) {
        Serial.println(); // Ajoute une ligne vide à la fin de la capture
      }
    }
  }
}

