#include "Joueur.h"
#include <string>
#include <vector>

// constructeur par defaut : initialise le joueur
Joueur::Joueur() {
  this->hand = {};
  this->score = 0; // score du joeur à 0 au début
}

Joueur::Joueur(std::string n) {
  nom = n;
  hand = new Paquet();
}
Joueur::Joueur(Paquet *h, int sco) {
  hand = h;
  score = sco;
}

Joueur::~Joueur() { delete hand; }

// Saisir le nom du joueur
void Joueur::setNom(std::string n) { this->nom = n; }

std::string Joueur::getNom() { return this->nom; };

// saisir le score
void Joueur::setScore(int s) { this->score = s; }

// obtenir le score du joueur
int Joueur::getScore() { return this->score; }

// Combien de cartes chaque joueur pioche a chaque nouveau jeu
void Joueur::premiereMain(Paquet *paquet) {
  for (int i = 0; i < 14; i++) { // 14 cartes au début de la partie
    hand->ajouterCarte(
        paquet->piocheCarte()); // ajout carte du paquet vers la main du joueur
  }
}

// Afficher la main
void Joueur::afficherMain() {
  hand->viewerCartes(); // affiche visuellement la main dans le terminal
}

// True si aucune carte dans la main = test partie finie ou non
bool Joueur::verifieCartes() {
  bool test = false;
  if (hand->taillePaquet() == 0) {
    test = true;
  } else {
    test = false;
  }
  return test;
}

void Joueur::soustraireScore() { // si un joueur a encore des cartes en main a
                                 // la fin de la partie, on retire des pts à son
                                 // score
  int somme = 0;
  for (int i = 0; i < hand->taillePaquet();
       i++) { // on parcourt le vecteur hand
    if (hand->getCartes().at(i).getValeur() <=
        10) { // si carte inf à 10, pts=valeur de la carte
      somme += hand->getCartes()[i].getValeur();
    } else { // si figure, 10 pts
      somme += 10;
    }
  }
  score = score - somme; // on soustrait le total au score du joueur
}
