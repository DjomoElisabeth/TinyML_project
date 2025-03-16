# TinyML Project

##  Présentation Générale
Ce projet met en œuvre **Edge Impulse** et **Arduino Nano 33 BLE Sense** pour la classification et l'inférence de signaux et d'images. Il est structuré en deux parties principales :
1. **Classification de Vibrations** à l'aide de l'IMU intégré.
2. **Classification et Comptage de Composants Électroniques** via une caméra et un traitement embarqué.

L'objectif est de capturer des données, entraîner un modèle de Machine Learning, et exécuter l'inférence en temps réel sur un microcontrôleur.

---

##  Structure du Repository

```
TinyML_project/
│── README.md  # Présentation générale du projet
│
│── PARTIE_1_ClassificationVibrations/
│   ├── README.md  # Explications spécifiques à la partie 1
│   ├── 1-DataGeneration_Arduino/
│   │   ├── data_generation.ino  # Code Arduino pour l'acquisition des données IMU
│   │
│   ├── 2-Training/
│   │   ├── dataset/  # Données d'entraînement collectées via Arduino
│   │   ├── notebooks/
│   │   │   ├── training_vibrations.ipynb  # Notebook Jupyter pour l'entraînement
│   │   ├── models/
│   │       ├── Modèle(s) entraînés (.tflite, .etx)
│   │
│   ├── 3-Inference_Arduino/
│   │   ├── inference_vibrations.ino  # Code Arduino pour l'inférence
│   │   ├── documentation.md  # Explications et schémas
│
│── PARTIE_2_ClassificationComposants/
│   ├── README.md  # Explications spécifiques à la partie 2
│   ├── 1-EdgeImpulse/
│   │   ├── link_to_edge_impulse.md  # Lien vers le projet Edge Impulse
│   │   ├── instructions.md  # Instructions de reproduction
│   │
│   ├── 2-ArduinoCamera/
│   │   ├── arduino_camera_classification.ino  # Code Arduino pour la capture & classification d’images
│   │
│   ├── 3-NodeRED/
│   │   ├── flows.json  # Export du flux Node-RED
│   │   ├── dashboard/  # Configuration et affichage des résultats
│   │
│   ├── doc/
│       ├── documentation.md  # Explications détaillées et schémas
```

---

##  Déroulement du Projet

###  **Partie 1 : Classification de Vibrations**
1. **Acquisition des données** IMU avec l'**Arduino Nano 33 BLE Sense**.
2. **Entraînement d’un modèle de Machine Learning** sur Google Colab.
3. **Déploiement sur Arduino** pour effectuer l’inférence en temps réel.

###  **Partie 2 : Classification et Comptage de Composants**
1. **Capture d’images** via une caméra **OV7675** connectée à Arduino.
2. **Entraînement d’un modèle de reconnaissance de composants électronique** avec Edge Impulse.
3. **Transmission des résultats** vers **Node-RED** pour l'affichage et le comptage.

---

##  Technologies et Outils Utilisés
- **Arduino Nano 33 BLE Sense** (capteur IMU intégré)
- **Caméra OV7670** pour l’acquisition d’images
- **Edge Impulse** pour l'entraînement des modèles TinyML
- **Arduino IDE** pour la programmation
- **Google colab** pour l'analyse et l'entraînement des modèles
- **Node-RED** pour la visualisation des résultats

---

##  Documentation et Instructions
- Chaque partie du projet contient un **README.md** avec les détails spécifiques.
- La documentation complète se trouve dans le dossier **doc/**.


##  Installation et Exécution
### 1 **Pré-requis**
- Installer **Arduino IDE** et les bibliothèques nécessaires
- Installer **Edge Impulse CLI**
  ```sh
  npm install -g edge-impulse-cli
  ```
- Avoir **Node.js** pour exécuter Node-RED

### 2 **Utilisation**
####  **Exécuter l'inférence sur Arduino**
1. Connecter la carte **Arduino Nano 33 BLE Sense**.
2. Ouvrir **Arduino IDE** et téléverser `inference_vibrations.ino` ou `arduino_camera_classification.ino`.
3. Lancer le **Moniteur Série** pour observer les résultats en temps réel.

####  **Visualiser les résultats sur Node-RED**
1. Importer `flows.json` dans Node-RED.
2. Démarrer Node-RED et ouvrir le tableau de bord pour afficher les classifications.

---

## Améliorations Possibles
- Ajouter plus de données pour améliorer la robustesse des modèles.
- Optimiser la gestion de la mémoire pour intégrer le modèle sur la carte.

---
