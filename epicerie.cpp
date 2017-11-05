/*  AUTEUR(S):
    1) Nom + Code permanent du l'étudiant.e 1
    2) Nom + Code permanent du l'étudiant.e 2
*/
#include <iostream>
#include "epicerie.h"
#include "arbremap.h"
#include "date.h"
#include "pointst.h"
#include <limits>
#include <math.h> 

// =============== Contructeurs ===========================

Epicerie::Epicerie()
{
}

Epicerie::Epicerie(string _nom, PointST _position)
	: nom(_nom), position(_position)
{
}

bool Epicerie::operator<(const Epicerie& autre) const{
    
    return(nom < autre.nom);
}
/*bool Epicerie::operator<(const Epicerie& autre1, const Epicerie& autre2){
    
    return(autre1.nom < autre2.nom);
}
*/


void Epicerie::inventaire(Date& dateActuelle) {

	typename ArbreMap<string, Aliment>::Iterateur i = arbreAliments.debut();  
	for(;i;++i)
	{
		i.valeur().inventaire(dateActuelle);
	}
	std::cout << ";";
}

Aliment::Aliment()
{
	nomAliment = " ";
	quantite = 0;
	dateExpiration = Date(0,0,0);
}

Aliment::Aliment(string _nomAliment, int _quantite)
	: nomAliment(_nomAliment), quantite(_quantite)
{
	dateExpiration = Date(0,0,0);
}


Aliment::Aliment(string _nomAliment, int _quantite, Date _date)
	: nomAliment(_nomAliment), quantite(_quantite), dateExpiration(_date)
{
}

void Aliment::inventaire(Date& dateActuelle){

	if(quantite > 0	&& dateActuelle < dateExpiration) // Ne pas afficher les aliments en rupture de stock ou passes date
	{
		std::cout << nomAliment << " " << quantite << " ";
	}
}

void Carte::inventaire(string nomEpicerie){

	arbreEpiceries[nomEpicerie].inventaire(dateActuelle);
	
}

void Carte::insererEpicerie(string nomEpicerie, Epicerie& epicerie) {	
    	
    arbreEpiceries[nomEpicerie] = epicerie;
    	
}

void Carte::insererAliment(string nomEpicerie, string nomAliment, Aliment& aliment) 
{	
    arbreEpiceries[nomEpicerie].insererAliment(nomAliment, aliment);
}
    
void Carte::afficherContenuEpiceries() {
    	
    	typename ArbreMap<string, Epicerie>::Iterateur i = arbreEpiceries.debut();  
		for(;i;++i)
		{
			std::cout << i.valeur() << endl;
		}
}
    
void Carte::peuplerTableauEpiceries() {
    	
    	typename ArbreMap<string, Epicerie>::Iterateur i = arbreEpiceries.debut();  
		for(;i;++i)
		{
			tableauEpiceries.ajouter(i.valeur());
		}
		
		//tableauEpiceries.afficher();
}
    
void Carte::genererCombinaisons(int nbMaxEpicerie) {
    	
    	Tableau<int> tableauIndicesEpiceries;
    	Pile<int> combinaisonIndices;
    	
    	for(int i = 0; i < tableauEpiceries.taille(); i++)
    	{
    		tableauIndicesEpiceries.ajouter(i);
    	}
    	
    	for(int nbElementsCombinaison = 1; 
    	nbElementsCombinaison <= (nbMaxEpicerie < tableauEpiceries.taille() ? nbMaxEpicerie : tableauEpiceries.taille()); 
    	nbElementsCombinaison++)
    	{
    		combiner(0,nbElementsCombinaison, tableauIndicesEpiceries, combinaisonIndices);
    	}
    	
    	// Affichage des combinaisons
    	/*
    	for(int j = 0; j < tableauCombinaisons.taille(); j++)
    		tableauCombinaisons[j].afficher();
    	*/
    	
}
    
