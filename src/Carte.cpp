#include "Carte.h"
#include <iostream>
#include <string>

// Constructeur par defaut
Carte::Carte() {
  valeur = 1;
  couleur = "Pique";
}

// Valeur de la carte connue
Carte::Carte(int valCarte, std::string couleurCarte) {
  this->valeur = valCarte;
  this->couleur = couleurCarte;
}

// Symboles ASCII des couleurs (pour affichage dans le terminal)
// Nb : ne fonctionne pas sur windows ??
const char Coeur[] = "\xe2\x99\xa5";
const char Pique[] = "\xe2\x99\xa0";
const char Carreau[] = "\xe2\x99\xa6";
const char Trefle[] = "\xe2\x99\xa3";

// Afficher carte dans le terminal
void Carte::afficherCarte() {
  // Afficher les contours
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 7; j++) {
      // Si rangée du haut ou du bas
      if (i == 0 || i == 5) {
        std::cout << "-"; // bordures haute et basse des cartes
      } else {
        // Si c'est le cote
        if (j == 0 || j == 6) {
          std::cout << "|"; // bordures gauche et droite des cartes
        }
        // Affiche la valeur (10)
        else if (((j == 2 && i == 1) || (j == 4 && i == 4)) && (valeur == 10)) {
          if ((valeur == 10) && (i == 4)) {
            std::cout << '1';
          } else if ((valeur == 10) && (i == 1)) {
            std::cout << '0';
          } else {
            std::cout << " ";
          }
        }
        // autres valeurs
        else if ((j == 1 && i == 1) || (j == 5 && i == 4)) {
          if (valeur == 1) {
            std::cout << 'A';
          } else if ((valeur == 10) && (i == 1)) {
            std::cout << '1';
          } else if ((valeur == 10) && (i == 4)) {
            std::cout << '0';
          } else if (valeur == 11) {
            std::cout << 'J';
          } else if (valeur == 12) {
            std::cout << 'Q';
          } else if (valeur == 13) {
            std::cout << 'K';
          } else {
            std::cout << valeur;
          }
        }
        // Afficher la couelur
        else if ((i == 2 && j == 1) || (i == 3 && j == 5)) {
          if (couleur == "Pique") {
            std::cout << Pique;
          } else if (couleur == "Coeur") {
            std::cout << Coeur;
          } else if (couleur == "Trefle") {
            std::cout << Trefle;
          } else if (couleur == "Carreau") {
            std::cout << Carreau;
          }
        }
        // Si cote droit
        else if (j == 10) {
          std::cout << "|" << std::endl;
        }
        // Espace vide
        else {
          std::cout << " ";
        }
      }
    }
    // Seperer cartes
    std::cout << std::endl;
  }
}

int Carte::getValeur() { // obtenir valeur de la carte
  return valeur;
}
std::string Carte::getCouleur() { // obtenir couleur de la carte
  return couleur;
}

void Carte::setValeur(int v) { this->valeur = v; } // donner une valeur

void Carte::setCouleur(std::string c) {
  this->couleur = c;
} // donner une couleur

// SURCHARGE DES OPERATEURS

// Operateur egal
bool Carte::operator==(const Carte &c) const {
  bool isEqual = false;
  if (c.valeur == valeur) {
    if (couleur == c.couleur) {
      isEqual = true;
    }
  } else {
    isEqual = false;
  }
  return isEqual;
}

// Operateur plus petit que
bool Carte::operator<(const Carte &c) const {
  bool isInf = false;
  if (valeur < c.valeur) {
    isInf = true;
  } else {
    isInf = false;
  }
  return isInf;
}

// Operateur plus grand que
bool Carte::operator>(const Carte &c) const {
  bool isSup = false;
  if (valeur > c.valeur) {
    isSup = true;
  } else {
    isSup = false;
  }
  return isSup;
}

// Operateur plus petit ou egal
bool Carte::operator<=(const Carte &c) const {
  bool isLeq = false;
  if (valeur <= c.valeur) {
    isLeq = true;
  } else {
    isLeq = false;
  }
  return isLeq;
}

// Operateur plus grand ou egal
bool Carte::operator>=(const Carte &c) const {
  bool isGeq = false;
  if (valeur >= c.valeur) {
    isGeq = true;
  } else {
    isGeq = false;
  }
  return isGeq;
}
