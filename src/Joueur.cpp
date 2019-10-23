#include "Joueur.h"

void Joueur::setnom(char *n) {
  nom = new char[strlen(n) + 1];
  strcpy(this->nom, n);
}

void Joueur::sethand(Hand &h) { this->hand = h; }

Hand &Joueur::gethand() { return hand; }

void Joueur::increment() // incrementer le score du joueur
{
  this->score++;
}

char *Joueur::getnom() { return nom; }

int Joueur::getscore() { return score; }
