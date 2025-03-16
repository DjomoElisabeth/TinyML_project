# Classification de Deux Types de Vibrations avec Machine Learning
## 1. Introduction

Ce projet vise à créer un modèle de Machine Learning permettant de classifier deux types de vibrations à partir des données d'un capteur IMU (accéléromètre et gyroscope) intégré sur une carte Arduino Nano 33 BLE Sense. Le but est d'entraîner un modèle *TinyML qui pourra reconnaître les vibrations en temps réel directement sur la carte Arduino.


Explications sur la façon de reproduire l’expérience.
Screenshots des résultats
Description de la configuration Arduino, des librairies utilisées, etc.

##Reproduction de l'expérience
Les deux vibration s "infinity" et "heartbeat" ont été généré en utilisant une application de smartphone.









## 2. Matériel et Logiciels Utilisés

### 2.1. Matériel
- **Arduino Nano 33 BLE Sense** (avec IMU intégré)
- **Câble USB** pour la connexion au PC
- **Support de fixation** (optionnel, pour stabiliser l'IMU)

### 2.2. Logiciels et Bibliothèques
- **Arduino IDE** (avec la bibliothèque `Arduino_LSM9DS1` pour lire l'IMU)
- **Python 3.x** (avec `pyserial`, `numpy`, `pandas`, `matplotlib`)
- Google Colab pour entraîner le modèle avec TensorFlow Lite il est rapide paer rapport a Jupiter Notebook.

## 3. Collecte des Données

Les données des vibrations sont collectées via l'IMU de la carte Arduino.
Nous enregistrons les valeurs des capteurs suivantes :
- **Accélération** : `aX`, `aY`, `aZ` (en G)
- **Gyroscope** : `gX`, `gY`, `gZ` (en degrés/seconde)
Le projet contient deux fichiers de données de vibration "infinity.csv" et "Vibration1.csv".
Infinity vient d'un appli de vibration. L'avantage de ca c'est que c'est facilement reproductible. L'inconvénient c'est que la vibration n'est pas tres forte. Par conséquent il faut reduire le seuil de detection dans le code arduino pour qu'il débute l'enrégistrement. Le probleme c'est que en faisant ca le modele devient tres sensible aux petites variation de vibration et par conséquent beaucoup de "faux positif".
Vibration1 vient des vibrations d'un moulinex :) puissance 1 pour ma part.
J'ai voulu utiliser l'appli de vibration pour les deux mais les variations etait pas tres distinct et le modele n'arrivait pas à les distinguer correctement.
L'appli utilisé pour généré les données de vibration Infinity est le suivant:

![overview](VibratorApp.PNG)

### 3.1. Détection et Capture des Vibrations
Un programme Arduino envoie les données via le port série. Un script Python (`serial_to_csv.py`) les enregistre dans des fichiers `.csv`. Chaque fichier CSV correspond à un type de vibration (ex: `vibration1.csv`, `vibration2.csv`).


## 4. Entraînement du Modèle de Machine Learning
L'entraînement est réalisé sur **Google Colab** en utilisant **TensorFlow Lite**.

### 4.1. Prétraitement des Données
- Normalisation des valeurs de l'IMU.
- Division des données en **train (80%)** et **test (20%)**.

### 4.2. Architecture du Modèle
- Type : **Réseau de Neurones Profonds (MLP)**
- Entrée : 6 paramètres (aX, aY, aZ, gX, gY, gZ)
- Couches cachées : 2 couches denses (activation ReLU)
- Sortie : 2 classes (une par vibration) avec une activation `softmax`

### 4.3. Compilation et Entraînement
- Fonction de perte: Categorical Crossentropy
- **Optimiseur** : Adam
- **Nombre d'époques** : 300



## 5. Déploiement et Inférence sur Arduino

Après l'entraînement, le modèle est converti en **TensorFlow Lite pour Microcontrollers (TFLM)** et intégré à un code Arduino.

Le modèle est exécuté en temps réel sur la carte pour classifier les vibrations captées.


## 6. Résultats 
Le modèle arrive a distinguer les deux vibrations. Toutefois, il est tres sensible aux petite variation donc pour reproduire l'expérience, avant de tester une nouvelle vibration, laisser la carte rester stable pour un temps. Idéalement jusqu'a ce que rien n'apparaisse plus sur le moniteur série d'arduino.

**Inférence sous arduino**



### Améliorations possibles
-Le  réseau de neurones convolutionnel 1D (CNN 1D) optimisé pour la classification des vibrations présent de bien meilleur resultat. Toutefois, il est très sujette aux probleme de dimensionnement des données. Lorsque le modele est généré tensorflow ajoute l'option Expand_DIM qui n'est pas supporter par la carte arduino nano BLE.
-Utiliser des vibrations facilement controllable pour garantir la reproducbilité de projet surtout lorsqu'il s'agit de classer des vibrations. 


## 7. Conclusion

Ce projet démontre l'utilisation de TinyML pour classifier des vibrations en temps réel sur un microcontrôleur embarqué. Il peut être utilisé pour des applications telles que la détection d'anomalies mécaniques, la surveillance des structures ou la reconnaissance de gestes.

## 8. Ressources et Références
- [TensorFlow Lite for Microcontrollers](https://www.tensorflow.org/lite/microcontrollers)
- [Arduino Nano 33 BLE Sense](https://store.arduino.cc/products/arduino-nano-33-ble-sense)


