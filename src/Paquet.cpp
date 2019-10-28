#include "Paquet.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include "Carte.h"
#include <algorithm>

// Symboles ASCII cartes
const char Coeur[] = "\xe2\x99\xa5";
const char Trefle[] = "\xe2\x99\xa3";
const char Carreau[] = "\xe2\x99\xa6";
const char Pique[] = "\xe2\x99\xa0";

void Paquet::suppDerniereCarte() {
  this->cartesPaquet
      .pop_back(); // pop_back vide retire le dernier element du vecteur
}
void Paquet::initPaquet() {
  nouveauPaquet();
  melangerPaquet();
}
void Paquet::viderPile() { this->cartesPaquet.clear(); }
void Paquet::ajoutDevant(Carte c) {
  this->cartesPaquet.insert(cartesPaquet.begin(),
                            c); // ajoute carte a l'avant du paquet
}
void Paquet::melangerPaquet() {
  std::random_shuffle(
      cartesPaquet.begin(),
      cartesPaquet.end()); // fonction du package algorithm. Melange le vecteur
                           // (on lui donne le debut et la fin)
}
void Paquet::nouveauPaquet() {
  std::string couleur;

  // Creation du paquet
  for (int cou = 0; cou < 4; cou++) {
    switch (cou) {
    case 0:
      couleur = "Pique";
      break;
    case 1:
      couleur = "Coeur";
      break;
    case 2:
      couleur = "Trefle";
      break;
    case 3:
      couleur = "Carreau";
      break;
    }

    // Creation des cartes
    for (int car = 1; car <= 13; car++) {
      Carte carteActuelle(car, couleur);
      ajouterCarte(carteActuelle);
    }
  }
}
Carte Paquet::piocheCarte() {
  Carte dessus = getCartes()[cartesPaquet.size() - 1];
  suppDerniereCarte();
  return dessus;
}
void Paquet::ajouterCarte(Carte carteAjoutee) {
  this->cartesPaquet.push_back(carteAjoutee); // ajoute carte au paquet
}
void Paquet::afficherCartes() {
  for (int i = 0; i < cartesPaquet.size(); i++) {
    this->cartesPaquet[i].afficherCarte();
  }
}
void Paquet::supprimerCarte(Carte c) {
  if (taillePaquet() == 0) { // si paquet vide
    return;
  } else if (taillePaquet() == 1) { // si plus qu'une carte
    suppDerniereCarte();
    return;
  } else { // si plus d'une carte
    for (int i = 0; i < taillePaquet(); i++) {
      if (cartesPaquet.at(i) == c) {
        this->cartesPaquet.erase(cartesPaquet.begin() + 1);
      }
    }
  }
}
void Paquet::viewerCartes() { // Fonction d'affichage visuel des cartes dans le
                              // terminal
  int totalCartes = cartesPaquet.size();
  int carteActuelle;
  int i = 0;
  int yBounds = (3 * (totalCartes)) + 4;

  if (totalCartes == 0) { // si pas de cartes, on n'affiche rien
    return;
  }

  for (int x = 0; x < 6; x++) {
    i = 0;
    for (int y = 0; y < yBounds; y++) { // deplacer toutes les piles sauf une
      carteActuelle = cartesPaquet[i].getValeur();
      // haut et bas
      if ((x == 0) || (x == 5)) {
        std::cout << "-";
      }
      // Inserer le cote des cartes
      else if (((y % 3) == 0) && (y < (yBounds - 4)) && (i != totalCartes)) {
        std::cout << "|";
      } else if (y == (yBounds - 1)) {
        std::cout << "|";
      }
      // Inserter le numero de la carte
      else if (((y % 3) == 1) && (x == 1) && (y < (3 * totalCartes))) {
        // Display Number
        if ((carteActuelle == 1) && (x == 1)) {
          std::cout << 'A';
          i++;
        } else if ((carteActuelle == 10) && (x == 1)) {
          std::cout << "10";
          i++;
          y++;
        } else if ((carteActuelle == 11) && (x == 1)) {
          std::cout << 'J';
          i++;
        } else if ((carteActuelle == 12) && (x == 1)) {
          std::cout << 'Q';
          i++;
        } else if ((carteActuelle == 13) && (x == 1)) {
          std::cout << 'K';
          i++;
        } else {
          std::cout << carteActuelle;
          i++;
        }

      }
      // afficher la couleur
      else if (((y % 3) == 1) && (x == 2) && (y < (3 * totalCartes))) {
        std::string couleur = cartesPaquet[i].getCouleur();
        if (couleur == "Pique") {
          std::cout << Pique;
        } else if (couleur == "Coeur") {
          std::cout << Coeur;
        } else if (couleur == "Trefle") {
          std::cout << Trefle;
        } else if (couleur == "Carreau") {
          std::cout << Carreau;
        }
        i++;
      }
      // Carte du dessus
      // Numéro de la carte
      else if ((y == (yBounds - 2)) && (x == 4)) {
        // afficher le numero
        carteActuelle = cartesPaquet[(totalCartes - 1)].getValeur();
        if (carteActuelle == 1) {
          std::cout << 'A';
          i++;
        } else if (carteActuelle == 10) {
          std::cout << "10";
          i++;
          y++;
        } else if (carteActuelle == 11) {
          std::cout << 'J';
          i++;
        } else if (carteActuelle == 12) {
          std::cout << 'Q';
          i++;
        } else if (carteActuelle == 13) {
          std::cout << 'K';
          i++;
        } else {
          std::cout << carteActuelle;
          i++;
        }

      }
      // afficher la couleur
      else if ((y == (yBounds - 3)) && (x == 3)) {
        std::string couleur = cartesPaquet[(totalCartes - 1)].getCouleur();
        if (couleur == "Pique") {
          std::cout << Pique;
        } else if (couleur == "Coeur") {
          std::cout << Coeur;
        } else if (couleur == "Trefle") {
          std::cout << Trefle;
        } else if (couleur == "Carreau") {
          std::cout << Carreau;
        }
        i++;
      }
      // Espace
      else {
        std::cout << " ";
      }
    }
    // lignes de separation
    std::cout << std::endl;
  }
}
int Paquet::taillePaquet() { return this->cartesPaquet.size(); }
void Paquet::suppCarteIndice(int ind) {
  this->cartesPaquet.erase(cartesPaquet.begin() +
                           ind); // supprime la carte a un indice donné
}
std::vector<Carte> Paquet::getCartes() { return this->cartesPaquet; }