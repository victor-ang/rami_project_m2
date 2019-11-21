#include "Scenario.h"
#include "Carte.h"
#include "Hand.h"
#include "Joueur.h"
#include "Paquet.h"
#include <algorithm>
#include <iostream>
#include <unistd.h>
#include <vector>

// constructeur
Scenario::Scenario(Joueur *j1, Joueur *j2, Paquet *pilePioche,
                   Paquet *pileDefausse) {
  joueur1 = j1;
  joueur2 = j2;
  pioche = pilePioche;
  defausse = pileDefausse;
  cartesEnJeu = new Hand();
}

// destructeur
Scenario::~Scenario() { delete cartesEnJeu; }

// sequence du tour d'un joueur
void Scenario::sequenceTour(Joueur *joueurActuel) {
  joueurActuel->afficherMain(); // affichage de ses cartes
  tirerCarte(joueurActuel);     // tirage d'une carte
  if (joueurActuel->getChoice() == 1) {
    afficherTable(joueurActuel); // affichage de la table
    choixJouer(joueurActuel);    // demande au joueur ce qu'il veut faire
  }
  defausseFinTour(joueurActuel); // defausse apres avoir joué
}

// verifie si un vecteur donné suit une regle.
//  -1 : rien
//  1 : brelan
//  2 : sequence
int Scenario::checkSequence(std::vector<Carte> cartesSelection) {
  // -1, 1 et 2 (les return) setont utilisés dans un switch
  sort(cartesSelection.begin(), cartesSelection.end()); // sort : fonction de algorithm pour trier
  if (cartesSelection.size() < 3) { // si moins de 3 cartes posées, sequence non valable
    return -1;
  }

  // Brelan, carré
  bool cartesIdentiques = true; // on verifie si les cartes sont identiques (brelan, carré)
  for (int i = 1; i < cartesSelection.size(); i++) {

    cartesIdentiques &= cartesSelection[i].getValeur() == cartesSelection[i - 1].getValeur(); // comparaison valeurs
  }
  if (cartesIdentiques == true) { // si cartes identiques
    return 1;                     // brelan
  }

  // Sequence
  cartesIdentiques = true;
  for (int i = 1; i < cartesSelection.size(); i++) {
    cartesIdentiques &= cartesSelection[i].getCouleur() == cartesSelection[i - 1].getCouleur(); // comparaison couleurs
  }
  if (cartesIdentiques == true) {
    for (int i = 1; i < cartesSelection.size(); i++) {
      cartesIdentiques &= cartesSelection[i].getValeur() == cartesSelection[i - 1].getValeur() + 1; // les cartes se suivent (+1) ?
    }
    if (cartesIdentiques == true) {
      return 2; // sequence
    }
  }
  return -1; // rien
}

void Scenario::tirerCarte(Joueur *joueurActuel) {
  joueurActuel->setChoice(0);
  //  Le joueur décide de piocher dans la pioche ou dans la défausse
  afficherTable(joueurActuel);
  std::cout << "Piocher une carte dans le paquet ou dans la défausse ?"
            << std::endl;
  std::cout << "1. Paquet" << std::endl;
  std::cout << "2. Défausse" << std::endl;

  // Vérifier si le choix entré est correct
  std::string choixEntre; // variable de type string pour l'entrée du joueur
  std::cin >> choixEntre; // cin
  int choix = 0;
  bool num = false;
  for (int i = 0; i < choixEntre.length(); i++) {
    num = isdigit(choixEntre.at(i)); // verifie si c'est un nombre
  }
  joueurActuel->setChoice(num);

  if (!num) {
    std::cout << "Choix non valable, veuillez réessayer" << std::endl;
  } else {
    choix = stoi(choixEntre); // cast string en int
  }
  std::string reponse;
  switch (choix) {
  case 1: { // pioche dans le paquet
    joueurActuel->hand->ajouterCarte(pioche->piocheCarte()); // fonction pioche de paquet
    return;
    break;
  }
  case 2: // pioche dans la défausse
    pileDefausse(joueurActuel);
    return;
    break;
  default: // entrée non valable
    std::cout << "Choisir une option disponible" << std::endl;
    tirerCarte(joueurActuel); // fonction de scenario
    break;
  }
}

