/*  INF3105 - Structures de données et algorithmes       *
 *  UQAM / Département d'informatique                    *
 *  Automne 2017 / TP1                                   *
 *  http://ericbeaudry.uqam.ca/INF3105/tp1/              */

#include <fstream>
#include <iostream>
#include <math.h>
#include <string>
#include "bixi.h"


int tp1(Reseau& reseau, std::istream& entree);


// argc: nombre d'arguments passés.
// argv: tableau de chaines de carractères.
// exemple: ./tp1 montreal-bixi.txt montreal-req0.txt
//   argv[0]="./tp1"; argv[1]="montreal-bixi.txt" argv[2]="montreal-req0.txt"

int main(int argc, const char** argv)
{
    if(argc<=1){
        std::cerr << "Erreur. Syntaxe : ./tp1 reseau-bixi.txt [requetes.txt]" << endl;
        return 1;
    }
    std::ifstream fichier_reseau(argv[1]);
    if(fichier_reseau.fail()){
        std::cerr << "Erreur ouverture réseau : " << argv[1] << endl;    
        return 2;
    }

    Reseau reseau;

	// Extraction des stations disponibles dans le réseau à partir d'un fichier texte
    fichier_reseau >> reseau;
    
    if(argc>2){
        // Au moins deux arguments sont passés.
        std::ifstream fichier_entree(argv[2]);
        if(fichier_entree.fail()){
            std::cerr << "Erreur de lecture du fichier '" << argv[1] << "'" << std::endl;
            return 3;
        }
        return tp1(reseau, fichier_entree); 
    }else{
        // Pas d'argument requêtes ==> lecture depuis l'entrée standard avec std::cin.
        return tp1(reseau, std::cin);
    }
}

int tp1(Reseau& reseau, std::istream& entree_requetes){
    
    
    // Cette fonction est utilisée pour créer un tableau générique de deux dimensions servant
    // à stocker le temps requis pour voyager en vélo entre chaque combinaison de deux stations,
    // peu importe les points de départ et d'arrivée.
	reseau.traiterReseau();


	// Lecture des requêtes pour un réseau
    while(entree_requetes){
        
        PointST p1, p2;
        
        // Stockage des coordonnéees de départ et d'arrivée dans deux objets PointST
        entree_requetes >> p1 >> p2;   
    
        if(!entree_requetes) break; // Fin de lecture du fichier texte de requêtes
              
		// Cette fonction effectue les calculs afin de déterminer le trajet optimal
        reseau.traiterRequete(p1, p2);     
        
    }
    
    return 0;
}
