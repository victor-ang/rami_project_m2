#ifndef CARTE_H
#define CARTE_H

class Carte {
  int valeur;
  int couleur;

public:
  Carte() {
    valeur = 0;
    couleur = 0;
  }                      // constructeur par defaut
  Carte(const Carte &ct) // constructeur par copie
  {
    this->valeur = ct.valeur;
    this->couleur = ct.couleur;
  }
  int compare(Carte &ct) {
    if (this->valeur > ct.valeur)
      return 1; // si la première carte est supérieure a la deuxième
    else if (this->valeur < ct.valeur)
      return 2; // si la première carte inférieure a la deuxième
    else
      return 0; // les deux cartes sont égales
  }
  void setvaleur(int val) // set value
  {
    this->valeur = val;
  }
  void setcouleur(int coul) // set color
  {
    this->couleur = coul;
  }
  int getvaleur() // accesseur en lecture sur valeur
  {
    return valeur;
  }
  int getcouleur() // accesseur en lecture sur valeur
  {
    return couleur;
  }
  void echange(Carte &ct) // echanger deux carte
  {
    Carte aide =
        *this; // en creer une carte aide pour enregistrer la premier carte
    valeur = ct.valeur;   // en affecte la valeur de 2 carte à la 1
    couleur = ct.couleur; // en affecte la couleur de 2 carte à la 1
    ct = aide;            // en recopie la 2 carte dans la premier
  }
  // class destructor
  ~Carte() {} // c'est le compilateur qui choisie le destructeur
};

#endif // CARTE_H
