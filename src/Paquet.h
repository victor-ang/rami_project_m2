#ifndef PAQUET_H
#define PAQUET_H
#include "Carte.h"
#include <vector>

// Ensemble des cartes
class Paquet {

public:
  char addPile;                    // private?
  std::vector<Carte> cartesPaquet; // private ?

  // constructeur par defaut
  Paquet() {
    cartesPaquet = {};
    addPile = 'p'; // Utilisée pour ajouter des cartes a une pile existante sur
                   // la table. p=paquet,  s=sequence, b=brelan : a utiliser
                   // dans la fonction placer sequence pour verifier si c'est
                   // une sequence valable ou non (avec la carte ajoutée)
  }

  // Constructeur avec cartes connues

  Paquet(std::vector<Carte> c) { cartesPaquet = c; }

  void suppDerniereCarte();
  void initPaquet();
  void viderPile();
  void ajoutDevant(Carte c);
  void melangerPaquet();
  void nouveauPaquet();
  Carte piocheCarte();
  void ajouterCarte(Carte carteAjoutee);
  void supprimerCarte(Carte c);
  void viewerCartes();
  int taillePaquet();
  std::vector<Carte> getCartes();
};

#endif
