"""
Programme de collecte de données IMU via un port série et enregistre dans un fichier CSV.

 Description :
- Ce programme lit les données envoyées par un capteur IMU connecté à un port série.
- Il écoute le port série*, récupère les valeurs de l'accéléromètre et du gyroscope.
- Les données sont stockées dans un fichier CSV (`vibration1.csv`).
- Il enregistre 120 échantillons par vibration, puis attend un nouveau vibration.
- À chaque nouveau vibration détectée, il affiche le nombre total de vibration enregistrés.
- Le programme s'arrête lorsque l'utilisateur appuie sur Ctrl+C. """


import serial  # Importation de la bibliothèque pour la communication série
import csv  # Importation de la bibliothèque pour l'écriture des fichiers CSV

#  Configuration du port série
SERIAL_PORT = 'COM8'  #  Modifier en fonction de ton port série 
BAUD_RATE = 9600  # Débit en bauds de la communication série
numSamples = 120  # Nombre d'échantillons à collecter pour chaque geste
Number_of_vibration = 0  # Compteur de vibration enregistrés

#  Ouverture du port série et du fichier CSV pour l'enregistrement
with serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1) as ser:  # Ouvre la connexion série
    with open('vibration1.csv', 'w', newline='') as csvfile:  # Ouvre le fichier CSV en mode écriture
        writer = csv.writer(csvfile)  # Crée un objet pour écrire dans le fichier CSV

        #  Écriture de l'en-tête du fichier CSV
        writer.writerow(['aX', 'aY', 'aZ', 'gX', 'gY', 'gZ'])

        print(" Début de la collecte de données... (Appuie sur Ctrl+C pour arrêter)")

        samples_collected = 0  # Compteur du nombre d'échantillons écrits dans le CSV

        try:
            #  Boucle infinie pour lire et enregistrer les données en continu
            while True:
                line = ser.readline().decode('utf-8').strip()  # Lit une ligne depuis le port série et supprime les espaces

                #  Vérification si la ligne est valide et n'est pas l'en-tête
                if line and not line.startswith('aX,aY,aZ,gX,gY,gZ'):
                    values = line.split(',')  # Découpe la ligne en une liste de valeurs
                    if len(values) == 6:  # Vérifie que la ligne contient bien 6 valeurs (X, Y, Z pour accéléromètre + gyroscope)
                        writer.writerow(values)  #  Écrit la ligne dans le fichier CSV
                        samples_collected += 1  # Incrémente le compteur d'échantillons

                        #  Une fois que 120 échantillons sont collectés, afficher un message et passer au geste suivant
                        if samples_collected == numSamples:
                            print(f" {numSamples} échantillons ont été enregistrés.")
                            print("Collecte terminée pour une vibration.")
                            samples_collected = 0  # Réinitialise le compteur
                            Number_of_vibration+= 1  # Incrémente le nombre de vibrations enregistrés
                            print(f" Nombre total de vibrations enregistrés : {Number_of_vibrations}")
                    else:
                        print(f" Format de ligne inattendu : {line}")  # Alerte si la ligne ne contient pas 6 valeurs
                elif line.startswith('aX,aY,aZ,gX,gY,gZ'):  # Ignore la ligne d’en-tête envoyée par l’Arduino
                    print(" En-tête détecté, ignoré...")

        except KeyboardInterrupt:
            #  Lorsque l'utilisateur appuie sur Ctrl+C, on arrête proprement l'enregistrement
            print(" Collecte de données arrêtée par l'utilisateur.")

print(" Collecte terminée. Les données ont été enregistrées dans 'vibration1.csv'.")
