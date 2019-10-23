#ifndef JOUEUR_H
#define JOUEUR_H

class Joueur {
  char *nom;
  Hand hand;
  int score;

public:
  // constructeur par defaut
  Joueur() {
    this->score = 0; // score du joeur à 0 au début
  }
  void setnom(char *n);

  void sethand(Hand &h);

  Hand &gethand();

  void increment();

  char *getnom();

  int getscore();

  ~Joueur() { delete[] nom; }
};

#endif