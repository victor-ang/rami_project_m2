#include "Carte.h"
#include "Joueur.h"
#include "Paquet.h"
#include "Scenario.h"
#include <fstream>
#include <iostream>

int main() {
  bool exit = false; // booléen pour quitter le jeu
  int choix = 0;     // pour selectionner quoi faire (nouvelle partie, afficher
                     // regles ou quitter le jeu)

  // Fichier regles
  std::ifstream file("Regles.txt");
  std::string contenu;

  // Creation  du paquet
  Paquet *paquetDeJeu = new Paquet(); // nouveau paquet
  paquetDeJeu->initPaquet();          // initialisation

  // Creation de la defausse
  Paquet *defausse = new Paquet();

  // Joueur 1
  std::cout << "Entrer le nom du joueur 1 :";
  std::string nom;                    // nom joueur 1
  std::getline(std::cin, nom);        // cin
  Joueur *joueur1 = new Joueur(nom);  // nouveau joueur
  joueur1->premiereMain(paquetDeJeu); // cartes du joueur 1 à l'initialisation

  // Joueur 2
  std::cout << "Entrer le nom du joueur 2 :";
  std::string nom2;                   // nom joueur 2
  std::getline(std::cin, nom2);       // cin
  Joueur *joueur2 = new Joueur(nom2); // initialisation joueur
  joueur2->premiereMain(paquetDeJeu); // cartes du joueur 2 à l'initialisation de la partie

  // Mise en place de la table
  Scenario *tableDeJeu = new Scenario(joueur1, joueur2, paquetDeJeu, defausse); // nouveau scenario

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
    std::cout << "2. Règles du jeu" << std::endl;
    std::cout << "3. Quitter le jeu" << std::endl;

    std::cin >> choix; // l'utilisateur entre le choix qu'il veut

    switch (choix) { // selon le choix effectué
    // Jouer
    case 1:
      tableDeJeu->joueur1->setScore(0); // score initial joueur1
      tableDeJeu->joueur2->setScore(0); // score initial joueur2
      tableDeJeu->jouer();              // debut jeu
      break;

    // Afficher regles
    case 2:
      std::cout << std::endl << std::endl; // espacement
      while (std::getline(file, contenu)) { // tant qu'il reste des lignes à afficher
        std::cout << contenu << std::endl; // affichage de la ligne
      }
      std::cout << std::endl; // saut de ligne
      break;

    // Quitter jeu
    case 3:
      exit = true; // modif du booléen de départ
      break;

    // Si option choisie non valide (evite un if)
    default: // sinon
      std::cout << "Choisir une option valide !" << std::endl;
      break;
    }
  }
  std::cout << "Merci !" << std::endl; // lorsqu'on quitte le jeu

  return 0;
}
