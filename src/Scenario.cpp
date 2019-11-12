#include "Scenario.h"
#include "Carte.h"
#include "Hand.h"
#include "Joueur.h"
#include "Paquet.h"
#include <algorithm>
#include <iostream>
#include <unistd.h>
#include <vector>

void Scenario::sequenceTour(Joueur *joueurActuel) {
  joueurActuel->afficherMain();
  tirerCarte(joueurActuel);
  afficherTable(joueurActuel);
  choixJouer(joueurActuel);
  defausseFinTour(joueurActuel);
}
int Scenario::checkSequence(std::vector<Carte> cartesSelection) {
  sort(cartesSelection.begin(),
       cartesSelection.end()); // sort : fonction de algorithm
  if (cartesSelection.size() < 3) {
    return -1;
  }

  bool cartesIdentiques = true;
  for (int i = 1; i < cartesSelection.size(); i++) {

    cartesIdentiques &=
        cartesSelection[i].valeur == cartesSelection[i - 1].valeur;
  }
  if (cartesIdentiques == true) {
    return 1;
  }

  cartesIdentiques = true;
  for (int i = 1; i < cartesSelection.size(); i++) {
    cartesIdentiques &=
        cartesSelection[i].couleur == cartesSelection[i - 1].couleur;
  }
  if (cartesIdentiques == true) {
    for (int i = 1; i < cartesSelection.size(); i++) {
      cartesIdentiques &=
          cartesSelection[i].valeur == cartesSelection[i - 1].valeur + 1;
    }
    if (cartesIdentiques == true) {
      return 2;
    }
  }
  return -1;
}

