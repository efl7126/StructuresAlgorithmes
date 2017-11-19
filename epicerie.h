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
#include "pile.h"

using namespace std;

// Déclaration de la classe Carte, qui contient un arbre comprenant toutes les
// épiceries placées.
class Carte;


class Aliment{
  public:
    
    // Constructeurs
    Aliment();
    Aliment(string _nomAliment, int _quantite);
    Aliment(string _nomAliment, int _quantite, Date _date);
    
    // Autres méthodes
    int inventaire(Date& dateActuelle);
    bool operator<(const Aliment& autre) const;
    
    Date& getDateExpiration() {return dateExpiration;}
    int& getQuantite() {return quantite;}
    string& getNomAliment() {return nomAliment;}
    
    friend class Carte; // Essayer d'enlever
    
  private:
   
    string nomAliment;
    int quantite;
    Date dateExpiration;
    
    friend ostream& operator << (ostream& os, const Aliment& aliment);
};

class Commande{
  public:
    
    ArbreMap<string, Aliment>& getArbreAliments() {return arbreAliments;}
    
  private:
    
    ArbreMap<string, Aliment> arbreAliments;
    
    friend istream& operator>>(istream& is, Commande& c);
    friend class Carte; // Essayer d'enlever
};



class Epicerie{

  public:
    // Constructeurs
    Epicerie();
    Epicerie(string nom, PointST position);
    
    // Autres méthodes
    void insererAliment(const string& nomAliment, const int& quantite, const Date& dateExpiration);
    void inventaire(Date& dateActuelle);
    
    bool operator<(const Epicerie& autre) const;
    
    string& getNom() {return nom;}
    ArbreMap<string, ArbreMap<Date, Aliment> >& getArbreAliments() {return arbreAliments;}
    
  private:
    
    // Arbre Map qui contient les aliments disponibles dans l'epicerie, accessibles
    // à partir d'une clé de type string. La valeur est de type ArbreMap<Date, Aliment>
    // et permet donc de contenir les aliments en fonction de leur date d'expiration.
    ArbreMap<string, ArbreMap<Date, Aliment> > arbreAliments;	 
    
    string nom;
    PointST position;
    
    friend ostream& operator << (ostream& os, const Epicerie& epicerie);
    friend class Carte; // Essayer d'enlever
};



class Carte{
  public:
   
   	// 1) Méthodes associées à la commande DATE 
    void fixerDateActuelle(Date& date) {dateActuelle = date;}
    
    // 2) Méthodes associées à la commande PLACER
    void insererEpicerie(string& nomEpicerie, PointST& position); 
    
    // 3) Méthodes associées à la commande INVENTAIRE  
    void inventaire(string nomEpicerie);
    
    // 4) Méthodes associées à la commande RECOMMANDER
    void peuplerTableauEpiceries(bool premierPlacement);
    void genererCombinaisons(int nbMaxEpicerie, int nbMaxEpiceriePrecedent);
    void combiner(int offset, int k, Tableau<int>& tableauIndicesEpiceries, Pile<int>& combinaisonIndices);
	void evaluerCombinaisons(Commande& cmd, int nbMaxEpiceries);	
	bool verifierCommandeParCombinaison(Pile<int> combinaison, Commande cmdCopie, int nbMaxEpiceries);
	void trouverCheminLePlusCourt(PointST positionInitiale, double distanceTotalMax);
	void genererPermutations();
    void permuter(int k, int taille, Tableau<int> tabCombinaison, int indiceCombinaison);
	void echanger(int x, int y, Tableau<int>& tabCombinaison);
	void viderTableaux();
	void viderTableauCombinaisons();
	
	// 5) Méthodes associées à la commande RAMASSER
	void ramasserProduits(Tableau<string>& tabEpiceries, Commande cmdCopie);
	
	// 6) Méthodes optionnelles d'affichage
	void afficherContenuEpiceries();
    
    ArbreMap<string, Epicerie>& getArbreEpiceries() {return arbreEpiceries;}
    
  private:
    
    Date dateActuelle;
    ArbreMap<string, Epicerie> arbreEpiceries;
    
    // Tableau de pointeurs vers les épiceries contenues dans arbre Epiceries
    Tableau<Epicerie*> tableauEpiceries;
    // Tableau contenant toutes les combinaisons possibles d'épiceries					
    Tableau<Tableau<int> > tableauCombinaisons;
    // Tableau contenant toutes les combinaisons d'épiceries qui permettent de remplir la commande actuelle	
    Tableau<Tableau<int> > tableauCombinaisonsPossibles;
    // Tableau contenant toutes les permutations d'épiceries générées à partir de tableauCombinaisonsPossibles
    Tableau<Tableau<Tableau<int> > > tableauPermutations;
    
};

#endif
