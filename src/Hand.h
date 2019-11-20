#ifndef HAND_H
#define HAND_H
#include "Carte.h"
#include "Joueur.h"
#include "Paquet.h"
#include <vector>

class Hand {
private:
  std::vector<Paquet *> pileDeCartes; // pile de cartes

public:
  // constructeur par defaut (pile vide)
  Hand();
  Hand(std::vector<Paquet *> pile);

  void suppDernierELement(); // supprimer le dernier element
  void ajouterPile(std::vector<Carte> cartes, Joueur *j); // Ajouter a la pile et augmenter le score du joueur
  std::vector<Paquet *> getPile(); // retourner la pile
  void ajouterPileExistante(Carte c, int ind, Joueur *j); // ajouter une carte à une pile existante
  void afficherPiles(); // afficher toutes les piles déja posées sur la table
};

#endif
