#include "Paquet.h"
#include "Carte.h"
#include <algorithm>
#include <ctime>
#include <iostream>
#include <stdlib.h>
#include <string>

Paquet::Paquet() { cartesPaquet = {}; }

// Constructeur avec cartes connues
Paquet::Paquet(std::vector<Carte> c) { cartesPaquet = c; }

// Symboles ASCII cartes (affichage terminal) (ne fonctionne pas sous Windows)
const char Coeur[] = "\xe2\x99\xa5";
const char Trefle[] = "\xe2\x99\xa3";
const char Carreau[] = "\xe2\x99\xa6";
const char Pique[] = "\xe2\x99\xa0";

void Paquet::suppDerniereCarte() {
  this->cartesPaquet.pop_back(); // pop_back vide retire le dernier element du vecteur
}
void Paquet::initPaquet() {
  // nouveau paquet trié, puis on le mélange
  nouveauPaquet();
  melangerPaquet();
}
void Paquet::viderPile() {
  this->cartesPaquet.clear();
} // vider une pile de cartes
void Paquet::ajoutDevant(Carte c) {
  this->cartesPaquet.insert(cartesPaquet.begin(), c); // ajoute carte a l'avant du paquet
}

int Paquet::nbMelangesAleatoires() {
  srand(time(NULL)); // temps aleatoire depuis 1970 (nouveau chaque seconde)
  return rand() % (100 - 1 + 1) + 1; // tirage entre 1 et 100
}

void Paquet::melangerPaquet() {
  int nbMelanges = nbMelangesAleatoires(); // nombre de mélanges
  for (int i = 0; i < nbMelanges; i++) {
    random_shuffle(cartesPaquet.begin(), cartesPaquet.end()); // fonction du package algorithm. Melange le vecteur
                                                              // (on lui donne le debut et la fin du paquet à melanger)
  }
}
void Paquet::nouveauPaquet() {
  std::string couleur; // couleurs

  // Creation du paquet
  for (int cou = 0; cou < 4; cou++) { // boucle sur les couleurs
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

    // Creation des cartes de l'as au roi
    for (int car = 1; car <= 13; car++) {
      Carte carteActuelle(car, couleur);
      ajouterCarte(carteActuelle); // ajout de la carte créée au paquet
    }
  }
}

Carte Paquet::piocheCarte() { // piocher carte dans paquet
  Carte dessus = getCartes()[cartesPaquet.size() - 1]; // derniere carte paquet
  suppDerniereCarte(); // on la supprime du paquet (pour apres l'ajouter au jeu
                       // du joueur)
  return dessus;
}
void Paquet::ajouterCarte(Carte carteAjoutee) {
  this->cartesPaquet.push_back(carteAjoutee); // ajoute carte au paquet
}

void Paquet::supprimerCarte(Carte c) {
  if (taillePaquet() == 0) { // si paquet vide, rien
    return;
  } else if (taillePaquet() == 1) { // si plus qu'une carte
    suppDerniereCarte();            // suppression de la seule carte
    return;
  } else {                                     // si plus d'une carte
    for (int i = 0; i < taillePaquet(); i++) { // parcours des cartes
      if (cartesPaquet.at(i) == c) {           // si carte trouvée
        this->cartesPaquet.erase(cartesPaquet.begin() + i); // on la supprime
      }
    }
  }
}
void Paquet::viewerCartes() { // Fonction d'affichage visuel des cartes dans le
                              // terminal (pour la défausse)
  unsigned long totalCartes = cartesPaquet.size(); // taille paquet
  int carteActuelle = 0;
  int i = 0;
  unsigned long yBounds = (3 * (totalCartes)) + 4;

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
      // Inserer le coté des cartes
      else if (((y % 3) == 0) && (y < (yBounds - 4)) && (i != totalCartes)) {
        std::cout << "|";
      } else if (y == (yBounds - 1)) {
        std::cout << "|";
      }
      // Inserter le numero de la carte
      else if (((y % 3) == 1) && (x == 1) && (y < (3 * totalCartes))) {
        // Affichage valeur
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
int Paquet::taillePaquet() {
  return this->cartesPaquet.size();
} // retourne la taille du paquet

std::vector<Carte> Paquet::getCartes() {
  return this->cartesPaquet;
} // obtenir cartes du paquet
