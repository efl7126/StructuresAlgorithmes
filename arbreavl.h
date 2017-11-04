/* UQAM / Département d'informatique
   INF3105 - Structures de données et algorithmes
   Squelette pour classe générique ArbreAVL<T> pour le Lab6 et le TP2.

   AUTEUR(S):
    1) Nom + Code permanent du l'étudiant.e 1
    2) Nom + Code permanent du l'étudiant.e 2
*/

#if !defined(_ARBREAVL___H_)
#define _ARBREAVL___H_
#include <cassert>
#include "pile.h"


/*


// ====== Autre Methode =====================

int eb = temp->equilibre;
int ea = racinesousarbre->equilibre;
int nea = -(eb<0 ? eb : 0) + 1 + ea;
int neb = (nea>0 ? nea : 0) + 1 + eb;


 int  ea = temp->equilibre;
 int  eb = racinesousarbre->equilibre;
 int  neb = -(ea>0 ? ea : 0) - 1 + eb;
 int  nea = ea + (neb < 0 ? neb : 0) - 1;
 
 */


template <class T>
class ArbreAVL {
  public:
    ArbreAVL();
    ArbreAVL(const ArbreAVL&);
    ~ArbreAVL();

    void inserer(const T&);
    bool contient(const T&) const;
    bool vide() const;
    void vider();
    void enlever(const T&); // non requis pour le TP2.
    int  hauteur() const;
    void afficher() const;

    // Annonce l'existance d'une classe Iterateur.
    class Iterateur;
    
    // Fonctions pour obtenir un itérateur (position dans l'arbre)    
    Iterateur debut() const;
    Iterateur fin() const;
    Iterateur rechercher(const T&) const;
    Iterateur rechercherEgalOuSuivant(const T&) const;
    Iterateur rechercherEgalOuPrecedent(const T&) const;

    // Accès aux éléments de l'arbre via un intérateur.
    const T& operator[](const Iterateur&) const;
    T& operator[](const Iterateur&);
    
    // Copie d'un arbre AVL.
    ArbreAVL& operator = (const ArbreAVL&);

  private:
    struct Noeud{
        Noeud(const T&);
        T contenu;
        int equilibre;
        Noeud *gauche;
        Noeud *droite;
    };
    Noeud* racine;

    // Fonctions internes.
    bool inserer(Noeud*&, const T&);
    void rotationGaucheDroite(Noeud*&);
    void rotationDroiteGauche(Noeud*&);
    void vider(Noeud*&);
    void copier(const Noeud*, Noeud*&) const;
    const T& max(Noeud*) const;
    bool enlever(Noeud*&, const T& e);

  public:
    // Sera présenté à la semaine #7
    class Iterateur{
      public:
        Iterateur(const ArbreAVL& a);
        Iterateur(const Iterateur& a);
        Iterateur(const ArbreAVL& a, Noeud* c);

        operator bool() const;
        bool operator!() const;
        bool operator==(const Iterateur&) const;
        bool operator!=(const Iterateur&) const;
        
        const T& operator*() const;

        Iterateur& operator++();
        Iterateur operator++(int);
        Iterateur& operator = (const Iterateur&);
      private:
        const ArbreAVL& arbre_associe;
        Noeud* courant;
        Pile<Noeud*> chemin;
        
      friend class ArbreAVL;
    };
};


//-----------------------------------------------------------------------------

// Constructeur par defaut du struct Noeud
template <class T>
ArbreAVL<T>::Noeud::Noeud(const T& c):
contenu(c), equilibre(0), gauche(NULL), droite(NULL)
{
}

// Constructeur par defaut de la classe ArbreAVL
template <class T>
ArbreAVL<T>::ArbreAVL() : racine(NULL)
{
}

// Constructeur par copie de la classe ArbreAVL
template <class T>
ArbreAVL<T>::ArbreAVL(const ArbreAVL<T>& autre) : racine(NULL)
{
    copier(autre.racine, racine);
}

