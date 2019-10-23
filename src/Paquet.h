#ifndef PAQUET_H
#define PAQUET_H
#include "Carte.h"
#include "Hand.h"
using namespace std;

// Ensemble des cartes
class Paquet {
  Carte carte[52];

public:
  // constructeur par defaut
  Paquet() {
    int i = 0;
    for (int coul = 0; coul < 4;
         coul++) // 0 à 3 (carreau, trèfle, coeur, pique)
      for (int val = 0; val < 13; val++) // 1 à 10 + Valet, Dame, Roi
      {
        carte[i].setvaleur(val);
        carte[i].setcouleur(coul);
        i++;
      }
  }
  void trier();

  // Melanger l'ensemble des cartes
  void melanger();

  // Couper le paquet en deux sous paquet
  void split(Hand &h1, Hand &h2);

  Carte getcarte(int pos);

  ~Paquet() { delete[] carte; } // destructeur
};

#endif