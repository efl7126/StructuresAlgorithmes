/*
  INF3105 - Structures de données et algorithmes
  UQAM / Département d'informatique
*/

#if !defined(__PILE_H__)
 #define __PILE_H__

#include <iostream>


using namespace std;

class Cellule;

template <class T>
class Pile
{
  public:
    Pile();
    ~Pile();
    
    Pile(const Pile<T>& autre);

    void empiler(const T&);
  
    void depiler(T& out);  // Depiler et copier le sommet dans out.
    T depiler();

    bool vide() const { return sommet==NULL;}
    void vider();
    Pile<T>& operator=(const Pile<T>& autre);
    void printPile() const;
    

  private:
    
    class Cellule
    {
      public:
        Cellule(const T& e, Cellule* c);
        T contenu;
        Cellule* suivante;
    };

    Cellule* sommet;

	//friend ostream& operator << (ostream& os, const Pile<T>& pile);
};

/*
 Puisque Pile<T> est une classe générique, toutes ses définitions doivent être
 inclues après les déclarations. On peut quand même séparer les déclarations et
 les définitions en deux fichiers (pile.h et pile.hcc), à condition d'inclure le
 deuxième (pile.hcc) à la fin du premier (pile.h). Ainsi, un fichier source
 (.cc, .cpp, c++) qui inclut pile.h inclura indirectement aussi pile.hcc.

*/

//#include "pile.hcc"
/**** Début des définitions pouvant être mises dans pile.hcc. ****/

// Les deux directives suivante sont utiles lorsqu'un fichier pile.hcc est utilisé.
#if !defined(__PILE_CPP__)
#define __PILE_CPP__

#include "assert.h"
#include "pile.h"

template <class T>
Pile<T>::Pile()
{
    sommet = NULL;
}

template <class T>
Pile<T>::Pile(const Pile<T>& autre)
{
	// CODE TEST AU LAB
	/*
	while(((autre.sommet)->suivante) != 0)
	{
		autre.sommet = (autre.sommet)->suivante;
	}
	*/
	
	
	
	Cellule** t = &sommet;
	Cellule* i = autre.sommet;
	
	while(i)
	{
		*t = new Cellule(i -> contenu, NULL);
		t = &((*t)->suivante);
		i = i -> suivante;
	}
	
}

template <class T>
Pile<T>::~Pile()
{
    vider();
}

template <class T>
void Pile<T>::vider()
{
    while(!vide())
        depiler();  
}

template <class T>
Pile<T>::Cellule::Cellule(const T& e, Cellule* c)
 : suivante(c)
{
    contenu=e;
}

template <class T>
void Pile<T>::empiler(const T& e)
{
	//std::cout << "Sommet" << sommet->contenu;
    sommet = new Cellule(e, sommet);
    
    assert(sommet);
}

template <class T>
T Pile<T>::depiler()
{
    //std::cout << "Instr 1" << std::endl;
    assert(sommet);
    //std::cout << "Instr 2" << std::endl;
    Cellule c(*sommet);
    //std::cout << "Instr 3" << std::endl;
    delete sommet;
    sommet = c.suivante;
	//std::cout << c.contenu << std::endl;
    return c.contenu;
}

template <class T>
void Pile<T>::depiler(T& e)
{
    assert(sommet!=NULL);
    e = sommet->contenu;
    Cellule* c = sommet;
    sommet = sommet->suivante;
    delete c;
}


template <class T>
Pile<T>& Pile<T>::operator=(const Pile<T>& autre)
{

	if(this==&autre) return *this; // cas special lorsqu'on affecte un objet a lui-meme

	vider(); //Ajout

	Cellule** t = &sommet;
	Cellule* i = autre.sommet;
	
	while(i)
	{
		*t = new Cellule(i -> contenu, NULL);
		t = &((*t)->suivante);
		i = i -> suivante;
	}
	
	Pile<T> &refPile = *this;

    return refPile;
}


// Autre version de l'operateur egal (notes de cours)

/*
Pile& Pile::operator = (const Pile& autre){
    if(this==&autre) return *this; // cas special lorsqu'on affecte un objet a lui-meme

    vider(); // ou: while(sommet!=NULL){Cellule*t=sommet->suivante; delete sommet; sommet=t;}
    if(autre.sommet !=NULL){
        sommet = new Cellule(autre.sommet->element);
        Cellule *cp = autre.sommet;
        Cellule *c = sommet;
        while(cp->suivante != NULL){
            c->suivante = new Cellule(cp->suivante->element);
            c = c->suivante;
            cp = cp->suivante;
        }
    }
    return p;
}
*/

// Tache 9 ====================================================


/*
Pile& Pile::operator = (const Pile& autre){
    if(this==&autre) return *this; // cas special lorsqu'on affecte un objet a lui-meme

    
    if(autre.sommet !=NULL){
    
        Cellule *cp = autre.sommet;
        Cellule *c = sommet;
        while(cp != NULL){
        
        	if((c->suivante != NULL) && (cp->suivante != NULL))
        	{
        		c->suivante->contenu = cp->suivante->contenu; 	// Copie de l'element
        		c = c->suivante;
            	cp = cp->suivante;
        	}
        	else if(c->suivante == NULL)
        	{
        		c->suivante = new Cellule(cp->suivante->element, NULL);
        		c = c->suivante;
            	cp = cp->suivante;
        	}
            
        }
    }
    else
    	vider();
    
    
    
    Pile<T> &refPile = *this;
    return refPile;
}
*/

template <class T>
void Pile<T>::printPile() const
{
	
	if(sommet == NULL)
		cout << "La pile est vide" << endl;
	else
	{
		
		Cellule* iter = sommet;
	
		while(iter)
		{
			cout << iter->contenu;
			iter=iter->suivante;
		}
	
		cout << endl;
	}

}

template <class T>
ostream& operator << (ostream& os, const Pile<T>& pile)
{
    pile.printPile();
    
    return os;
}

#endif
// Les deux directives suivante sont utiles lorsqu'un fichier pile.hcc est utilisé.


#endif