// Destructeur de la classe ArbreAVL
template <class T>
ArbreAVL<T>::~ArbreAVL()
{
    vider(racine);
}


// ================= Fonctions a definir ==========================


template <class T>
bool ArbreAVL<T>::contient(const T& element) const
{
    // À compléter.

	Noeud* noeud = racine;

	// SI egal, renvoyer. SI inferieur, si superieur.

	while(noeud!=NULL)
    {
    	if(element < noeud->contenu)
    		noeud = noeud->gauche;
    	else if(noeud->contenu < element)
    		noeud = noeud->droite;
    	else
    		return true;
    }	  	
   
	return false;	// On est rendu a une feuille et la valeur n'est pas trouvee
}
//OK

template <class T>
void ArbreAVL<T>::inserer(const T& element)
{
    inserer(racine, element);
}
//OK

template <class T>
bool ArbreAVL<T>::inserer(Noeud*& noeud, const T& element)
{
    if(noeud==NULL)
    {
        noeud = new Noeud(element);
        return true;
    }
    
    if(element < noeud->contenu){	// Cas de gauche
        
		if(inserer(noeud->gauche, element))
		{
		    noeud->equilibre++;
		    if(noeud->equilibre == 0) return false;
		    if(noeud->equilibre == 1) return true;
		    assert(noeud->equilibre==2);
		    if(noeud->gauche->equilibre == -1)
		        rotationDroiteGauche(noeud->gauche);
		    rotationGaucheDroite(noeud);
		}
		return false;
	}
	
    else if(noeud->contenu < element){	// Cas de droite
        // À compléter.
        
        if(inserer(noeud->droite, element))
		{
		    noeud->equilibre--;
		    if(noeud->equilibre == 0) return false;
		    if(noeud->equilibre == -1) return true;
		    assert(noeud->equilibre==-2);
		    if(noeud->droite->equilibre == 1)
		        rotationGaucheDroite(noeud->droite);
		    rotationDroiteGauche(noeud);
		}
        
        return false;
    }

    // element == noeud->contenu
    noeud->contenu = element;  // Mise à jour
    return false;
}
//OK

template <class T>
void ArbreAVL<T>::rotationGaucheDroite(Noeud*& racinesousarbre)
{
    Noeud *temp = racinesousarbre->gauche;
    int  ea = temp->equilibre;
    int  eb = racinesousarbre->equilibre;
    int  neb = -(ea>0 ? ea : 0) - 1 + eb;
    int  nea = ea + (neb < 0 ? neb : 0) - 1;

    temp->equilibre = nea;
    racinesousarbre->equilibre = neb;
    racinesousarbre->gauche = temp->droite;
    temp->droite = racinesousarbre;
    racinesousarbre = temp;
}
//OK

template <class T>
void ArbreAVL<T>::rotationDroiteGauche(Noeud*& racinesousarbre)
{
    Noeud *temp = racinesousarbre->droite;
    
	int eb = temp->equilibre;
	int ea = racinesousarbre->equilibre;
	int nea = -(eb<0 ? eb : 0) + 1 + ea;
	int neb = (nea>0 ? nea : 0) + 1 + eb;

    temp->equilibre = neb;
    racinesousarbre->equilibre = nea;
    racinesousarbre->droite = temp->gauche;
    temp->gauche = racinesousarbre;
    racinesousarbre = temp;
}
//OK

// ===================== Lab 6 (2e partie) =====================

template <class T>
bool ArbreAVL<T>::vide() const
{
    // À compléter.
    // Moi
    
    return (racine == NULL);
}
//OK

template <class T>
void ArbreAVL<T>::vider(){
  vider(racine);
}
//OK

template <class T>
void ArbreAVL<T>::vider(Noeud*& noeud)
{
	// Moi

    if(noeud == NULL)
    	return;
    
    vider(noeud -> gauche);
    vider(noeud -> droite);
    
    delete noeud;
    noeud = NULL;
}
//OK

