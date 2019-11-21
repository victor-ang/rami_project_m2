#ifndef PAQUET_H
#define PAQUET_H
#include "Carte.h"
#include <vector>

// Ensemble des cartes
class Paquet : public Carte {

private:
  std::vector<Carte> cartesPaquet;

public:
  // constructeur par defaut
  Paquet();
  // Constructeur avec cartes connues
  Paquet(std::vector<Carte> c);

  void suppDerniereCarte();              // supprime derniere carte
  void initPaquet();                     // initialisation paquet
  void viderPile();                      // vider une pile de cartes
  void ajoutDevant(Carte c);             // ajouter à l'avant d'une pile
  void melangerPaquet();                 // melanger paquet
  void nouveauPaquet();                  // nouveau paquet
  Carte piocheCarte();                   // piocher une carte
  void ajouterCarte(Carte carteAjoutee); // ajouter une carte
  void supprimerCarte(Carte c);          // supprimer une carte
  void viewerCartes();                   // affichage cartes terminal
  int taillePaquet();                    // taille du paquet
  std::vector<Carte> getCartes();        // getter cartes
  int nbMelangesAleatoires();            // nombre de mélanges des cartes
};

#endif