void Scenario::placerSequence(Joueur *joueurActuel) { // placer une sequence de cartes sur la table
  std::vector<Carte> cartesChoisies; // cartes choisies par le joueur
  bool selection = true;
  char reponse;
  do {
    cartesChoisies.push_back(selectionCarte(joueurActuel)); // on ajoute a cartesChoisies les cartes que le joueur
                                                            // veut jouer (à partir de ses cartes)
    std::cout
        << "Continuer? (Y ou N)"
        << std::endl; // Rajouter des cartes? Si Yes, on reste dans le while
    std::cin >> reponse;
    selection = (reponse == 'Y' || reponse == 'y');
  } while (selection);
  int suitUneRegle = checkSequence(cartesChoisies); // on verifie si les cartes choisies
                                                    // suivent une regle (brelan, sequence)
  switch (suitUneRegle) {
  case 1:
    // brelan
    cartesEnJeu->ajouterPile(cartesChoisies, joueurActuel); // ajouter la pile sur la table
    enleverCartes(cartesChoisies, joueurActuel); // enlever les cartes posées de la main du joueur
    afficherTable(joueurActuel); // afficher les cartes du joueur
    choixJouer(joueurActuel);    // lui proposer de continuer à jouer
    break;
  case 2:
    // sequence
    cartesEnJeu->ajouterPile(cartesChoisies, joueurActuel);
    enleverCartes(cartesChoisies, joueurActuel);
    afficherTable(joueurActuel);
    choixJouer(joueurActuel);
    break;
  default:
    std::cout << "Main non valable, veuillez réessayer" << std::endl;
    cartesChoisies .clear(); // on efface la variable temporaire qui contenait les cartes
                             // qu ele joueur voulait poser (car non valables)
    afficherTable(joueurActuel); // on affiche ses cartes
    choixJouer(joueurActuel);    // on lui repropose de jouer
    break;
  }
}

void Scenario::ajouterCartesPileExistante(Joueur *joueurActuel) { // ajouter des cartes à une pile deja sur la table
  cartesEnJeu->afficherPiles();
  std::cout << "Choisir une pile à laquelle ajouter les cartes:" << std::endl;

  std::vector<Carte> cartesSelectionnees;
  std::string entree;
  // Verification de l'entree
  int selection = 0;
  std::cin >> entree;
  bool verif = false;
  for (int i = 0; i < entree.length(); i++) {
    verif = isdigit(entree.at(i)); // check si entrée est un nombre
  }
  if (!verif) { // si ce n'est pas un nombre
    std::cout << "Choix non valable, veuillez réessayer" << std::endl;
    choixJouer(joueurActuel);
  } else {                    // si c'est un entier
    selection = stoi(entree); // cast
  }
  selection--; // on retire 1 pour que les indices correspondent
  if (!(selection >= 0 && selection < cartesEnJeu->getPile().size())) {
    std::cout << "Choix non valable, veuillez réessayer" << std::endl;
    modifierPile(joueurActuel);
  } else { // si choix valable
    for (int i = 0; i < cartesEnJeu->getPile().at(selection)->taillePaquet(); i++) {
      cartesSelectionnees.push_back(cartesEnJeu->getPile().at(selection)->getCartes().at(i)); // ajout de cartes
    }
    std::cout << "Choisir une carte à ajouter. " << std::endl;
    cartesSelectionnees.push_back(selectionCarte(joueurActuel));
  }
  int regleOk = checkSequence(cartesSelectionnees); // on verifie si le joueur a le droit
                                                    // de poser les cartes
  switch (regleOk) {
  case 1: // brelan OK
  case 2: // séquence OK
    cartesEnJeu->ajouterPileExistante(cartesSelectionnees.at(cartesSelectionnees.size() - 1), selection, joueurActuel);
    joueurActuel->hand->supprimerCarte(cartesSelectionnees.at(cartesSelectionnees.size() - 1));
    afficherTable(joueurActuel);
    choixJouer(joueurActuel);
    break;
  default: // la valeur retournee par checkSequence est -1 : le joueur ne peux
           // pas poser les cartes
    std::cout
        << "La carte ajoutée et la pile ne suivent pas une règle valable, "
           "merci de réessayer. "
        << std::endl;
    cartesSelectionnees.clear();
    choixJouer(joueurActuel);
  }
}

void Scenario::enleverCartes(std::vector<Carte> cartes, Joueur *joueurActuel) { // enlever de la main du joueur quand il pose
  for (int i = 0; i < cartes.size(); i++) {
    joueurActuel->hand->supprimerCarte(cartes.at(i));
  }
}

