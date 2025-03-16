## 2. Acquisition des Images
Les images des composants électroniques sont capturées directement à l'aide d'Edge Impulse via l'interface de capture d'image.
Pour ce faire, on procède comme suit:
2. Connexion de la caméra OV7675 à l'Arduino Nano 33 BLE Sense.
3. Prise de photos en direct dans l'onglet "Data acquisition" en cliquant sur "start sampling".

## 3. Étiquetage des Données
1. Accès à **"Labeling queue"** dans Edge Impulse.
2. Attribution d'un label à chaque image selon le type de composant.
3. Vérification et correction des labels pour garantir une classification optimale.

## 4. Conception du Modèle de Machine Learning
Un modèle de reconnaissance d'images est conçu dans l'onglet **Impulse Design**.
Pour construire le modèle on procède comme suit:

1. Ajout d'un **bloc de traitement d'images**  ce projet a été réaliser avec "image".
2. Sélection d'un modèle de type Transfer Learning pour l'entraînement. Ici, "Objet detection"
3. Enregistrement et validation de l'architecture du modèle.

## 5. Entraînement et Optimisation du Modèle
Une fois le modèle configuré, l'entraînement est lancé dans **Model training**.

1. Division des données en **train (80%)** et **test (20%)**.
2. Réglage des paramètres d'entraînement :
   - **Nombre d'époques** : 50
   - **Taux d'apprentissage** : 0.001
   - **Taille du batch** : 16
3. Exécution de l'entraînement et analyse des performances :
   - **Précision du modèle** (doit être supérieure à 85%).
   - **Confusion matrix** pour vérifier les erreurs de classification.

---

## 6. Déploiement et Intégration sur Arduino

Le modèle final est exporté et intégré dans un programme Arduino.

1. Génération de la **bibliothèque C++** depuis Edge Impulse (onglet "Deployment").
2. Importation du fichier **.zip** dans **Arduino IDE**.
3. Implémentation du modèle dans un sketch Arduino :
   - Lecture des images de la caméra.
   - Exécution de l'inférence pour classifier le composant.
   - Transmission des résultats via **Bluetooth**.

---

## 7. Affichage des Résultats sur Node-RED

Les données de classification sont envoyées à un **dashboard Node-RED** en temps réel.

1. Connexion de l'Arduino à **Node-RED** via Bluetooth.
2. Création d'un **flux Node-RED** pour recevoir et afficher les données.
3. Ajout de **widgets** pour visualiser le comptage des composants.

---

## 8. Résultats et Améliorations

Le système est capable de **distinguer et compter les composants électroniques** avec une précision d'environ 90%. Cependant, des améliorations sont possibles :

- **Augmentation du dataset** pour réduire les erreurs de classification.
- **Optimisation de la caméra** (meilleure résolution et gestion de la lumière).
- **Utilisation d'un microcontrôleur plus puissant** pour une inférence plus rapide.



## 9. Conclusion

Le projet met en œuvre Edge Impulse et Arduino pour réaliser un **système intelligent de reconnaissance et de comptage de composants électroniques**. Ce système peut être utilisé en **industrie** pour l'automatisation du tri et du suivi des stocks en temps réel.