template <class T>
void ArbreAVL<T>::copier(const Noeud* source, Noeud*& noeud) const
{
    // À compléter.
    // Moi
    
    if(source == NULL)
    	return;
    
		noeud = new Noeud(source->contenu);
		noeud->equilibre = source->equilibre;
		    
		copier(source->gauche, noeud->gauche);
		copier(source->droite, noeud->droite);
    
}
//OK

template <class T>
int  ArbreAVL<T>::hauteur() const{
    // À compléter.
    // MOI
    
	Noeud* noeud = racine;
	
	int hauteur = 0;

	while(noeud!=NULL)
    {
    	if(noeud->equilibre > 0)
    	{
    		noeud = noeud->gauche;
    		hauteur++;
    	}
    	else if(noeud->equilibre < 0)
    	{
    		noeud = noeud->droite;
    		hauteur++;
    	}
    	else
    	{
    		noeud = noeud->gauche;
    		hauteur++;
    	}
    }	  	
   
	return hauteur;	

}
//OK



template <class T>
const T& ArbreAVL<T>::max(Noeud* n) const
{
	//Moi
    Iterateur iter(*this);
    
    iter.courant = racine;
    
    if(iter.courant != NULL)
    {
    	while(iter.courant->droite != NULL)
    	{
    		// Pourquoi^^
    		//iter.chemin.empiler(iter.courant);
    		iter.courant = iter.courant->droite;
    	}
    }
    
    return (iter.courant)->contenu;
}
// OK

// L'enlèvement est optionnel (non requise pour le TP2)
template <class T>
void ArbreAVL<T>::enlever(const T& element)
{
    enlever(racine, element);
}

template <class T>
bool ArbreAVL<T>::enlever(Noeud*& noeud, const T& element)
{
    if(element < noeud->contenu)
    {
        if(enlever(noeud->gauche, element))
        {
            // ...
        }
    }
    else if(element > noeud->contenu)
    {
        // ...
    }
    else if(element == noeud->contenu)
    {
        if (noeud->gauche==NULL && noeud->droite==NULL)
        {
            delete noeud;
            noeud = NULL;
            return true;
        }
        else
        {
            // ...
            return true;
        }
    }
    
}
//----------- L'enlèvement est optionnel (non requise pour le TP2) ----------//

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::debut() const
{
    Iterateur iter(*this);
    
    iter.courant = racine;
    
    if(iter.courant != NULL)
    {
    	while(iter.courant->gauche != NULL)
    	{
    		iter.chemin.empiler(iter.courant);
    		iter.courant = iter.courant->gauche;
    	}
    }
    
    return iter;
}
// OK


template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::fin() const
{

    return Iterateur(*this);	// courant == NULL
}
// Pas certain, verifier

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercher(const T& e) const
{
    
    Iterateur iter(*this);  

	Noeud* n = racine;

	while(n)
    {
    	if(e < n->contenu)
    	{
    		iter.chemin.empiler(n);
    		n = n->gauche;
    	}
    	else if(n->contenu < e)
    		n = n->droite;
    	else	// cas d'egalite
    	{
    		iter.courant = n;
    		return iter;
    	}
    }	  	
   
	iter.chemin.vider();
    
    return iter;
}
// OK

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercherEgalOuSuivant(const T& e) const
{
// ATTENTION MOI

	Noeud* n = racine;
	Noeud* suivant = NULL;
	Pile<Noeud*> pile;
	
	while(n)
    {
    	if(e < n->contenu)
    	{
    		pile.empiler(n);	// Besoin d'une pile^
    		n = n->gauche;
    	}
    	else if(n->contenu < e)
    	{
    		n = n->droite;
    	}
    	else	// cas d'egalite
    	{
    		return rechercher(e);	// retourne un iterateur sur l'element
    	}
    }
    
    if(!pile.vide())
    {
    	suivant = pile.depiler();
    	return rechercher(suivant->contenu);
    }		
   
    return Iterateur(*this);	// Si on cherchait l'element le plus petit, il n'y a aucun element precedent et on retourne donc un iterateur vers la fin.
	// Verifier

}
// Verifier

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercherEgalOuPrecedent(const T& e) const
{ 

	Noeud* n = racine, *dernier = NULL;

	while(n)
    {
    	if(e < n->contenu)
    	{
    		n = n->gauche;
    	}
    	else if(n->contenu < e)
    	{
    		dernier = n;
    		n = n->droite;
    	}
    	else	// cas d'egalite
    	{
    		return rechercher(e);	// retourne un iterateur sur l'element
    	}
    }
    
    if(dernier != NULL)
    	return rechercher(dernier->contenu);	// retourne un iterateur sur l'element precedent (l'element exact n'a pas ete trouve)  	
   
    return Iterateur(*this);	// Si on cherchait l'element le plus petit, il n'y a aucun element precedent et on retourne donc un iterateur vers la fin.
}
// OK

