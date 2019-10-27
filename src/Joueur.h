#ifndef JOUEUR_H
#define JOUEUR_H
#include"Paquet.h"
#include "Carte.h"
#include <string>
#include<iostream>
#include<vector>

class Joueur {
  std::string nom;
  Paquet *hand;
  int score;

public:
  // constructeur par defaut : initialise le joueur
  Joueur() {
    this->hand ={};
    this->score = 0; // score du joeur à 0 au début
  }
  Joueur(std::string n){
    nom = n;
    hand = new Paquet(); //ajouter destructeur !!
  }
  Joueur(Paquet* h, int sco){
    hand = h;
    score = sco;
  }
  Paquet* getMain();  // Retourne la main du joueur
  void afficherNom(); // Afficher le nom du joueur
  void premiereMain(Paquet * paquet); // Combien de cartes chaque joueur pioche a chaque nouveau jeu
  void afficherMain(); // Afficher la main
  bool verifieCartes(); // True si aucune carte dans la main
  void soustraireScore();  //soustrait le score à la fin du jeu (car le score est augmente des qu'un joueur pioche une carte)
};

#endif