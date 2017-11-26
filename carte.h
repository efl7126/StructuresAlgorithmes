/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    Lab12
    Fichier de départ carte.h © Éric Beaudry (beaudry.eric@uqam.ca).
    http://ericbeaudry.ca/INF3105/lab12/ */

#if !defined(__CARTE_H__)
#define __CARTE_H__

#include <cassert>
#include <istream>
#include <list>
#include <set>
#include <string>
#include "pointst.h"
#include "graphe.h"
using namespace std;

class Carte{
  public:
  	// osmid c'est le nom de notre noeud
    void ajouter_noeud(long osmid, const PointST& p);
    void ajouter_route(const string& nom, const list<long>& noeuds);
    
    set<long> trouver_noeuds_inutiles();	// const enleve

    // À compléter (vous pouvez tout changer).
    
    
    // Recherche en profondeur
    // Tarjan

  private:
    // À compléter. // Pas besoin de changer (point de question)
    Graphe<long> graphe;
    

  friend istream& operator >> (istream& is, Carte& carte);
};

#endif
