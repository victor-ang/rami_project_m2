#ifndef JOUEUR_H
#define JOUEUR_H
#include "Carte.h"
#include "Paquet.h"
#include <iostream>
#include <string>
#include <vector>

class Joueur {

public:
  // to put in private
  std::string nom;
  Paquet *hand;
  int score;
  //

  // constructeur par defaut : initialise le joueur
  Joueur() {
    this->hand = {};
    this->score = 0; // score du joeur à 0 au début
  }
  Joueur(std::string n) {
    nom = n;
    hand = new Paquet(); // ajouter destructeur !!
  }
  Joueur(Paquet *h, int sco) {
    hand = h;
    score = sco;
  }


  void premiereMain(Paquet *paquet); // Combien de cartes chaque joueur pioche a
                                     // chaque nouveau jeu
  void afficherMain();               // Afficher la main
  bool verifieCartes();              // True si aucune carte dans la main
  void soustraireScore(); // soustrait le score à la fin du jeu (car le score
                          // est augmente des qu'un joueur pioche une carte)
};

#endif