void Scenario::tirerCarte(Joueur *joueurActuel) {
  //  Le joueur décide de piocher dans la pioche ou dans la défausse
  afficherTable(joueurActuel);
  std::cout << "Piocher une carte dans le paquet ou dans la défausse ?"
            << std::endl;
  std::cout << "1. Paquet" << std::endl;
  std::cout << "2. Défausse" << std::endl;

  // Vérifier si le choix entré est correct
  std::string choixEntre;
  std::cin >> choixEntre;
  int choix;
  bool num;
  for (int i = 0; i < choixEntre.length(); i++) {
    num = isdigit(choixEntre.at(i));
  }
  if (!num) {
    std::cout << "Choix non valable, veuillez réessayer" << std::endl;
  } else {
    choix = stoi(choixEntre);
  }
  std::string reponse;
  switch (choix) {
  case 1: {
    joueurActuel->hand->ajouterCarte(
        pioche->piocheCarte()); // fonction pioche de paquet
    return;
    break;
  }
  case 2:
    pilePioche(joueurActuel);
    return;
    break;
  default:
    std::cout << "Choisir une option disponible" << std::endl;
    tirerCarte(joueurActuel); // fonction de scenario
    break;
  }
}
void Scenario::placerSequence(Joueur *joueurActuel) {
  std::vector<Carte> cartesChoisies;
  bool selection = true;
  char reponse;
  do {
    cartesChoisies.push_back(selectionCarte(joueurActuel));
    std::cout << "Continuer? (Y ou N)" << std::endl;
    std::cin >> reponse;
    selection = (reponse == 'Y' || reponse == 'y');
  } while (selection);
  int suitUneRegle = checkSequence(cartesChoisies);
  char id;
  switch (suitUneRegle) {
  case 1:
    id = 'm';
    cartesEnJeu->ajouterPile(cartesChoisies, joueurActuel, id);
    enleverCartes(cartesChoisies, joueurActuel);
    afficherTable(joueurActuel);
    choixJouer(joueurActuel);
    break;
  case 2:
    id = 's';
    cartesEnJeu->ajouterPile(cartesChoisies, joueurActuel, id);
    enleverCartes(cartesChoisies, joueurActuel);
    afficherTable(joueurActuel);
    choixJouer(joueurActuel);
    break;
  default:
    std::cout << "Main non valable, veuillez réessayer" << std::endl;
    sleep(1); // unistd Attente 1 seconde
    cartesChoisies.clear();
    afficherTable(joueurActuel);
    choixJouer(joueurActuel);
    break;
  }
}
void Scenario::ajouterCartesPileExistante(Joueur *joueurActuel) {
  std::cout << "Choisir une pile à laquelle ajouter les cartes:" << std::endl;
  cartesEnJeu->afficherPiles();
  std::vector<Carte> cartesSelectionnees;
  std::string entree;
  // Verification de l'entree
  int selection;
  std::cin >> entree;
  bool verif;
  for (int i = 0; i < entree.length(); i++) {
    verif = isdigit(entree.at(i));
  }
  if (!verif) {
    std::cout << "Choix non valable, veuillez réessayer" << std::endl;
    choixJouer(joueurActuel);
  } else {
    selection = stoi(entree);
  }
  selection--;
  if (!(selection >= 0 && selection < cartesEnJeu->getPile().size())) {
    std::cout << "Choix non valable, veuillez réessayer" << std::endl;
    modifierPile(joueurActuel);
  } else {
    for (int i = 0; i < cartesEnJeu->getPile().at(selection)->taillePaquet();
         i++) {
      cartesSelectionnees.push_back(
          cartesEnJeu->getPile().at(selection)->getCartes().at(i));
    }
    std::cout << "Choisir une carte à ajouter. " << std::endl;
    cartesSelectionnees.push_back(selectionCarte(joueurActuel));
  }
  int regleOk = checkSequence(cartesSelectionnees);
  switch (regleOk) {
  case 1:
  case 2:
  case 3:
  case 4:
    cartesEnJeu->ajouterPileExistante(
        cartesSelectionnees.at(cartesSelectionnees.size() - 1), selection,
        joueurActuel);
    joueurActuel->hand->supprimerCarte(
        cartesSelectionnees.at(cartesSelectionnees.size() - 1));
    afficherTable(joueurActuel);
    choixJouer(joueurActuel);
    break;
  default:
    std::cout << "La carte ajoutée et la pile ne suit pas une règle valable, "
                 "merci de réessayer. "
              << std::endl;
    sleep(1);
    cartesSelectionnees.clear();
    choixJouer(joueurActuel);
  }
}
void Scenario::enleverCartes(std::vector<Carte> cartes, Joueur *joueurActuel) {
  for (int i = 0; i < cartes.size(); i++) {
    joueurActuel->hand->supprimerCarte(cartes.at(i));
  }
}
Carte Scenario::selectionCarte(Joueur *joueurActuel) {
  std::cout << "Choisir une carte (Entrer la valeur (1-13), puis Co,T,P,Ca pour la couleur" << std::endl;
	std::string entreeJoueur;
	std::string couleurDedans;
	std::string couleur;
	std::cout << "Numéro: ";
	std::cin >> entreeJoueur;
	std::cout << "Couleur (Co,T,P,Ca): ";
	std::cin >> couleurDedans;
	int entreeJ;
	bool entreeVal = true;
	for (int i = 0; i < entreeJoueur.length(); ++i)
	{
		entreeVal &= isdigit(entreeJoueur.at(i)); 
	}
	if(entreeJoueur == "A" || entreeJoueur == "a"){
		entreeJ = 1;
	}else if(entreeJoueur == "J" || entreeJoueur == "j"){
		entreeJ = 11;
	}else if(entreeJoueur == "Q" || entreeJoueur == "q"){
		entreeJ = 12;
	}else if(entreeJoueur == "K" || entreeJoueur == "k"){
		entreeJ = 13;
	}else if(entreeVal){
		entreeJ = stoi(entreeJoueur);
	}else{
		std::cout << "Entrée invalide" << std::endl;
		return selectionCarte(joueurActuel);
	}

	if(couleurDedans[0] == 'co' || couleurDedans[0] =='Co'){
		couleur = "Coeur";
	}else if(couleurDedans[0] == 't' || couleurDedans[0] =='T'){
		couleur = "Trefle";
	}else if(couleurDedans[0] == 'ca' || couleurDedans[0] =='Ca'){
		couleur = "Carreau";
	}else if(couleurDedans[0] == 'p' || couleurDedans[0] =='P'){
		couleur = "Pique";
	}else{
		std::cout << "Entrée invalide" << std::endl;
		selectionCarte(joueurActuel);

	}
	Carte cible(entreeJ, couleur);
	// Recherche des cartes dans la main du joueur
	bool trouve = false;
	int i = 0;
	if(joueur1->hand->taillePaquet() == 1){
		trouve = true;
		return joueur1->hand->getCartes().at(0);
	}
	for(i = 0; i < joueur1->hand->taillePaquet(); i++){
		if(cible == joueur1->hand->getCartes().at(i)){
			trouve = true;
			break;
		}
	}
	if(!trouve){
		std::cout << "Carte non trouvée, merci de réessayer." << std::endl;
		return selectionCarte(joueurActuel);
	}
	
	return joueurActuel->hand->getCartes().at(i);
}
void Scenario::jouer() {
  // Nombre de parties et premier joueur
	int parties = 1;
	int joueur = 1;
	bool joueurGagnePartie = false;
	int scoreJoueur1 = joueur1->score;
	int scoreJoueur2 = joueur2->score;
	while(joueur1->score < 500 && joueur2->score < 500){
		while(joueurGagnePartie == false) {
			// Tour du joueur 1
			if(pioche->taillePaquet() == 0){ // plus de cartes dans la pioche
				// Ajouter toutes les cartes de la défausse dans la pioche et remelanger
				std::cout << "Re mélange" << std::endl;
				for(int i = 0; i < defausse->taillePaquet()-1;i++){
					pioche->ajouterCarte(defausse->getCartes().at(i));
				}
				Carte carteDessus(defausse->getCartes().at(defausse->taillePaquet()-1));
				defausse->viderPile();
				defausse->ajouterCarte(carteDessus);
				pioche->melangerPaquet();
			}
			if (joueur == 1) {
				sequenceTour(joueur1);
				joueurGagnePartie = joueur1->verifieCartes();
				joueur = 2;
			}
			else {
				sequenceTour(joueur2);
				joueurGagnePartie = joueur2->verifieCartes();
				joueur = 1;
			}
		}

		// Soustraction des points des cartes restantes et reset du jeu 
		if(joueur1->verifieCartes()){
			joueur2->soustraireScore();
		}else{
			joueur1->soustraireScore();
		}
		// Reset de la table
		cartesEnJeu->effacerPile();
		pioche->viderPile();
		pioche->nouveauPaquet();
		pioche->melangerPaquet();
		scoreJoueur1 += joueur1->score;
		scoreJoueur2 += joueur2->score;
		defausse->viderPile();
		joueur1->hand->viderPile();
		joueur2->hand->viderPile();
		std:: cout << "\t\tPartie suivante" << std:: endl;
		sleep(2);
		joueur1->premiereMain(pioche);
		joueur2->premiereMain(pioche);
		joueurGagnePartie = false;
	}

	// Sorties lorsqu'un joueur gagne
	if(joueur1->score >= 500){
		std::cout << "Le joueur 1 a gagné! avec: "<< joueur1->score << " points!" << std::endl;
	}else if(joueur2->score >= 500){
		std::cout << "Le joueur 2 a gagné! avec: "<< joueur2->score << " points!" << std::endl;
	}else{
		if(joueur1->score > joueur2-> score){
			std::cout << "Le joueur 1 a gagné! avec: "<< joueur1->score << " points!" << std::endl;
		}else if(joueur2->score > joueur1->score){
			std::cout << "Le joueur 2 a gagné! avec: "<< joueur2->score << " points!" << std::endl;
		}else{
			std::cout << "Egalité, avec: " << joueur1->score << " points" << std::endl;
		}
	}
}

