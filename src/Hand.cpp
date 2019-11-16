#include "Hand.h"
#include <iostream>
#include <vector>
#include<algorithm>

// effacer la pile
void Hand::effacerPile() { pileDeCartes = {}; }

// supprimer le dernier element
void Hand::suppDernierELement() { this->pileDeCartes.pop_back(); }

// Ajouter a la pile et augmenter le score du joueur
void Hand::ajouterPile(std::vector<Carte> cartes, Joueur *j, char ide) {
  sort(cartes.begin(), cartes.end()); // tri du vecteur
  Paquet *ajout = new Paquet();

  // ajout des cartes à la pile
  for (int i = 0; i < cartes.size(); i++) {
    ajout->ajouterCarte(cartes.at(i));
  }
    ajout->addPile = ide;
  this->pileDeCartes.push_back(ajout);
  // modif du score
  int somme = 0;
  for (int i = 0; i < cartes.size(); i++) {
    if (cartes.at(i).getValeur() == 1) { // si AS
      somme += 1;
    } else if (cartes.at(i).getValeur() <= 10) { // cartes de 2 a 10
      somme += cartes.at(i).getValeur();
    } else {
      somme += 10;
    }
  }
  j->score = (j->score + somme); // ATTENTION : SCORE EST PRIVE! (hand aussi)
}

// retourner la pile
std::vector<Paquet *> Hand::getPile() { return pileDeCartes; }

//void Hand::setPile(std::vector<Paquet *> nouvellePile) {
//  pileDeCartes = nouvellePile;
//}

// ajouter une carte à une pile existante
void Hand::ajouterPileExistante(Carte c, int ind, Joueur *j) {
  if (c < pileDeCartes.at(ind)->getCartes().at(0)){ //si carte plus petite que la premiere de la pile, on la met devant
    this->pileDeCartes.at(ind)->ajoutDevant(c);
  }
  else {
    this->pileDeCartes.at(ind)->ajouterCarte(c); // Sinon, apres
  }
  int somme = 0;
  if (c.getValeur()==1){ //si AS
    somme +=1;
  }
  else if (c.getValeur() <= 10){ // si cartes de 2 a 10
  somme += c.getValeur();
  }
  else{ // valet, dame, roi
    somme +=10;
  }
  j->score += somme; // ATTENTION : SCORE PRIVE
}

// afficher toutes les piles
void Hand::afficherPiles() {
  for (int i = 0; i < pileDeCartes.size(); i++) {
    std::cout << "Pile #" << (i + 1) << std::endl;
    pileDeCartes[i]->viewerCartes();
  }
}
