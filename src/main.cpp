#include "Carte.h"
#include "Joueur.h"
#include "Paquet.h"
#include "Scenario.h"
#include <fstream>
#include <iostream>

int main() {
  bool exit = false;
  int choix = 0;

  // Fichier regles
  std::ifstream file("Regles.txt");
  std::string contenu;

  // Creation  du paquet
  Paquet *paquetDeJeu = new Paquet();
  paquetDeJeu->initPaquet(); // initialisation

  // Creation de la defausse
  Paquet *defausse = new Paquet();

  // Joueur 1
  std::cout << "Entrer le nom du joueur 1 :";
  std::string nom;
  std::getline(std::cin, nom);
  Joueur *joueur1 = new Joueur(nom);
  joueur1->premiereMain(paquetDeJeu);

  // Joueur 2
  std::cout << "Entrer le nom du joueur 2 :";
  std::string nom2;
  std::getline(std::cin, nom2);
  Joueur *joueur2 = new Joueur(nom2);
  joueur2->premiereMain(paquetDeJeu);

  // Mise en place de la table
  Scenario *tableDeJeu = new Scenario(joueur1, joueur2, paquetDeJeu, defausse);

  // Boucle tant que le jeu continue

  while (exit != true) {
    // Accueil jeu
    std::cout << std::endl;
    std::cout << "######################" << std::endl;
    std::cout << "#        Rami        #" << std::endl;
    std::cout << "######################" << std::endl;
    std::cout << std::endl;
    std::cout << "Choisir une option" << std::endl;
    std::cout << "1. Nouvelle partie" << std::endl;
    std::cout << "2. Règles" << std::endl;
    std::cout << "3. Quitter le jeu" << std::endl;

    std::cin >> choix;

    switch (choix) { // selon le choix effectué
    // Jouer
    case 1:
      tableDeJeu->joueur1->setScore(0); // score initial joueur1
      tableDeJeu->joueur2->setScore(0); // score initial joueur2
      tableDeJeu->jouer();
      break;

    // Afficher regles
    case 2:
      std::cout << std::endl << std::endl; // espacement
      while (std::getline(file, contenu)) {
        std::cout << contenu << std::endl;
      }
      std::cout << std::endl;
      break;

    // Quitter jeu
    case 3:
      exit = true;
      break;

    // Si option choisie non valide (evite un if)
    default:
      std::cout << "Choisir une option valide" << std::endl;
      break;
    }
  }
  std::cout << "Merci !" << std::endl;

  return 0;
}