Carte Scenario::selectionCarte(Joueur *joueurActuel) {
  std::cout
      << "Choisir une carte (Entrer la valeur (1-13 ou 1-10, J, Q, K), puis H "
         "(Coeur),T (Trèfle),P (Pique),C (Carreau) pour la couleur)"
      << std::endl;
  std::string entreeValeur;
  std::string entreeCouleur;
  std::string couleur;
  std::cout << "Numéro: ";
  std::cin >> entreeValeur; // le joueur entre le numéro de la carte
  std::cout << "Couleur (H (Coeur),T (Trèfle), P (Pique), C (Carreau)): ";
  std::cin >> entreeCouleur; // le joueur entre la couleur de la carte
  int val;
  bool entreeVal = true;
  for (int i = 0; i < entreeValeur.length(); ++i) {
    entreeVal &= isdigit(entreeValeur.at(i));
  }
  if (entreeValeur == "A" || entreeValeur == "a") {
    val = 1;
  } else if (entreeValeur == "J" || entreeValeur == "j") {
    val = 11;
  } else if (entreeValeur == "Q" || entreeValeur == "q") {
    val = 12;
  } else if (entreeValeur == "K" || entreeValeur == "k") {
    val = 13;
  } else if (entreeVal) {
    val = stoi(entreeValeur);
  } else {
    std::cout << "Entrée invalide" << std::endl;
    return selectionCarte(joueurActuel); // on recommence
  }

  if (entreeCouleur[0] == 'h' || entreeCouleur[0] == 'H') {
    couleur = "Coeur";
  } else if (entreeCouleur[0] == 't' || entreeCouleur[0] == 'T') {
    couleur = "Trefle";
  } else if (entreeCouleur[0] == 'c' || entreeCouleur[0] == 'C') {
    couleur = "Carreau";
  } else if (entreeCouleur[0] == 'p' || entreeCouleur[0] == 'P') {
    couleur = "Pique";
  } else {
    std::cout << "Entrée invalide" << std::endl;
    selectionCarte(joueurActuel);
  }
  Carte cible(val, couleur);
  // Recherche des cartes dans la main du joueur
  bool trouve = false;
  int i = 0;
  if (joueurActuel->hand->taillePaquet() == 1) {
    trouve = true;
    return joueurActuel->hand->getCartes().at(0);
  }
  for (i = 0; i < joueurActuel->hand->taillePaquet(); i++) {
    if (cible == joueurActuel->hand->getCartes().at(i)) {
      trouve = true;
      break;
    }
  }
  if (!trouve) {
    std::cout << "Carte non trouvée, merci de réessayer." << std::endl;
    return selectionCarte(joueurActuel);
  }

  return joueurActuel->hand->getCartes().at(i);
}
void Scenario::jouer() {
  // Nombre de parties et premier joueur
  int joueur = 1;                 // joueur 1 commence
  bool joueurGagnePartie = false; // bool : true si partie terminée
  while (joueurGagnePartie == false) {
    // Tour du joueur 1 ou 2
    if (pioche->taillePaquet() == 0) { // plus de cartes dans la pioche
      // Ajouter toutes les cartes de la défausse dans la pioche et remelanger
      std::cout << "Re mélange" << std::endl;
      for (int i = 0; i < defausse->taillePaquet() - 1; i++) {
        pioche->ajouterCarte(defausse->getCartes().at(i)); // ajout des cartes de la défausse dans la pioche
      }
      Carte carteDessus(defausse->getCartes().at(defausse->taillePaquet() - 1));
      defausse->viderPile(); // on vide la défausse
      defausse->ajouterCarte(carteDessus);         // ajout de la derniere carte dans la défausse
      pioche->melangerPaquet(); // mélange de la pioche
    }
    if (joueur == 1) { // joueur 1 commence
      sequenceTour(joueur1);
      joueurGagnePartie = joueur1->verifieCartes();
      joueur = 2; // tour du joueur2
    } else {
      sequenceTour(joueur2);
      joueurGagnePartie = joueur2->verifieCartes();
      joueur = 1; // puis tour j1 ...
    }
  }

  // Soustraction des points des cartes restantes
  if (joueur1->verifieCartes()) {
    joueur2->soustraireScore();
  } else {
    joueur1->soustraireScore();
  }

  // Sorties lorsqu'un joueur gagne
  std::cout << std::endl;
  if (joueur1->getScore() > joueur2->getScore()) {
    std::cout << "Le joueur 1 (" << joueur1->getNom()
              << ") a gagné, avec: " << joueur1->getScore() << " points!"
              << std::endl;
    std::cout << "Score du joueur 2 (" << joueur2->getNom()
              << ") : " << joueur2->getScore() << std::endl;
  } else if (joueur2->getScore() > joueur1->getScore()) {
    std::cout << "Le joueur 2 (" << joueur2->getNom()
              << ") a gagné, avec: " << joueur2->getScore() << " points!"
              << std::endl;
    std::cout << "Score du joueur 1 (" << joueur1->getNom()
              << ") : " << joueur1->getScore() << std::endl;
  } else {
    std::cout << "Egalité, avec: " << joueur1->getScore() << " points"
              << std::endl;
  }
}