template <class T>
const T& ArbreAVL<T>::operator[](const Iterateur& iterateur) const
{
    assert(&iterateur.arbre_associe == this);
    assert(iterateur.courant);
    return iterateur.courant->contenu;
}
// Check

template <class T>
T& ArbreAVL<T>::operator[](const Iterateur& iterateur)
{
    assert(&iterateur.arbre_associe == this);
    assert(iterateur.courant);
    return iterateur.courant->contenu;
}
// Check

template <class T>
ArbreAVL<T>& ArbreAVL<T>::operator=(const ArbreAVL& autre) {
    
    if(this==&autre) return *this;
    
    vider();
    
    copier(autre.racine, racine);
    
    return *this;
}
// Check


//-----------------------
template <class T>
ArbreAVL<T>::Iterateur::Iterateur(const ArbreAVL& a)
 : arbre_associe(a), courant(NULL)
{
}
// Check

template <class T>
ArbreAVL<T>::Iterateur::Iterateur(const ArbreAVL<T>::Iterateur& a)
: arbre_associe(a.arbre_associe)
{
    courant = a.courant;
    chemin = a.chemin;
}
// Check

// Pré-incrément
template <class T>
typename ArbreAVL<T>::Iterateur& ArbreAVL<T>::Iterateur::operator++()
{
    // À compléter.
    
    assert(courant);
    Noeud *suivant = courant->droite;
    
    while(suivant)
    {
    	chemin.empiler(suivant);
    	suivant = suivant -> gauche;  
    }
    if(!chemin.vide())
    	courant = chemin.depiler();
    else
    	courant = NULL; // L'element precedent etait deja le plus grand de l'arbre
    
    return *this;
}
// OK

// Post-incrément
template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::Iterateur::operator++(int)
{
    Iterateur copie(*this);
    operator++();
    return copie;
}
// Check

template <class T>
ArbreAVL<T>::Iterateur::operator bool() const
{
    return courant!=NULL;
}
// Check

template <class T>
bool ArbreAVL<T>::Iterateur::operator!() const{
    return courant==NULL;
}
// Check

template <class T>
bool ArbreAVL<T>::Iterateur::operator==(const Iterateur& o) const{
    assert(&arbre_associe==&o.arbre_associe);
    return courant==o.courant;
}
// Check

template <class T>
bool ArbreAVL<T>::Iterateur::operator!=(const Iterateur& o) const{
    assert(&arbre_associe==&o.arbre_associe);
    return courant!=o.courant;
}
// Check

template <class T>
const T& ArbreAVL<T>::Iterateur::operator *() const
{
    assert(courant!=NULL);
    return courant->contenu;
}
// Check

template <class T>
typename ArbreAVL<T>::Iterateur& ArbreAVL<T>::Iterateur::operator = (const Iterateur& autre){
    assert(&arbre_associe==&autre.arbre_associe);
    courant = autre.courant;
    chemin = autre.chemin;
    return *this;
}
// Check


// ===================================================================

template <class T>
void ArbreAVL<T>::afficher() const{
    
    Iterateur iter = debut();
    
    for(;iter;iter++)
    {
    	std::cout << *iter << std::endl;
    }
}
// Check

#endif
