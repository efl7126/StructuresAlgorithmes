/*  INF3105 - Structures de données et algorithmes
    Lab 11 -- Graphes / Représentations et algorithmes de base
    http://ericbeaudry.uqam.ca/INF3105/lab11/
*/
#if !defined(__GRAPHE_H__)
#define __GRAPHE_H__

#include <queue>
#include <map>
#include <set>
#include <stack>
#include <iostream>

using namespace std;

// Le type S est le type utilisé pour identifier les sommets
template <class S>
class Graphe{
  public:
    // Interface public pour créer le graphe.
    void ajouterSommet(const S& s);
    void ajouterAreteOrientee(const S& s1, const S& s2);
    void ajouterAreteNonOrientee(const S& s1, const S& s2);

    // Interface public pour les requêtes de base.
    // Amélioration possible : retourner le résultat au lieu de faire l'affichage à l'interne.
    void parcoursRechercheProfondeur(const S& s) const;
    void parcoursRechercheLargueur(const S& s) const;
   
    void extraireCompostantesConnexes() const;
	void tarjan(queue<set<S> >& partition);
	void tarjanAffichage(queue<set<S> >& partition);

	
  private:
  
  	void parcoursRechercheProfondeur2(const S& s, set<S>& sommets_visites) const;
  	set<S> parcoursRechercheLargeurExtraction(const S& s, 
		set<S>& sommets_visites) const;
  
    struct Sommet{
        // À compléter.
        //Coordonnee coor; // variable inutile pour le Lab12, mais utile pour le TP3.
        set<S> voisins; // ensemble des sommets accessibles via les arêtes sortantes du sommet.
                        // Cela est légèrement différent de la page 120 des notes de cours.
                        // C'est voulu, car ici les arêtes ne sont pas étiquetées par un poids (ex: distance).
                        // Pour attacher une étiquette, il suffirait de modifier pour : map<S, A> sortants;
         
        S nom;
        int num;
        int min;
                        
    };
    
    void tarjanParcoursProfondeur(Sommet& v, int& compteur, stack<S>& chemin, 
	queue<set<S> >& partition);
    
    map<S, Sommet> sommets; // identification --> sommet
};

template <class S>
void Graphe<S>::ajouterSommet(const S& s){
    // À compléter.
    
    /*
    Graphe::Sommet sommetAjouter;
    
    sommets[s] = sommetAjouter;
    */
    
    Sommet ajout;
    ajout.nom = s;
    sommets[s] = ajout;
    // sommets[s].nom = s;	Pourquoi!
}

template <class S>
void Graphe<S>::ajouterAreteNonOrientee(const S& s1, const S& s2){
    // À compléter.
    // Doit ajouter les 2 arêtes orientées : s1->s2 et s2->s1;
    
    sommets[s1].voisins.insert(s2);
    sommets[s2].voisins.insert(s1);
    
}

template <class S>
void Graphe<S>::ajouterAreteOrientee(const S& s1, const S& s2){
    // À compléter.
    // Doit uniquement ajouter s1->s2.
    
    sommets[s1].voisins.insert(s2);
}

template <class S>
void Graphe<S>::parcoursRechercheProfondeur(const S& s) const{
    // À compléter.
    // Vous devrez implémenter des marqueurs «visité» sur les sommets.
    
    /*
    set 
    file.push(s);
    while(!file.empty())
    {
    	S suivant = file.top();
    	file.pop();
    	const Sommet& sommet = sommets.at(suivant);
    	if(visites.find(sommet) != visites.end()) continue;
    	visites.insert(sommet);
    	cout << suivant << " ";
    	stack<S> sfile;
    	
    	for(typename set<S>::const_iterator iter=sommet.voisins.begin();iter!=sommet.voisins.end();++iter)
    		sfile.push(*iter); 
    		
    	while(!
    */
    
    set<S> sommets_visites;
    
    parcoursRechercheProfondeur2(s, sommets_visites);
    
    cout << endl;
    
}

template <class S>
void Graphe<S>::parcoursRechercheProfondeur2(const S& s, set<S>& sommets_visites) const{

    cout << s << " ";
  	sommets_visites.insert(s);
  	
  	const Graphe::Sommet& sommet_a_visiter = sommets.at(s);
  	
  	for(typename set<S>::const_iterator iter=sommet_a_visiter.voisins.begin();
  	    		iter!=sommet_a_visiter.voisins.end();++iter)
  	{
  		S w = *iter;
  		
  		if(!(sommets_visites.count(w) > 0))
  			parcoursRechercheProfondeur2(w, sommets_visites);
  	}
    		
    
}

template <class S>
void Graphe<S>::parcoursRechercheLargueur(const S& s) const{
    // À compléter.
    // Vous devrez implémenter des marqueurs «visité» sur les sommets.
    // Il est recommendé d'utiliser la file std::queue de la bibliothèque standard de C++.
    // Voir : http://en.cppreference.com/w/cpp/container/queue
    
    // Option 3 - Ensemble (set) temporaire enumerant les sommets visites
    
    set<S> sommets_visites;
    queue<S> sommets_a_visiter;	// File
    
    sommets_visites.insert(s);	// Le premier noeud est visite (bool = true)
    sommets_a_visiter.push(s);	// Enfiler
    
    while(!sommets_a_visiter.empty())
    {
    	S suivant = sommets_a_visiter.front();
    	sommets_a_visiter.pop();	// s = file.defiler()
    	cout << suivant << " ";		// Affichage 
    	
    	const Graphe::Sommet& refSuivant = sommets.at(suivant);
    	
    	for(typename set<S>::const_iterator iter=refSuivant.voisins.begin();
  	    		iter!=refSuivant.voisins.end();++iter)
  	    {
  			S w = *iter;
  		
  			if(!(sommets_visites.count(w) > 0))
  			{
  				sommets_visites.insert(w);	// Le noeud est visite 
  				sommets_a_visiter.push(w);
  			}
  		}
    	
    }
    
    cout << endl;
    
}


