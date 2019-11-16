#ifndef SCENARIO_H
#define SCENARIO_H
#include "Carte.h"
#include "Hand.h"
#include "Joueur.h"
#include "Paquet.h"
#include <iostream>
#include <vector>

class Scenario {
public:
  Hand *cartesEnJeu;
  Joueur *joueur1;
  Joueur *joueur2;
  int modifRegles;
  Paquet *pioche;
  Paquet *defausse;

  Scenario(Joueur *j1, Joueur *j2, Paquet *pilePioche, Paquet *pileDefausse) {
    joueur1 = j1;
    joueur2 = j2;
    pioche = pilePioche;
    defausse = pileDefausse;
    cartesEnJeu = new Hand(); // ajouter destructeur !
    modifRegles = 0;
  }

  void sequenceTour(Joueur *joueurActuel); // sequence de tour d'un joueur
  int checkSequence(
      std::vector<Carte>
          cartesSelection); // check si les cartes forment une sequence ou pas
  void tirerCarte(Joueur *joueurActuel);     // tirer carte (pile ou defausse)
  void placerSequence(Joueur *joueurActuel); // placer une sequence
  void ajouterCartesPileExistante(
      Joueur *
          joueurActuel); // ajouter des cartes a une pile existante sur la table
  void enleverCartes(
      std::vector<Carte> cartes,
      Joueur *joueurActuel); // enleve des cartes dans une main d'un joueur
  Carte selectionCarte(Joueur *joueurActuel); // selection cartes
  void jouer(); // controle combien de parties ont ete joueees et boucle : fixer
                // limite de points
  void afficherTable(Joueur *joueurActuel); // afficher la table
  void defausseFinTour(Joueur *joueurActuel);
  void modifierPile(Joueur *joueurActuel);
  void pileDefausse(Joueur *joueurActuel);
  void choixJouer(Joueur *joueurActuel); // demande si le joueur veut poser
                                         // quelque chose sur la table
};

#endif
