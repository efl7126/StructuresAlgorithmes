/*  AUTEUR(S):
    1) Nom + Code permanent du l'étudiant.e 1
    2) Nom + Code permanent du l'étudiant.e 2
*/
#if !defined(_EPICERIE__H_)
#define _EPICERIE__H_

#include <string>
#include "arbremap.h"
#include "pointst.h"
#include "date.h"
#include "tableau.h"
#include "liste.h"

using namespace std;

class Aliment{
  public:
    // À compléter
    Aliment();
    Aliment(string _nomAliment, int _quantite);
    Aliment(string _nomAliment, int _quantite, Date _date);
    void inventaire();
    friend class Carte; // Essayer d'enlever
    
  private:
    // À compléter
    string nomAliment;
    int quantite;
    Date dateExpiration;
    
    friend ostream& operator << (ostream& os, const Aliment& aliment);
};

class Commande{
  public:
    // À compléter
  private:
    // À compléter
    ArbreMap<string, Aliment> arbreAliments;
    
    friend istream& operator>>(istream& is, Commande& c);
    friend class Carte; // Essayer d'enlever
};

class Epicerie{
  public:
    // À compléter
    Epicerie();
    Epicerie(string nom, PointST position);
    bool operator<(const Epicerie& autre) const;
    //bool operator<(const Epicerie& autre1, const Epicerie& autre2);
    void insererAliment(string nom, Aliment& alimentAInserer) 
    {	
    	arbreAliments[nom] = alimentAInserer;
    }
    void inventaire();
    
  private:
    // À compléter
    
    ArbreMap<string, Aliment> arbreAliments;
    
    string nom;
    PointST position;
    
    friend ostream& operator << (ostream& os, const Epicerie& epicerie);
    friend class Carte; // Essayer d'enlever
};

class Carte{
  public:
    // À compléter
    
    void fixerDateActuelle(Date& date) {dateActuelle = date;}
    
    void insererEpicerie(string nomEpicerie, Epicerie& epicerie) 
    {	
    	arbreEpiceries[nomEpicerie] = epicerie;
    }
    void insererAliment(string nomEpicerie, string nomAliment, Aliment& aliment) 
    {	
    	arbreEpiceries[nomEpicerie].insererAliment(nomAliment, aliment);
    }
    void afficher() {arbreEpiceries.afficher();}
    
    void afficherContenuEpiceries() {
    	
    	typename ArbreMap<string, Epicerie>::Iterateur i = arbreEpiceries.debut();  
		for(;i;++i)
		{
			std::cout << i.valeur() << endl;
		}
    }
    
    void inventaire(string nomEpicerie);
    
    void peuplerTableauEpiceries() {
    	
    	typename ArbreMap<string, Epicerie>::Iterateur i = arbreEpiceries.debut();  
		for(;i;++i)
		{
			tableauEpiceries.ajouter(i.valeur());
		}
		
		//tableauEpiceries.afficher();
    }
    
    void genererCombinaisons() {
    	
    	for(int i = 0; i < tableauEpiceries.taille(); i++)
    	{
    		tableauIndicesEpiceries.ajouter(i);
    	}
    	
    	for(int nbElementsCombinaison = 1; nbElementsCombinaison <= tableauEpiceries.taille(); nbElementsCombinaison++)
    	{
    		combiner(0,nbElementsCombinaison);
    	}
    	
    	// Affichage des combinaisons
    	/*
    	for(int j = 0; j < tableauCombinaisons.taille(); j++)
    		tableauCombinaisons[j].afficher();
    	*/
    	
    }
    
    void combiner(int offset, int k) {
	
		if (k == 0) {
			tableauCombinaisons.ajouter(combinaisonIndices);
			return;
	  	}
	  	
		for (int i = offset; i <= tableauIndicesEpiceries.taille() - k; ++i) {
			combinaisonIndices.empiler(tableauIndicesEpiceries[i]);
			combiner(i+1, k-1);
			combinaisonIndices.depiler();
	  	}
	}
	
	
	void evaluerCombinaisons(Commande& cmd) {
		
		for(int i = 0; i < tableauCombinaisons.taille(); i++)
    	{
    		if(verifierCommandeParCombinaison(tableauCombinaisons[i], cmd))
    		{
    			tableauCombinaisonsPossibles.ajouter(tableauCombinaisons[i]);
    		}
    	}
    	
    	// Affichage des combinaisons
    	/*for(int j = 0; j < tableauCombinaisonsPossibles.taille(); j++)
    		tableauCombinaisonsPossibles[j].afficher();
    	*/
    	
	}
		
