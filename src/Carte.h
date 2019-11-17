#ifndef CARTE_H
#define CARTE_H
#include <iostream>
#include <string>

class Carte {
private:
  int valeur;          // valeur de la carte
  std::string couleur; // couleur de la carte

public:
  Carte(); // constructeur par défaut
  Carte(int valCarte, std::string couleurCarte);

  int getValeur(); // obtenir numero de la carte
  void setValeur(int v);
  std::string getCouleur(); // obtenir couleur de la carte
  void setCouleur(std::string c);
  void afficherCarte(); // afficher une carte

  // Surcharge des opérateurs. Permer de comparer des objets de type carte en
  // utilisant les opérateurs classiques

  bool operator==(const Carte &c) const;
  bool operator<(const Carte &c) const;
  bool operator>(const Carte &c) const;
  bool operator<=(const Carte &c) const;
  bool operator>=(const Carte &c) const;
};

#endif
