/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    Lab12
    Fichier iocarte.cpp © Éric Beaudry (beaudry.eric@uqam.ca).
    http://ericbeaudry.ca/INF3105/lab12/ */

#include <cassert>
#include <cstdlib>
#include "carte.h"

/* Lire une carte. 
   Normalement, vous n'aurez pas à modifier ceci.
*/
istream& operator >> (istream& is, Carte& carte)
{
    int countnoeuds=0, countroutes=0, countrefs=0;
    // Lire les lieux
    while(is){
        string nomlieu;
        long osmid;
        is >> nomlieu;
        if(nomlieu == "---") break;
        assert(nomlieu[0]=='n');
        osmid = atol(nomlieu.c_str()+1);
        PointST point;
        char pv;
        is >> point >> pv;
        assert(pv==';');
        carte.ajouter_noeud(osmid, point);
        countnoeuds++;
    }

    // Lire les routes
    while(is){
        string nomroute;
        is >> nomroute;
        if(nomroute == "---") break;
        
        char deuxpoints;
        is >> deuxpoints;
        assert(deuxpoints == ':');
        
        std::list<long> listenomslieux;
        while(is){
            string nomlieu;
            is>>nomlieu;
            if(nomlieu==";") break;
            assert(nomlieu!=":"); // pour robustesse
            assert(nomlieu.find(";")==string::npos); // pour robustesse
            long osmid;
            assert(nomlieu[0]=='n');
            osmid = atol(nomlieu.c_str()+1);
            listenomslieux.push_back(osmid);
            countrefs++;
        }
        carte.ajouter_route(nomroute, listenomslieux);
        countroutes++;
    }
    cerr << "Carte chargée: " << countnoeuds << " noeuds; " << countroutes << " routes; " << countrefs << " références." << endl;

    return is;
}

