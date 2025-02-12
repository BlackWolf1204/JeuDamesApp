# JeuDamesApp

## 1.	Développement ##

Inclure les différentes bibliothèques dans le projet mais faire attention à n’inclure que les -d pour la version debug et les mêmes sans -d pour la version release (sinon possibilité de bug si tout est inclus comme le font ne pouvant pas être chargé).

Pour contrôler le robot en dehors de l’application, télécharger DobotStudio (DOBOT Magician) v1.9.4 – Jan 10, 2022 sur le site [Search for the Right Manual | Dobot Download Center.](https://www.dobot-robots.com/service/download-center)
Sa documentation est sur le lien suivant : [DOBOT MAGICIAN ROBOTICS USER MANUAL | ManualsLib](https://www.manualslib.com/manual/1554643/Dobot-Dobot-Magician.html)
La documentation de l’API se trouve sur celui-ci : [dobot-api-en.pdf](https://ecksteinimg.de/Datasheet/Dobot/dobot-api-en.pdf)

## 2.	Utilisation ##

Au démarrage de l’application, le robot ne sera pas connecté, entrer dans la barre d’input en haut à gauche le port sur lequel se trouve les robot (regarder dans gestionnaire des périphériques). Attendre que l’indicateur lumineux du robot passe au vert avant de la connecter à l’application. 
Une fois la connexion faite, le robot effectuera une phase d’initialisation (fonction home du robot) puis se positionnera en position de lecture du plateau. 
Pour placer les différents éléments (plateau, dames, poubelle), une fonction de calibrage est disponible en bas à gauche. A chaque appuie sur le bouton « Calibrage », le robot se mettra au-dessus de l’une de ces posi-tions dans l’ordre indiqué : 
-	la case en bas à gauche du robot
-	la case en haut à droite du robot
-	la poubelle
-	la dame en bas à droite du robot
-	la dame en haut à gauche
-	position de lecture
Une fois la position de lecture atteinte, la phase de calibrage est terminée.

Dans « Image Details », quatre images représentent les phases de traitement de l’image et l’image originale possède un quadrillage pour cali-brer la caméra sur le scratch si nécessaire pour faire correspondre le qua-drillage et les cases du plateau (assez tolérant sur la correspondance). Si jamais un pion est mal détecté, vérifier sur l’image en bas à droite que chaque pion est un cercle fermé, si ce n’est pas le cas, bouger légèrement le pion pour qu’un de ses bords ne soit pas confondu avec l’arrière-plan.

Dans « Jouer », un bouton réinitialiser permet de réinitialiser l’état du plateau et si le premier coup du robot a été joué. Attention : le premier coup du robot est recherché par rapport un nombre défini d’état du plateau, si le plateau n’est pas dans l’un de ces états (début de partie, état initial avec un pion du joueur déplacé) le robot ne jouera pas ou l’application se fermera. Le bouton permet de recharger les emplacements de dame. Le bouton jouer indique au robot que c’est à son tour de jouer. Si le joueur ou le robot gagne la partie, un message de victoire ou de défaite du joueur apparaitra, un simple clic sur l’écran le fera disparaître.

Quand le robot joue, entre chaque déplacement de pion, il se passe-ra toujours par une même position, c’est une position de transition car cer-tains chemins de déplacement entre deux positions est impossible pour le robot (ex : une case très proche du robot à la position de lecture). Cette position de transition permet d’éviter une erreur du robot.