void Carte::combiner(int offset, int k, Tableau<int>& tableauIndicesEpiceries, Pile<int>& combinaisonIndices) {
	
		if (k == 0) {
			tableauCombinaisons.ajouter(combinaisonIndices);
			return;
	  	}
	  	
		for (int i = offset; i <= tableauIndicesEpiceries.taille() - k; ++i) {
			combinaisonIndices.empiler(tableauIndicesEpiceries[i]);
			combiner(i+1, k-1,tableauIndicesEpiceries, combinaisonIndices);
			combinaisonIndices.depiler();
	  	}
}
	
	
void Carte::evaluerCombinaisons(Commande& cmd) {
		
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
		
bool Carte::verifierCommandeParCombinaison(Pile<int> combinaison, Commande cmdCopie) {
		
		while(!combinaison.vide())
		{
			int indiceEpicerie = combinaison.depiler();
			Epicerie epicerie = tableauEpiceries[indiceEpicerie];
			
			typename ArbreMap<string, Aliment>::Iterateur i = cmdCopie.arbreAliments.debut();  
			for(;i;++i)
			{
				if(epicerie.arbreAliments.contient(i.cle()) &&
					dateActuelle < epicerie.arbreAliments[i.cle()].dateExpiration)
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
	
void Carte::trouverCheminLePlusCourt(PointST positionInitiale, double distanceTotalMax) {
	
		transfertPileTableau();
		
		genererPermutations();
		
		
		// Test
		/*
		std::cout << positionInitiale << std::endl;
		std::cout << tableauEpiceries[1].position << std::endl;
		
		double dist2 = positionInitiale.distance(tableauEpiceries[1].position);
		std::cout << "TEST " << dist2 << std::endl;
		*/
		
		
		//double distanceMin = std::numeric_limits<double>::max();
		double distanceMin = distanceTotalMax;  
		int indiceComboOptimal = 0, indicePermutOptimal = 0;
		Tableau<int> indicesEpiceriesAVisiter;
		
		for(int combo = 0; combo < combinaisonsPossibles.taille(); combo++)
		{
			for(int permut = 0; permut < tableauPermutations[combo].taille(); permut++)
			{
				double distance = 0;
				PointST pointPrecedent = positionInitiale;
		
				for(int h = 0; h < tableauPermutations[combo][permut].taille(); h++)
				{
					int indiceEpicerie = tableauPermutations[combo][permut][h];
					string epicerieAVisiter = tableauEpiceries[indiceEpicerie].nom;	// Changer
					//cout << epicerieAVisiter;
				
					distance = distance + pointPrecedent.distance(arbreEpiceries[epicerieAVisiter].position);
				
					pointPrecedent = arbreEpiceries[epicerieAVisiter].position;
			
				}
				
				distance += pointPrecedent.distance(positionInitiale);
				
				//cout << "Dist:" << distance << std::endl;
			
				if(distance < distanceMin)
				{
					distanceMin = distance;
					indiceComboOptimal = combo;
					indicePermutOptimal = permut;
				}
			}
		}
		
		//if(distanceMin == std::numeric_limits<double>::max())
		if(distanceMin == distanceTotalMax)
		{
			std::cout << "0m IMPOSSIBLE";	
		}
		else
		{
			indicesEpiceriesAVisiter = tableauPermutations[indiceComboOptimal][indicePermutOptimal];
			cout << round(distanceMin) << "m" << " ";
		
			// Afficage des epiceries
			for(int h = 0; h < indicesEpiceriesAVisiter.taille(); h++)
			{
				std::cout << tableauEpiceries[indicesEpiceriesAVisiter[h]].nom << " ";
			}
	
		}
}
	
void Carte::transfertPileTableau() {
	
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
	
	
void Carte::genererPermutations() {
    	
    	for(int i = 0; i < combinaisonsPossibles.taille(); i++)
    	{
    		tableauPermutations.ajouter(Tableau<Tableau<int> >());
    		permuter(combinaisonsPossibles[i].taille(), combinaisonsPossibles[i].taille(), combinaisonsPossibles[i], i);
    	}
    	
  
 		//Afficher
 		/*
    	for(int i = 0; i < combinaisonsPossibles.taille(); i++)	// QUESTION
    	{
    		for(int j = 0; j < tableauPermutations[i].taille(); j++)
    		{
    			(tableauPermutations[i][j]).afficher();
    		}
    	}
    	*/
    	
}
    
void Carte::permuter(int k, int taille, Tableau<int>& tabCombinaison, int indiceCombinaison) {
	
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
	
void Carte::echanger(int x, int y, Tableau<int>& tabCombinaison) {
	
		int temp = tabCombinaison[x];
		tabCombinaison[x] = tabCombinaison[y];
		tabCombinaison[y] = temp;
		
		return;
}

void Carte::viderTableaux() {
	
	tableauEpiceries.vider();
    tableauCombinaisons.vider();
    tableauCombinaisonsPossibles.vider();
    combinaisonsPossibles.vider();
    tableauPermutations.vider();
}

void Carte::ramasserProduits(Tableau<string>& tabEpiceries, Commande cmdCopie) {
		
	for(int i = 0; i < tabEpiceries.taille(); i++)
	{		
		typename ArbreMap<string, Epicerie>::Iterateur iterEpicerie = arbreEpiceries.rechercher(tabEpiceries[i]);
		
		if(!iterEpicerie)
			continue;
		
		typename ArbreMap<string, Aliment>::Iterateur iterCmd = cmdCopie.arbreAliments.debut();  
		for(;iterCmd;++iterCmd)
		{
			if(iterEpicerie.valeur().arbreAliments.contient(iterCmd.cle()) &&
				dateActuelle < iterEpicerie.valeur().arbreAliments[iterCmd.cle()].dateExpiration)	// Pour chaque aliment
			{
				// Si l'epicerie possede l'aliment en plus petite quantite que celle requise par la commande
				if(cmdCopie.arbreAliments[iterCmd.cle()].quantite -
					iterEpicerie.valeur().arbreAliments[iterCmd.cle()].quantite >= 0)
				{
					// Soustraire la quantite disponible de la commande
					cmdCopie.arbreAliments[iterCmd.cle()].quantite -=
					iterEpicerie.valeur().arbreAliments[iterCmd.cle()].quantite;
					
					// Enlever la quantite de l'inventaire de l'epicerie
					iterEpicerie.valeur().arbreAliments[iterCmd.cle()].quantite = 0;
				}
				else // Si l'epicerie possede l'aliment en plus grande quantite que celle requise par la commande
				{
					// Enlever la quantite de l'inventaire de l'epicerie
					iterEpicerie.valeur().arbreAliments[iterCmd.cle()].quantite -=
					cmdCopie.arbreAliments[iterCmd.cle()].quantite;
					
					// La commande est terminee
					cmdCopie.arbreAliments[iterCmd.cle()].quantite = 0;
				}
			}	
		}
	}	
	
	// Affichage ==============================================
	
	bool manque = false;
		
	typename ArbreMap<string, Aliment>::Iterateur k = cmdCopie.arbreAliments.debut();  
	for(;k;++k)
	{
		if(cmdCopie.arbreAliments[k.cle()].quantite > 0)
		{
			if(!manque)
				std::cout << "MANQUE";
			std::cout << " " << cmdCopie.arbreAliments[k.cle()].nomAliment << 
				" " << cmdCopie.arbreAliments[k.cle()].quantite;
			manque = true;
		}
	}
	if(!manque)
		std::cout << "COMPLET";
}
	

// =============== Fonctions amies =========================

istream& operator>>(istream& is, Commande& c){
    string nomproduit;
    is >> nomproduit;
    while(is && nomproduit!=";"){
		int quantite;
		is >> quantite;
		// À compléter: faire quelque chose avec c 
		
		Aliment alimentAjouter(nomproduit, quantite);
		c.arbreAliments[nomproduit] = alimentAjouter;
		
		is >> nomproduit;
    }
    return is;
}

ostream& operator << (ostream& os, const Epicerie& epicerie)
{ 
    os 	<< epicerie.nom << std::endl;
    
    epicerie.arbreAliments.afficher();
    
    return os;
}

ostream& operator << (ostream& os, const Aliment& aliment)
{ 
    os 	<< aliment.nomAliment << " " << aliment.quantite << " " << aliment.dateExpiration;
    
    return os;
}



