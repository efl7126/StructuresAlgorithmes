/*  AUTEUR(S):
    1) Nom + Code permanent du l'étudiant.e 1
    2) Nom + Code permanent du l'étudiant.e 2
*/

#include "date.h"
#include <cstdio>
#include <iomanip>
#include <assert.h>

Date::Date()
{
	annee = 2000;
	mois = 1;
	jour = 1;
}

Date::Date(int _annee, int _mois, int _jour)
	: annee(_annee), mois(_mois), jour(_jour)
{
}

Date& Date::operator = (const Date& autre){
    
    annee = autre.annee;
    mois = autre.mois;
    jour = autre.jour;
    
    return *this;
}

bool Date::operator <(const Date& d) const{

	if(annee < d.annee)
		return true;
	else if(annee == d.annee && mois < d.mois)
	{
		return true;
	}
	else if(annee == d.annee && mois == d.mois && jour < d.jour)
	{
		return true;
	}
	
    return false;
}

bool Date::operator <=(const Date& d) const{

	if(annee < d.annee)
		return true;
	else if(annee == d.annee && mois < d.mois)
	{
		return true;
	}
	else if(annee == d.annee && mois == d.mois && jour < d.jour)
	{
		return true;
	}
	else if(annee == d.annee && mois == d.mois && jour == d.jour)
	{
		return true;
	}
	
    return false;
}

std::ostream& operator << (std::ostream& os, const Date& d){
    //int a=2017, m=10, j=17; // <<=== utilisez le paramètre d au lieu de 2017-10-17
    char chaine[40];
    sprintf(chaine, "%04d-%02d-%02d", d.annee, d.mois, d.jour);
    os << chaine;
    return os;
}

std::istream& operator >> (std::istream& is, Date& d){
    //int a=0, m=0, j=0;
    char t1=0,t2=0;
    is >> d.annee >> t1 >> d.mois >> t2 >> d.jour;
    assert(t1=='-');
    assert(t2=='-');
    // À compléter: transférez les valeur a,m,j dans l'objet d.
    return is;
}

