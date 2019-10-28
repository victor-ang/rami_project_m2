#include "Joueur.h"
#include <string>

// Retourne la main du joueur
Paquet *Joueur::getMain() { return hand; }

// Afficher le nom du joueur
void Joueur::afficherNom() { std::cout << nom << std::endl; }

// Combien de cartes chaque joueur pioche a chaque nouveau jeu
void Joueur::premiereMain(Paquet *paquet) {
  for (int i = 0; i < 7; i++) {
    hand->ajouterCarte(paquet->piocheCarte()); 
  }
}

// Afficher la main
void Joueur::afficherMain() {
  hand->viewerCartes(); // affiche visuellement la main dans le terminal
}

// True si aucune carte dans la main
bool Joueur::verifieCartes() {
  if (hand->taillePaquet() == 0) { 
    return true;
  } else {
    return false;
  }
}

// soustrait le score à la fin du jeu (car le score est augmente des qu'un
// joueur pioche une carte)
void Joueur::soustraireScore() {
  int somme = 0;
  for (int i = 0; i < hand->taillePaquet(); i++) { // on parcourt le vecteur hand
    if (hand->getCartes().at(i).getValeur() <= 10) {  // si carte inf à 10, pts=valeur de la carte
      somme += hand->getCartes()[i].getValeur();
    } else if (hand->getCartes().at(i).getValeur() == 1) { // si  AS,  1 pts
      somme += 1;
    } else { //si figure, 10 pts
      somme += 10;
    }
  }
  score = score - somme; // on soustrait le total au score du joueur
}