#ifndef HAND_H
#define HAND_H

#define NB 10

class Hand {
  Carte listcarte[NB];
  int nb_cartes;

public:
  // constructeur par defaut
  Hand() { this->nb_cartes = NB[]; }
  // constructeur par copie
  Hand(const Hand &h) {
    this->nb_cartes = h.nb_cartes;
    for (int i = 0; i < NB; i++)
      listcarte[i] = h.listcarte[i];
  }
  void setlist(Carte *t);
  Carte &tirer();

  void decaler(int debut, int fin);
  int getnb_carte();
  Carte &getcarte(int pos);

  ~Hand() { delete[] listcarte; } // destructeur
};

#endif