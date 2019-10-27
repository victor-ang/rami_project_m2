#ifndef HAND_H
#define HAND_H
#include"Carte.h"
#include"Paquet.h"
#include"Joueur.h"
#include<vector>


class Hand {
  vector<Paquet*> pileDeCartes;

public:
  // constructeur par defaut (pile vide)
  Hand() {
    pileDeCartes = {};
  }
  // Constructeur avec pile donnée
  Hand(vector<Paquet*> pile) {
    pileDeCartes = pile;
  }
  
  void effacerPile(); // effacer la pile
  void suppDernierELement(); // supprimer le dernier element
  void ajouterPile(vector<Carte> cartes, Joueur* j); // Ajouter a la pile et augmenter le score du joueur
  vector<Paquet*> getPile(); // retourner la pile
  void setPile(vector<Paquet*> nouvellePile);
  void ajouterPileExistante(Carte c, int ind, Joueur* j); //ajouter une carte à une pile existante
  void afficherPiles(); // afficher toutes les piles
};

#endif