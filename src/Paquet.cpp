#include "Paquet.h"

void Paquet::trier() {
  for (int i = 0; i < 51; i++) {
    for (int j = i + 1; j < 52; j++) {
      if (this->carte[i].getvaleur() > this->carte[j].getvaleur()) {
        // Permuter les deux carte
        carte[i].echange(carte[j]);
      }
    }
  }
}
// Melanger l'ensemble des cartes
void Paquet::melanger() {
  int indice;
  int pos = 52;
  for (int i = 0; i < 52; i++) {
    indice = rand() % (pos); // indice d'une carte au hasard
    // permutation de 2 cartes
    carte[indice].echange(carte[pos - 1]);
    pos--; // on decremente la fin du paquet pour ne pas remelanger la carte
  }
}
// Couper le paquet en deux sous paquet
void Paquet::split(Hand &h1, Hand &h2) {
  Carte list1[26], list2[26]; // 2 pointeurs de listes de cartes
  int a = 0;
  // Distribution du paquet en deux listes
  for (int i = 0; i < 26; i++) {
    list1[i] = carte[a];
    a++;
    list2[i] = carte[a];
    a++;
  }
  // Affectation des listes
  h1.setlist(list1);
  h2.setlist(list2);
}
Carte Paquet::getcarte(int pos) // Retourne carte
{
  return carte[pos];
}