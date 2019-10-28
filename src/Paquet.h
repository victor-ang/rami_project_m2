#ifndef PAQUET_H
#define PAQUET_H
#include "Carte.h"
#include<vector>

// Ensemble des cartes
class Paquet {

public:

  char addPile; // private?
  vector<Paquet> cartesPaquet; // private ?
  

  // constructeur par defaut
  Paquet() {
    cartesPaquet = {};
    addPile = 'd'; // Utilisée pour ajouter des cartes a une pile existante. p=paquet,  s=sequence, m=meld
  }

  // Constructeur avec cartes connues

  Paquet(vector<Carte> c){
    cartesPaquet = c;
  }

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
 vector<Carte> getCartes();
};

#endif