template <class S>
set<S> Graphe<S>::parcoursRechercheLargeurExtraction(const S& s, 
		set<S>& marqueurs) const{

	set<S> sommets_visites;
    queue<S> sommets_a_visiter;	// File
    
    sommets_visites.insert(s);	// Le premier noeud est visite (bool = true)
    sommets_a_visiter.push(s);	// Enfiler
    
    while(!sommets_a_visiter.empty())
    {
    	S suivant = sommets_a_visiter.front();
    	sommets_a_visiter.pop();	// s = file.defiler()
    	//cout << suivant << " ";		// Affichage 
    	
    	const Graphe::Sommet& refSuivant = sommets.at(suivant);
    	
    	for(typename set<S>::const_iterator iter=refSuivant.voisins.begin();
  	    		iter!=refSuivant.voisins.end();++iter)
  	    {
  			S w = *iter;
  		
  			if(!(marqueurs.count(w) > 0))
  			{
  				marqueurs.insert(w);
  				sommets_visites.insert(w);	// Le noeud est visite 
  				sommets_a_visiter.push(w);
  			}
  		}
    	
    }
    
    //cout << endl;
    
    return sommets_visites;
    
}


template <class S>
void Graphe<S>::extraireCompostantesConnexes() const{
    // À compléter.
    // Ne faites que l'extraction simple en premier (plus simple que l'extraction de composantes *fortement* connexes).
    
    
    
    set<S> marqueurs;
    queue<set<S> > sommets_composantes_connexes;
    
  	
  	for(typename map<S, Sommet>::const_iterator iter=sommets.begin();
  	    		iter!=sommets.end();++iter)
  	{
  		if(marqueurs.count(iter->first) > 0)
  			continue;
  			
  		set<S> sommets_visites;
  		sommets_visites = parcoursRechercheLargeurExtraction(iter->first, marqueurs);
  		sommets_composantes_connexes.push(sommets_visites);
    }
    
    
  	
    // Affichage
    
    cout << "{";
    while(!sommets_composantes_connexes.empty())
    {
    	set<S> composante = sommets_composantes_connexes.front();
    	sommets_composantes_connexes.pop();
    
  		cout << "{";
	    for(typename set<S>::iterator iter=composante.begin(); iter!=composante.end();)
	  	{
	  		cout << *iter;
	  		if(++iter != composante.end())
	  			cout << ",";
	  		
		}
		cout << "}";
		
		if(!sommets_composantes_connexes.empty())
			cout << ",";
		
    }
    cout << "}" << endl;
   
}


template <class S>
void Graphe<S>::tarjan(queue<set<S> >& partition) {
	
	int compteur = 0;
	
	// Initialiser les numerateurs a -1
	for(typename map<S, Sommet>::iterator iter=sommets.begin();
  	    		iter!=sommets.end();++iter)
  	{
  		//Sommet& v = iter->second;
  		(iter->second).num = -1;
  	}
  	
  	stack<S> chemin;
  	
  	// Parcourir les noeuds
	for(typename map<S, Sommet>::iterator iter=sommets.begin();
  	    		iter!=sommets.end();++iter)
  	{
  		Sommet& v = iter->second;
  		
  		if(v.num == -1)
  			tarjanParcoursProfondeur(v, compteur, chemin, partition);
  		
  	}

}


template <class S>
void Graphe<S>::tarjanParcoursProfondeur(Sommet& v, int& compteur, stack<S>& chemin, 
	queue<set<S> >& partition) {
	
	v.num = compteur++;
	v.min = v.num;
	chemin.push(v.nom);
	
	//cout << v.nom << " :";
	
	
	
	// Parcourir les arretes sortantes
	for(typename set<S>::iterator iter=v.voisins.begin();
  	    		iter!=v.voisins.end();++iter)
  	{
  	
  		S w_nom = *iter;
  		Sommet& w = sommets[w_nom]; // Changer (log N)
  		
  		//cout << w_nom;
  		
  		if(w.num == -1)
  		{
  			tarjanParcoursProfondeur(w, compteur, chemin, partition);
  			
  			if(v.min > w.min)	// Minimum
  				v.min = w.min;
  		}
  	  
  	  	
  		else
  		{	
  			// Chercher si w appartient a chemin
  			stack<S> stackCopy = chemin;
  			
  			while(!(stackCopy.empty()))
  			{
  				S suivant = stackCopy.top();
    			stackCopy.pop();
    			
    			
    			if(suivant == w_nom)
    			{
    				if(v.min > w.num)	// Minimum
  						v.min = w.num;
    				break;
    			}
    			
    		
  			}
  			
  		}
  		
  
  	}
	//cout << endl;
	
	
	
	if(v.num == v.min)
	{
		set<S> noeuds_a_parcourir;
		S suivant;
		while(!chemin.empty())
  		{
  			suivant = chemin.top();
  			noeuds_a_parcourir.insert(suivant);
  			chemin.pop();
  			if(v.nom == suivant)
  				break;
  		}
  		
  		partition.push(noeuds_a_parcourir);
	}
	
	
	
}

template <class S>
void Graphe<S>::tarjanAffichage(queue<set<S> >& partition) {

    while(!partition.empty())
    {
    	set<S> composante = partition.front();
    	partition.pop();

	    for(typename set<S>::iterator iter=composante.begin(); iter!=composante.end(); iter++)
	  		cout << *iter << "  ";	
    }
    cout << endl;
}

#endif


