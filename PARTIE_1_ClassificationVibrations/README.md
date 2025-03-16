## Objectif du projet
L'objectif du projet et de détecter et classifier différents types de vibrations.

![overview](doc/VibrationPartie1.PNG)

#  Classification des Vibrations avec TinyML et Arduino Nano 33 BLE

## Présentation du projet
Ce projet utilise un IMU (Inertial Measurement Unit) intégré sur la carte Arduino Nano 33 BLE Sense pour détecter et classifier différents types de vibrations en utilisant TinyML et TensorFlow Lite.

Les données sont collectées via l’accéléromètre et le gyroscope, stockées dans des fichiers CSV, puis utilisées pour entraîner un modèle de machine learning embarqué.

📌 Objectifs du projet :
- Récupérer les signaux de vibrations avec l'IMU.
- Stocker et étiqueter ces signaux sous forme de fichiers CSV.
- Entraîner un modèle TinyML pour la reconnaissance des vibrations sur Google Colab avec TensorFlow Lite.
- Déployer le modèle sur Arduino Nano 33 BLE Sense et effectuer une inférence en temps réel.


## Matériel & Logiciels requis
###  Matériel
-  Arduino Nano 33 BLE Sense
- Capteur IMU intégré (LSM9DS1)
- Câble USB pour la communication série

###  Logiciels et Bibliothèques
#### Sur Arduino
- Arduino IDE ([Télécharger ici](https://www.arduino.cc/en/software))
- Bibliothèque Arduino_LSM9DS1 (pour lire les données de l’IMU)
- Biblithèque Harvard_tinyMLx

#### Sur PC / Google Colab
- Python 3.x avec pyserial, pandas, numpy, tensorflow
- Google Colab pour l'entraînement du modèle
- TensorFlow Lite pour TinyML


###  Fonctionnement :
1. Connexion au port série pour lire les données envoyées par l’IMU.
2. Enregistrement des échantillons dans un fichier `.csv` avec un étiquetage manuel des vibrations.
3. Un fichier CSV par type de vibration (ex: `vibration1.csv`, `infinity.csv`...).

## Comment étiqueter les données ?
- Modifier "le nom du fichier CSV" dans le code python avant l’enregistrement.
- Exemple : `"vibration1.csv"` pour enregistrer des vibrations dues à la marche.

## 3. Entraînement du Modèle TinyML
L'entraînement du modèle se fait sur Google Colab en utilisant TensorFlow et TensorFlow Lite.

**Processus** :
1. Charger les fichiers CSV dans Google Colab.
2. Prétraitement des données (normalisation, extraction de features).
3. Création et entraînement du modèle avec TensorFlow.
4. Conversion du modèle en TensorFlow Lite (TFLite) pour une utilisation sur Arduino.

## 4. Déploiement et Inférence sur Arduino
Une fois le modèle TensorFlow Lite entraîné, il est déployé sur l'Arduino Nano 33 BLE pour faire des prédictions en temps réel.

 **Étapes du déploiement** :
1. Convertir le modèle en TFLite pour Microcontrollers.
2. Intégrer le modèle dans un sketch Arduino C++.
3. Compiler et téléverser le code sur l’**Arduino Nano 33 BLE.
4. Tester la reconnaissance des vibrations en temps réel.


## Liens utiles
-  [Documentation TensorFlow Lite](https://www.tensorflow.org/lite/microcontrollers)
-  [Edge Impulse - AutoML pour TinyML](https://www.edgeimpulse.com/)
-  [Arduino Nano 33 BLE Sense](https://store.arduino.cc/products/arduino-nano-33-ble-sense)