	bool verifierCommandeParCombinaison(Pile<int> combinaison, Commande cmdCopie) {
		
		while(!combinaison.vide())
		{
			int indiceEpicerie = combinaison.depiler();
			Epicerie epicerie = tableauEpiceries[indiceEpicerie];
			
			typename ArbreMap<string, Aliment>::Iterateur i = cmdCopie.arbreAliments.debut();  
			for(;i;++i)
			{
				if(epicerie.arbreAliments.contient(i.cle()))
				{
					cmdCopie.arbreAliments[i.cle()].quantite -= epicerie.arbreAliments[i.cle()].quantite;
				}	
			}
		}
		
		typename ArbreMap<string, Aliment>::Iterateur k = cmdCopie.arbreAliments.debut();  
		for(;k;++k)
		{
			if(cmdCopie.arbreAliments[k.cle()].quantite > 0)
				return false;
		}
		
		return true;
	}
	
	void trouverCheminLePlusCourt() {
	
		transfertPileTableau();
		
		/*
		for (int combo = 0; combo < combinaisonsPossibles.taille(); combo++)
		{
			
			for(int epi = 0; epi < combinaisonsPossibles[combo].taille(); epi++)
			{
			
			}
		}
		*/
		
		genererPermutations();
		
	}
	
	void transfertPileTableau() {
	
		for(int i = 0; i < tableauCombinaisonsPossibles.taille(); i++)
    	{
    		Tableau<int> tab;
    		while(!tableauCombinaisonsPossibles[i].vide())
    		{
    			int element = tableauCombinaisonsPossibles[i].depiler();
    			tab.ajouter(element);
    		}
    			
    		combinaisonsPossibles.ajouter(tab);
    	}
    	
    	//Afficher
    	/*
    	for(int j = 0; j < combinaisonsPossibles.taille(); j++)
    		combinaisonsPossibles[j].afficher();
    	*/
	}
	
	
	void genererPermutations() {
    	
    	for(int i = 0; i < combinaisonsPossibles.taille(); i++)
    	{
    		permuter(combinaisonsPossibles[i].taille(), combinaisonsPossibles[i].taille(), combinaisonsPossibles[i], i);
    	}
    	
 		//Afficher
    	for(int i = 0; i < tableauPermutations.taille(); i++)
    	{
    		for(int j = 0; j < tableauPermutations[i].taille(); j++)
    		{
    			(tableauPermutations[i][j]).afficher();
    		}
    	}
    	
    }
    
    void permuter(int k, int taille, Tableau<int>& tabCombinaison, int indiceCombinaison) {
	
		if (k == 0) {
			tableauPermutations[indiceCombinaison].ajouter(tabCombinaison);
			//tabCombinaison.afficher();
			/*for(int i = 0; i < tableauPermutations[indiceCombinaison].taille(); i++)
			{
				tableauPermutations[indiceCombinaison][i].afficher();
				std::cout << std::endl;
			}
			*/
	  	}
	  	else
	  	{
			for (int i = k - 1; i >= 0; i--) {
				echanger(i,k-1,tabCombinaison);
				permuter(k-1,taille,tabCombinaison,indiceCombinaison);
				echanger(i,k-1,tabCombinaison);
		  	}
		}
		
		return;
	}
	
	void echanger(int x, int y, Tableau<int>& tabCombinaison) {
	
		int temp = tabCombinaison[x];
		tabCombinaison[x] = tabCombinaison[y];
		tabCombinaison[y] = temp;
		
		return;
	}
	
    
  private:
    
    Date dateActuelle;
    ArbreMap<string, Epicerie> arbreEpiceries;
    Tableau<Epicerie> tableauEpiceries;
    Tableau<Pile<int> > tableauCombinaisons;
    Tableau<Pile<int> > tableauCombinaisonsPossibles;
    Tableau<Tableau<int> > combinaisonsPossibles;
    Tableau<Tableau<Tableau<int> > > tableauPermutations;
    
    // Pour la generation de combinaisons
    Tableau<int> tableauIndicesEpiceries;
    Pile<int> combinaisonIndices;
    
};

#endif
