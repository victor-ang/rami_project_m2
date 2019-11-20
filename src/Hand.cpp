#include "Hand.h"
#include <algorithm>
#include <iostream>
#include <vector>

Hand::Hand() { pileDeCartes = {}; } // Main d'un joueur

// Constructeur avec pile donnée
Hand::Hand(std::vector<Paquet *> pile) { pileDeCartes = pile; }

// Supprimer le dernier element
void Hand::suppDernierELement() {
  this->pileDeCartes.pop_back();
} // utilisation de la fonction pop_back de vector

// Ajouter a la pile et augmenter le score du joueur
void Hand::ajouterPile(std::vector<Carte> cartes, Joueur *j) {
  sort(cartes.begin(), cartes.end()); // tri du vecteur
  Paquet *ajout = new Paquet();       // nouveau paquet (pile)

  // Ajout des cartes à la pile
  for (int i = 0; i < cartes.size(); i++) {
    ajout->ajouterCarte(cartes.at(i));
  }
  this->pileDeCartes.push_back(ajout); // ajout
  // Modif du score
  int somme = 0; // calcul du score
  for (int i = 0; i < cartes.size(); i++) {
    if (cartes.at(i).getValeur() <= 10) { // cartes de 1 a 10
      somme += cartes.at(i).getValeur();
    } else { // si valet, dame, roi
      somme += 10;
    }
  }
  j->setScore(j->getScore() + somme); // Màj du score
}

// Retourner la pile
std::vector<Paquet *> Hand::getPile() { return pileDeCartes; }

// ajouter une carte à une pile existante
void Hand::ajouterPileExistante(Carte c, int ind, Joueur *j) {
  if (c < pileDeCartes.at(ind)->getCartes().at(0)) { // si carte plus petite que la premiere de la pile, on la
                                                    // met devant
    this->pileDeCartes.at(ind)->ajoutDevant(c);
  } else {
    this->pileDeCartes.at(ind)->ajouterCarte(c); // Sinon, apres
  }
  int somme = 0;             // score du joueur
  if (c.getValeur() <= 10) { // si cartes de 1 a 10
    somme += c.getValeur();
  } else { // valet, dame, roi
    somme += 10;
  }
  j->setScore(j->getScore() + somme); // màj du score
}

// afficher toutes les piles posées sur la table
void Hand::afficherPiles() {
  for (int i = 0; i < pileDeCartes.size(); i++) {
    std::cout << "Pile #" << (i + 1) << std::endl;
    pileDeCartes[i]->viewerCartes();
  }
}
