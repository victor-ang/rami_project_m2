#ifndef CARTE_H
#define CARTE_H
#include <iostream>
#include <string>

class Carte {
private :
// mettre les attributs dans private

public:
  // Valeur et couleur de la carte
  int valeur;
  std::string couleur;


  Carte() {
    valeur = 1;
    couleur = "Pique";
  } // constructeur par defaut

  Carte(int valCarte, std::string couleurCarte) // valeur de la carte connue
  {
    this->valeur = valCarte;
    this->couleur = couleurCarte;
  }

  int getValeur();          // obtenir numero de la carte
  std::string getCouleur(); // obtenir couleur de la carte
  void afficherCarte(); // afficher une carte

  // Surcharge des opérateurs. Permer de comparer des objets de type carte en utilisant les opérateurs classiques
  bool operator==(const Carte c) const; // Rajouter des & : utiliser references
  bool operator<(const Carte c) const;
  bool operator>(const Carte c) const;
  bool operator<=(const Carte c) const;
  bool operator>=(const Carte c) const;
};

#endif
