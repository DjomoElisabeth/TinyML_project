## 2 Acquisition des Images
Les images des composants electroniques sont capturees directement a l aide d Edge Impulse via l interface de capture d image.
Pour ce faire on procede comme suit
2 Connexion de la camera OV7675 a l Arduino Nano 33 BLE Sense
3 Prise de photos en direct dans l onglet Data acquisition en cliquant sur start sampling

## 3 Etiquetage des Donnees
1 Acces a Labeling queue dans Edge Impulse
2 Attribution d un label a chaque image selon le type de composant
3 Verification et correction des labels pour garantir une classification optimale

## 4 Conception du Modele de Machine Learning
Un modele de reconnaissance d images est concu dans l onglet Impulse Design
Pour construire le modele on procede comme suit

1 Ajout d un bloc de traitement d images  ce projet a ete realise avec image
2 Selection d un modele de type Transfer Learning pour l entrainement Ici Objet detection
3 Enregistrement et validation de l architecture du modele

Deux sous onglets vont apparaitre qui permettent de voir l effet de l extraction des features par ces algorithmes
Sous l'onglet "image" et l'onglet "Objet Detection"

**1. Onglet Imange**
![overview](edge_image.PNG]

Le Feature Explorer montre une separation correcte entre les classes mais indique un chevauchement entre BACKGROUND et LED source potentielle d erreurs de classification Tandis que la classe B7S est bien regroupee les similarites entre les donnees de BACKGROUND et LED compliquent la distinction entre ces categories Pour ameliorer la classification il est recommande de multiplier les echantillons distincts de reduire les variations au sein des classes et d optimiser l extraction des caracteristiques Une autre solution serait d explorer une nouvelle methode de reduction de dimensionalite ou de recourir a un modele plus avance tel qu un CNN 1D afin de mieux separer les classes

Le modele avec un F1 Score de 833 montre de bonnes performances globales bien qu il souffre d une confusion notable entre B7S et BACKGROUND 125 Ce probleme est exacerbe par la presence de deux labels BACKGROUND dont l un ajoute
