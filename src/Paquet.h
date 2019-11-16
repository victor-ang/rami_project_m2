#ifndef PAQUET_H
#define PAQUET_H
#include "Carte.h"
#include <vector>

// Ensemble des cartes
class Paquet {

public:
  char addPile;                     // private?
  std::vector<Carte> cartesPaquet; // private ?

  // constructeur par defaut
  Paquet() {
    cartesPaquet = {};
    addPile = 'a'; // Utilisée pour ajouter des cartes a une pile existante.
                   // p=paquet,  s=sequence, b=brelan : a utiliser dans la fonction placer sequence pour verifier si c'est une sequence valable ou non
  }

  // Constructeur avec cartes connues

  Paquet(std::vector<Carte> c) { cartesPaquet = c ; }

  void suppDerniereCarte();
  void initPaquet();
  void viderPile();
  void ajoutDevant(Carte c);
  void melangerPaquet();
  void nouveauPaquet();
  Carte piocheCarte();
  void ajouterCarte(Carte carteAjoutee);
  void afficherCartes();
  void supprimerCarte(Carte c);
  void viewerCartes();
  int taillePaquet();
  void suppCarteIndice(int ind);
  std::vector<Carte> getCartes();
};

#endif