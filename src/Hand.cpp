#include "Hand.h"

void Hand::setlist(Carte *t) {
  for (int i = 0; i < NB; i++) {
    listcarte[i] = t[i];
  }
}

Carte &Hand::tirer() {
  int indice = rand() % (this->nb_cartes); // choisir un indice entre 0 et le nombre de cartes
  Carte *ct = new Carte(listcarte[indice]); // on memorise la carte
  decaler(indice, nb_cartes);               // decaler la liste des cartes
  listcarte[nb_cartes - 1] = *ct;           // on met la carte a tirer a la fin
  nb_cartes--;                              // une carte de moins dans la main
  return listcarte[nb_cartes];              // retourner la carte choisie
}

void Hand::decaler(int debut, int fin) {

  for (int i = debut; i < fin; i++) {
    listcarte[i] = listcarte[i + 1];
  }
}
int Hand::getnb_carte() { return nb_carte; }
Carte &Hand::getcarte(int pos) { return listcarte[pos]; }