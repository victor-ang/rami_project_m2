#ifndef CARTE_H
#define CARTE_H
#include<iostream>

class Carte {
  int valeur;
  std::string couleur;

public:
  Carte() {
    valeur = 0;
    couleur = "";
  } // constructeur par defaut

  Carte(const Carte &ct) // constructeur par copie
  {
    this->valeur = ct.valeur;
    this->couleur = ct.couleur;
  }

  int compare(Carte &ct);
  void setvaleur(int val);   // set value
  void setcouleur(std::string coul); // set color
  int getvaleur();           // get valeur
  std::string getcouleur();          // get couleur
  void echange(Carte &ct);   // échanger deux cartes

  ~Carte() {} // destructeur
};

#endif
