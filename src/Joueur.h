#ifndef JOUEUR_H
#define JOUEUR_H
#include "Carte.h"
#include "Paquet.h"
#include <iostream>
#include <string>
#include <vector>

class Joueur {

private:
  std::string nom;
  int score;
  int choice;

public:
  Paquet *hand; // Main du joueur

  // constructeur par defaut : initialise le joueur
  Joueur();
  Joueur(std::string n);
  Joueur(Paquet *h, int sco, int cho);
  ~Joueur(); // destructeur

  void setNom(std::string n); // set nom du joueur
  std::string getNom();       // obtenir nom du joueur
  void setScore(int s);       // set score du joueur
  int getScore();             // obtenir score du joueur
  void setChoice(int c);      // set choix du joueur
  int getChoice();            // obtenir choix du joueur
  void premiereMain(Paquet *paquet); // Combien de cartes chaque joueur pioche au
                                      // debut de la partie = distribution des cartes
  void afficherMain();          // Afficher la main
  bool verifieCartes();         // True si aucune carte dans la main : permet de
                                // verifier si fin de la partie
  void soustraireScore(); // a la fin de la partie, si un joueur a encore des
                          // cartes en main, on soustrait a son score la somme
                          // des carte qui sont encore dans sa main
};

#endif
