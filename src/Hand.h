#ifndef HAND_H
#define HAND_H
#include"Carte.h"
#include"Paquet.h"
#include"Joueur.h"
#include<vector>


class Hand {
  

public:

  std::vector<Paquet*> pileDeCartes; // to put in private
  // constructeur par defaut (pile vide)
  Hand() {
    pileDeCartes = {};
  }
  // Constructeur avec pile donnée
  Hand(std::vector<Paquet*> pile) {
    pileDeCartes = pile;
  }
  
  void effacerPile(); // effacer la pile
  void suppDernierELement(); // supprimer le dernier element
  void ajouterPile(std::vector<Carte> cartes, Joueur* j, char ide); // Ajouter a la pile et augmenter le score du joueur
  std::vector<Paquet*> getPile(); // retourner la pile
  void setPile(std::vector<Paquet*> nouvellePile);
  void ajouterPileExistante(Carte c, int ind, Joueur* j); //ajouter une carte à une pile existante
  void afficherPiles(); // afficher toutes les piles
};

#endif