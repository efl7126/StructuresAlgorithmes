/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    Lab12
    Fichier de départ lab12.cpp © Éric Beaudry (beaudry.eric@uqam.ca).
    http://ericbeaudry.ca/INF3105/lab12/ */

#include <iostream>
#include <fstream>
#include "carte.h"
#include "graphe.h"

using namespace std;

int main(int argc, const char** argv)
{
    if(argc<=1){
        cout << "Syntaxe: ./lab12 carte.txt" << endl;
        return 1;
    }

    // Lecture de la carte.
    Carte carte;
    {
        ifstream fichiercarte(argv[1]);
        if(fichiercarte.fail()){
            cout << "Erreur ouverture du fichier : " << argv[1] << endl;    
            return 1;
        }
        fichiercarte >> carte;
    }
    
    set<long> noeudsinutiles = carte.trouver_noeuds_inutiles();
    for(set<long>::iterator iter=noeudsinutiles.begin();iter!=noeudsinutiles.end();++iter){
        cout << 'n' << *iter << ' ';
    }
    cout << endl;
    cout << "Nombre de noeuds exclus : " << noeudsinutiles.size() << endl;
    return 0;
}
