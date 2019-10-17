#include "Carte.h"
#include<iostream>

int Carte::compare(Carte &ct) {
  if (this->valeur > ct.valeur)
    return 1; // si la première carte est supérieure a la deuxième
  else if (this->valeur < ct.valeur)
    return 2; // si la première carte inférieure a la deuxième
  else
    return 0; // les deux cartes sont égales
}
void Carte::setvaleur(int val) { // set value
  this->valeur = val;
}
void Carte::setcouleur(std::string coul) { // set color
  this->couleur = coul;
}
int Carte::getvaleur() { // get valeur
  return valeur;
}
std::string Carte::getcouleur() { // get couleur
  return couleur;
}
void Carte::echange(Carte &ct) { // échanger deux cartes
  Carte tmp = *this;             // carte temporaire
  valeur = ct.valeur;
  couleur = ct.couleur;
  ct = tmp;
}
