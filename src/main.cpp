#include<iostream>
#include"Carte.h"

int main(){
    std::cout<<"aaa"<<std::endl;

    Carte c;
    c.setvaleur(2);
    c.setcouleur("Coeur");

    std::cout <<c.getcouleur()<< std::endl;
    std::cout <<c.getvaleur()<< std::endl;
    return 0;
}