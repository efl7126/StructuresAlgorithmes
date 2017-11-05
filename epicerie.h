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

class Carte;

class Aliment{
  public:
    // À compléter
    Aliment();
    Aliment(string _nomAliment, int _quantite);
    Aliment(string _nomAliment, int _quantite, Date _date);
    void inventaire(Date& dateActuelle);
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
    void inventaire(Date& dateActuelle);
    
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
    void insererEpicerie(string nomEpicerie, Epicerie& epicerie);
    void insererAliment(string nomEpicerie, string nomAliment, Aliment& aliment);
    void afficher() {arbreEpiceries.afficher();}
    void afficherContenuEpiceries();   
    void inventaire(string nomEpicerie);
    
    void peuplerTableauEpiceries();
    void genererCombinaisons(int nbMaxEpicerie);
    void combiner(int offset, int k, Tableau<int>& tableauIndicesEpiceries, Pile<int>& combinaisonIndices);
	void evaluerCombinaisons(Commande& cmd);	
	bool verifierCommandeParCombinaison(Pile<int> combinaison, Commande cmdCopie);
	
	void trouverCheminLePlusCourt(PointST positionInitiale, double distanceTotalMax);
	void transfertPileTableau();
	void genererPermutations();
    void permuter(int k, int taille, Tableau<int>& tabCombinaison, int indiceCombinaison);
	void echanger(int x, int y, Tableau<int>& tabCombinaison);
	
	void viderTableaux();
	
	void ramasserProduits(Tableau<string>& tabEpiceries, Commande cmdCopie);
    
  private:
    
    Date dateActuelle;
    ArbreMap<string, Epicerie> arbreEpiceries;
    
    Tableau<Epicerie> tableauEpiceries;
    Tableau<Pile<int> > tableauCombinaisons;
    Tableau<Pile<int> > tableauCombinaisonsPossibles;
    Tableau<Tableau<int> > combinaisonsPossibles;
    Tableau<Tableau<Tableau<int> > > tableauPermutations;
    
};

#endif
