////////////////////////
/// TP recherche IDS ///
////////////////////////

--> ( ENGLISH VERSION BELOW ) <--
Currently working on q1 and chose to work on Forced Capture

q1- Définir :
+ une fonction heuristique pour la variante classique 
+ une recherche IDS en temps limité (présentée au cours1) dans un fichier ids_player.cpp



q2b- Ajouter la variante à captures forcées (dans mybt.h et dans run_many_games.pike)



(question q1 obligatoire)
(questions q2a à q3 fixées semi-aléatoirement)

barème :
q1 = 2 pts
q2a = 2 pts
q2b = 2 pts
q2c = 3 pts
q2d = 4 pts
q2e = 4 pts

Présenter votre solution dans 3 semaines.

////////////////////////

Fichiers fournis pour ce TP :
* mybt.h définit les structures bt_piece_t, bt_move_t et bt_t
* bt_piece_t qui modélise une piece
* bt_move_t qui modélise un coup
* bt_t qui modélise le plateau et ses contraintes
* rand_player.cpp est un joueur aléaoire qui supporte le breakthrough text protocol btp
* le protocol btp permet de controler un programme pour jouer a breakthrough
* game1.txt est un exemple de fichier de commandes btp
* run_many_games.pike est un programme pike permettant de faire jouer ensemble des programmes supportant le btp
* Makefile permet de compiler le rand_player
* mk_stats.sh permet de lancer plusieurs parties, stocker les logs et les stats

Pour le moment, on posera pour contrainte de répondre le coup à jouer en 0.1 sec
Au delà de 0.1 sec, l'absence de réponse sera considérée comme un abandon

/////////////////////////


ENGLISH : 



////////////////////////
/// TP search IDS ///
////////////////////////

Currently working on q1 and chose to work on Forced Capture

q1- Define:
+ a heuristic function for the classic variant 
+ a limited-time IDS search (presented in course1) in an ids_player.cpp file



q2b- Add forced capture variant (in mybt.h and run_many_games.pike)



(mandatory question q1)
(questions q2a to q3 fixed semi-randomly)

scale:
q1 = 2 pts
q2a = 2 pts
q2b = 2 pts
q2c = 3 pts
q2d = 4 pts
q2e = 4 pts

Present your solution in 3 weeks.

////////////////////////

Files provided for this TP:
* mybt. h defines the structures bt_piece_t, bt_move_t and bt_t
* bt_piece_t that models a piece
* bt_move_t that models a move
* bt_t which models the platform and its constraints
* rand_player.cpp is a random player that supports the breakthrough text protocol btp
* the btp protocol allows to control a program to play a breakthrough
* game1.txt is an example of a btp command file
* run_many_games.pike is a pike program to play together programs supporting the building
* Makefile allows to compile the rand_player
* mk_stats.sh allows to launch multiple games, store logs and stats

For the moment, we will be forced to answer the blow to play in 0.1 sec
Beyond 0.1 sec, the lack of response will be considered an abandonment

/////////////////////////
