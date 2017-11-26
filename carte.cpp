/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    Lab12
    Fichier de départ carte.cpp © Éric Beaudry (beaudry.eric@uqam.ca).
    http://ericbeaudry.ca/INF3105/lab12/ */

#include "carte.h"

void Carte::ajouter_noeud(long osmid, const PointST& p){
    // À compléter.
    
    graphe.ajouterSommet(osmid);
    
}

void Carte::ajouter_route(const string& nomroute, const list<long>& noeuds){
    // À compléter.
    // Exemple de ligne dans une carte : «Jeanne-Mance : a b c d ; »
    // Donc, route est une séquence (liste) : <a, b, c, d, e>.
    // Il faut alors ajouter les segments de route (arêtes/arcs) : (a,b), (b,c), (c,d), (d,e).
    // Il ne faut pas ajouter (e,d), (d,c), (c,b), (b,a).
    // Les sens uniques doivent être considérées.
    
    long noeudPrecedent;
    
    for(typename list<long>::const_iterator iter=noeuds.begin();
  	    		iter!=noeuds.end();++iter)
  	{
  		if(iter==noeuds.begin())
  		{
  			noeudPrecedent = *iter;
  			continue;
  		}
  		
  		graphe.ajouterAreteOrientee(noeudPrecedent, *iter);
  		
  		noeudPrecedent = *iter;
  	}
    
}

set<long> Carte::trouver_noeuds_inutiles() {
    // À compléter.
    
    queue<set<long> > partition;
    graphe.tarjan(partition);	// Algorithme de Tarjan
    //graphe.tarjanAffichage(partition);
    
    
    set<long> noeudsInutiles;
    set<long> composanteConnexePrincipale;
    
    int tailleCompConnexe = 0, tailleMaxCompConnexe = 0;
    
    while(!partition.empty())
    {
    	set<long> composante = partition.front();
    	partition.pop();
    	
    	// Ajouter les noeuds dans noeudsInutiles
    	noeudsInutiles.insert(composante.begin(), composante.end()); 

	    tailleCompConnexe = composante.size();
	    
	    if(tailleCompConnexe > tailleMaxCompConnexe)
	    {
	    	tailleMaxCompConnexe = tailleCompConnexe;
	    	composanteConnexePrincipale = composante;	// Meilleur?
	    }
    }
    
 	
    
    // Retirer les noeuds de la composanteConnexePrincipale
    for(set<long>::iterator iter = noeudsInutiles.begin(); iter != noeudsInutiles.end();)
    {
    	//cout << "Noeud " << *iter;
    	// Si l'element est dans la composante connexe principale
    	if(composanteConnexePrincipale.find(*iter) != composanteConnexePrincipale.end())
    	{
    		//cout << "Erase ";
    		noeudsInutiles.erase(iter++);
    	}
    	else
    		++iter;
    		
    	//cout << endl;
    }

	
	// Affichage
	/*
	for(typename set<long>::iterator iter=composanteConnexePrincipale.begin(); 
		iter!=composanteConnexePrincipale.end(); iter++)
	{
		cout << *iter << "  ";	
	}
	cout << endl << "--------------------------------" << endl;
	*/
 
    return noeudsInutiles;
    
}



