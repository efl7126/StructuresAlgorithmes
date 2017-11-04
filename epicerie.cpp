/*  AUTEUR(S):
    1) Nom + Code permanent du l'étudiant.e 1
    2) Nom + Code permanent du l'étudiant.e 2
*/
#include <iostream>
#include "epicerie.h"
#include "arbremap.h"
#include "date.h"

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


void Epicerie::inventaire() {

	typename ArbreMap<string, Aliment>::Iterateur i = arbreAliments.debut();  
	for(;i;++i)
	{
		i.valeur().inventaire();
	}
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

void Aliment::inventaire(){

	if(quantite > 0)	// Ne pas afficher les aliments en rupture de stock
		std::cout << nomAliment << " " << quantite << " ";
	
}

void Carte::inventaire(string nomEpicerie){

	arbreEpiceries[nomEpicerie].inventaire();
	
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