void Scenario::afficherTable(Joueur *joueurActuel) {
  std::cout << std::endl;
  std::cout << "\033[2J\033[1;1H"; // code pour effacer le terminal, et
                                   // position du curseur ligne 1 colonne 1
  std::cout << "Score de " << joueur1->getNom() << " : " << joueur1->getScore()
            << "\t Score de " << joueur2->getNom() << " : "
            << joueur2->getScore() << std::endl;
  std::cout << "Cartes jouées" << std::endl;
  cartesEnJeu->afficherPiles();
  std::cout << "Paquet" << std::endl;
  std::cout << "-------" << std::endl;
  std::cout << "|?    |" << std::endl;
  std::cout << "|     |" << std::endl;
  std::cout << "|     |" << std::endl;
  std::cout << "|    ?|" << std::endl;
  std::cout << "-------" << std::endl;
  std::cout << "Défausse" << std::endl;
  defausse->viewerCartes();
  std::cout << "Cartes de " << joueurActuel->getNom() << std::endl;
  joueurActuel->afficherMain();
}

void Scenario::defausseFinTour(Joueur *joueurActuel) {
  joueurActuel->afficherMain();
  afficherTable(joueurActuel);
  if (joueurActuel->hand->taillePaquet() == 0) {
    return;
  } else {
    std::cout
        << "Vous devez vous débarasser d'une carte. Sélectionnez une carte à "
           "jeter (Entrez une valeur, puis H (coeur),T (Trèfle),P (Pique), C "
           "(Carreau) pour la couleur)"
        << std::endl;
  }
  Carte def = selectionCarte(joueurActuel);
  defausse->ajouterCarte(def); // ajout de la carte à la défausse
  joueurActuel->hand->supprimerCarte(def); // suppression de la carte jetée de la main du joueur
}

void Scenario::modifierPile(Joueur *joueurActuel) {
  char reponse = 'b'; // caractere au hasard, pour initialiser la variable sur
                      // une valeur et pas au hasard
  afficherTable(joueurActuel);
  std::cout << "Voulez-vous ajouter des cartes à une pile existante ? (Y ou N)"
            << std::endl;
  std::cin >> reponse;
  if (reponse == 'y' || reponse == 'Y') {
    ajouterCartesPileExistante(joueurActuel);
  } else {
    placerSequence(joueurActuel);
  }
}

// Fonction pour piocher dans la défausse
void Scenario::pileDefausse(Joueur *joueurActuel) {
  int taille = joueurActuel->hand->taillePaquet();
  int scoreActuel = joueurActuel->getScore();

  if (defausse->taillePaquet() != 0) {
    int tailleDefausse = defausse->taillePaquet();
    joueurActuel->hand->ajouterCarte(defausse->getCartes().at(tailleDefausse - 1));
    defausse->suppDerniereCarte();
    afficherTable(joueurActuel);
    modifierPile(joueurActuel);
    if (joueurActuel->getScore() == scoreActuel) {
      // Suppriner la cartes tirée de la main et la rajouter a la
      // defausse
      Carte changer = joueurActuel->hand->getCartes().at(joueurActuel->hand->taillePaquet() - 1);
      joueurActuel->hand->supprimerCarte(changer);
      defausse->ajouterCarte(changer);
      //}
      std::cout << "Vous devez faire ou modifier une pile avec la carte tirée."
                << std::endl;
      tirerCarte(joueurActuel);
    }
  } else {
    std::cout << "La défausse est vide" << std::endl;
    tirerCarte(joueurActuel);
  }
}
void Scenario::choixJouer(Joueur *joueurActuel) {
  std::cout << "Jouer des cartes ou terminer le tour ? (Y pour jouer, N pour "
               "terminer le tour) "
            << std::endl;
  char reponse = 'b';
  std::cin >> reponse;
  switch (reponse) {
  case 'Y':
  case 'y':
    modifierPile(joueurActuel);
    break;
  case 'N':
  case 'n':
    break;
  default:
    std::cout << "Entrée invalide, veuillez réessayer" << std::endl;
    choixJouer(joueurActuel);
  }
}