void Scenario::afficherTable(Joueur *joueurActuel) {
  std::cout << std::endl;
  std::cout << "\033[2J\033[1;1H"; // code pour effacer le terminal, et
                                   // position du curseur ligne 1 colonne 1
  std::cout << "Score de " << joueur1->nom << " : " << joueur1->score
            << "\t Score de " << joueur2->nom << " : " << joueur2->score
            << std::endl;
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
  std::cout << "Cartes du joueur 2" << std::endl;
  std::cout << "Cartes du joueur 1" << std::endl;
  joueurActuel->afficherMain();
}

void Scenario::defausseFinTour(Joueur *joueurActuel) {
  joueurActuel->afficherMain();
	afficherTable(joueurActuel);
	if(joueurActuel->hand->taillePaquet() == 0){// defausse 
		std::cout << "Veuillez jeter une carte" << std::endl;
		sleep(2);
		int pile = cartesEnJeu->getPile().size()-1;
		std::cout << pile << std::endl;
		for(int i = 0; i < cartesEnJeu->getPile().at(pile)->taillePaquet(); i++){
			//Remettre les cartes dans la main
			cartesEnJeu->getPile().at(pile)->getCartes().at(i).afficherCarte();
			joueur1->hand->ajouterCarte(cartesEnJeu->getPile().at(pile)->getCartes().at(i));
		}
		cartesEnJeu->suppDernierELement();
		afficherTable(joueurActuel);
		choixJouer(joueurActuel);
	}else{
		std::cout << "Vous devez vous débarrasser d'une carte. Sélectionnez une carte à jeter (Entrez une valeur, puis Co,T,P,Ca pour la couleur)" << std::endl;

	}
	Carte def = selectionCarte(joueurActuel);
	defausse->ajouterCarte(def);
	joueurActuel->hand->supprimerCarte(def);
}
void Scenario::modifierPile(Joueur *joueurActuel) {
  char reponse = 'm';
  afficherTable(joueurActuel);
  std::cout << "Voulez-vous ajouter des cartes à une pile existante ? (Y ou N)"
            << std::endl;
  std::cin >> reponse;
  if (reponse == 'y' || reponse == 'Y') {
    modifRegles = 2;
    ajouterCartesPileExistante(joueurActuel);
  } else {
    modifRegles = 0;
    placerSequence(joueurActuel);
  }
}
void Scenario::pilePioche(Joueur *joueurActuel) {
  int taille = joueurActuel->hand->taillePaquet();
	int scoreActuel = joueurActuel->score;
	int num = -1;
	
	
	if (defausse->taillePaquet() != 0) {
		while (num == -1) {
			afficherTable(joueurActuel);
			std::cout << "Veuillez sélectionner la carte que vous souhaitez prendre : (Entrer le numéro de la carte  (1 pour celle à gauche, etc)" << std::endl;	
			std::cin >> num;
			int tailleDefausse = defausse->taillePaquet();
			if (num <= defausse->taillePaquet()) {
				for (int i = (num-1); i < tailleDefausse; i++) {
					joueurActuel->hand->ajouterCarte(defausse->getCartes().at(i));
					
				}
				int difference = taille - joueurActuel->hand->taillePaquet();
				for(int i = joueurActuel->hand->taillePaquet(); i > taille; i--){
					defausse->suppDerniereCarte();
				}
				afficherTable(joueurActuel);
				modifierPile(joueurActuel);
				if (joueurActuel->score == scoreActuel) {
					// Suppriner les cartes tirées de la main et les rajouter a la defausse
					for (int i = joueurActuel->hand->taillePaquet()-1; i >= taille; i--){
						Carte changer = joueurActuel->hand->getCartes().at(i);
						joueurActuel->hand->supprimerCarte(changer);
						defausse->ajouterCarte(changer);
					}
					std::cout << "Vous devez faire, ou modifier, une pile avec la carte tirée." << std::endl;
					sleep(3);
					tirerCarte(joueurActuel);
				}
			}
			else {
				num = -1;
			}
		}	
	}
	else {
		std::cout << "La défausse est vide" << std::endl;
		tirerCarte(joueurActuel);
	}
}
void Scenario::choixJouer(Joueur *joueurActuel) {
  std::cout << "Jouer des cartes ou terminer le tour ? (Y pour jouer, N pour "
               "terminer le tour) "
            << std::endl;
  char reponse = 'm';
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
