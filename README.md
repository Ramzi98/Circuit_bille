# Circuit_bille
- Un jeu implémenter en OpenGL avec la bibliothèque GLUT
# Descriptif des techniques employées pour réaliser le travail :
- Utilisation de la Modélisation à base d'ensembles de facettes pour la
réalisation des trois étages du circuit , et des courbes de bézier pour les relier
- On a réalisé 3 étages et un ascenseur et deux relie entre les trois étages.
- Réalisation de déplacement de la balle sur le circuit et la remonte de la balle à
l’étage initial à l’aide de l'ascenseur.
- Pour le virage de l'étage 2 nous avons calculé les vertex à l'aide des sin
cosinus et tangente afin de créer un demi cercle.
- Pour la vitesse nous avons fait une estimation dans le but de la augmenter
dans les descentes et de garder une vitesse constante dans les circuits droits,
nous avons mis 3 variable vitesse 1, vitesse 2 et vitesse 3 qui permettent de
modifier la vitesse dans les différentes parties du circuit .
- Nous avons conçu un ascenseur afin de faire monter la balle depuis l'étage 1
(l’étage le plus bas vers l’étage le plus haut) pour que la balle se déplace
dans un circuit fermé.
- Pour les caméras on a implémenté 3 type de caméras :
  - **a. Une caméra Fixe :** une caméra fixée au-dessus du circuit pour voir
tout le circuit.
  - **b. Une caméra 3éme personne :** qui suit la balle pendant son parcour
dans la position de 3eme personne
  - **c. Une caméra 1er personne :** qui suit la balle dans le circuit et qui se
situe avant la balle dans le front de la balle.
- Réalisation deux modes d'affichage : affichage en fil de fer et mode
d'affichage par facettes.

# Lancement du projet :
- Importer le projet dans Visual Studio 2019.
- Exécuter le projet en cliquant sur le Bouton « Débogueur Windows Local »

# Les contrôles Clavier :
- Button “k”: Changement de la couleur du Fond (le blanc , gris et noir) .
- Button “f”: le passage en "full screen" et le retour en mode fenêtré normal.
- Button “F1 F2 F3” : gestion des lumières
- Button “C” : contrôle de la caméra .
- Button “espace” : gestion des textures.
- Button “entrée” : gestion des mouvements de la balle (activer/désactiver l'animation).
- Button “l” :Allumer et éteindre les lumières.
- Button “v” : switcher entre mode d'affichage fil de fer et mode d'affichage par facettes.
