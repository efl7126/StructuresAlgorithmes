/*
  INF3105 - Structures de données et algorithmes
  UQAM / Département d'informatique

  Liste simplement chaînée.

  À compléter.
*/



#if !defined(__LISTE_H__)
#define __LISTE_H__

#include <assert.h>

// Déclaration

template <class T>
class Liste
{
  public:
    class Iterateur;

    Liste();
    ~Liste();

    bool estVide() const;
    void vider();

    bool operator == (const Liste&) const;

    const Liste& operator = (const Liste&);

    T& operator[] (const Iterateur&);
    const T& operator[] (const Iterateur&) const;

    // Les fonctions insérer retournent un Itérateur sur la position de l'objet inséré.
    // La fonction enlever retourne un Iterateur sur la position suivante de l'objet enlevé.
    Iterateur inserer(const T&, const Iterateur&);
    Iterateur enlever(const Iterateur&);

    Iterateur inserer_debut(const T&);
    Iterateur inserer_fin(const T&);
    void      enlever_debut();

    Iterateur debut() const; // Iterateur sur le début.
    Iterateur fin() const;   // Iterateur sur la fin. La fin est la position suivante du dernier élément.

    Iterateur trouver(const T&) const; // Retourne un itérateur sur le premier élément cherchée. S'il n'existe pas, retourne fin().

  private:
    class Cellule{
      public:
      Cellule(const T& c, Cellule* s=NULL) : suivante(s) { contenu=c; }
      T contenu;
      Cellule* suivante;
    };

  public:
    class Iterateur{
      public:
        Iterateur(const Iterateur&);
        Iterateur(const Liste&);

        operator bool() const; // retourne vrai si l'itérateur n'est pas rendu à la fin. Permet de faire while(iter)
        bool operator!() const; // retourne faux si l'itérateur n'est pas rendu à la fin
        bool operator==(const Iterateur&) const; // compare deux itérateur (deux "positions")
        bool operator!=(const Iterateur&) const; // !compare deux itérateur (deux "positions")

        Iterateur operator++(int);  // post-incrément (passe au suivant)
        Iterateur& operator++(); // pré-incrément (passe au suivant)

        //T& operator*(); // Pourquoi est-ce une mauvaise idée? Qu'arrive-t-il si la liste est constante?
        const T& operator*() const; // déférencement

        Iterateur& operator = (const Iterateur&); // affecte l'itérateur à la valeur d'un autre

     private:
        Cellule* precedente; // pointeur sur la Cellule précédente de la position courante
        const Liste& liste;  // référence sur la Liste associée à l'itérateur courant (pour des fins de robustesse).
     friend class Liste;
    };

  private:
    Liste(const Liste&);

    Cellule* derniere;
};


/*
 Puisque Liste<T> est une classe générique, toutes ses définitions doivent être
 inclues après les déclarations. On peut quand même séparer les déclarations et
 les définitions en deux fichiers (liste.h et liste.hcc), à condition d'inclure le
 deuxième (liste.hcc) à la fin du premier (liste.h). Ainsi, un fichier source
 (.cc, .cpp, c++) qui inclut liste.h inclura indirectement aussi liste.hcc.
*/
//#include "liste.hcc"

// Implémentation des constructeurs, destructeurs et fonctions
template <class T>
Liste<T>::Liste(){
    derniere = NULL;
}

template <class T>
Liste<T>::~Liste(){

    vider();
}

template <class T>
bool Liste<T>::estVide() const
{
    return derniere == NULL;
}

template <class T>
void Liste<T>::vider()
{
    // À compléter.
    // Requis pour la tâche 3.

	Cellule* c = derniere;
	
	while(c != NULL)
	{
		Cellule *t = c->suivante;
		delete c;
		c = t;
		if(c==derniere)
			c = NULL;
	}
	derniere = NULL;
	
	// ======= Autre version ========
	/*
	while(!estVide())
	{
		enleverdebut();
	}
	*/
	

}

template <class T>
const Liste<T>& Liste<T>::operator = (const Liste<T>& autre)
{
    // À compléter.
    
    
    if(this == &autre) return *this;
    vider();
    for(Iterateur ia=autre.debut();ia;++ia)
    	inserer_fin(*ia);   
    
    return *this;
}

template <class T>
T& Liste<T>::operator [](const Iterateur& i)
{
    assert(&i.liste == this);
    assert(i.precedente != NULL);
    return i.precedente->suivante->contenu;
}

template <class T>
const T& Liste<T>::operator [](const Iterateur& i) const
{
    assert(&i.liste == this);
    assert(i.precedente != NULL);
    return i.precedente->suivante->contenu;
}

template <class T>
typename Liste<T>::Iterateur Liste<T>::inserer(const T& e, const Iterateur& i)
{
    // À compléter.
    
    assert(this == &i.liste); // Verifie qu'on ajoute dans la bonne liste
    
    Iterateur position(i);
    
    Cellule* c = i.precedente;
    
    if(derniere==NULL){		// Liste vide
    
    	derniere = new Cellule(e);
    	derniere -> suivante = derniere;
    }
    else if(c == NULL)		// Ajouter a la fin
    {
    	c = derniere;
    	derniere -> suivante = new Cellule(e, derniere->suivante);
    	derniere = derniere -> suivante;
    }
    else
    	c->suivante = new Cellule(e, c->suivante);
    	
    position.precedente = c;
    return position;
    
    
    // On pourrait remplacer c partout position.precedente
;
}

template <class T>
typename Liste<T>::Iterateur Liste<T>::inserer_debut(const T& e)
{
    // À compléter.
    
    Iterateur position(*this);
    if(derniere==NULL){		// Liste vide
    
    	derniere = new Cellule(e);
    	position.precedente = derniere -> suivante = derniere;
    }
    else
    {
    	position.precedente->suivante = new Cellule(e, position.precedente->suivante);
    }
    
    return position;
}

template <class T>
typename Liste<T>::Iterateur Liste<T>::inserer_fin(const T& e){
    // À compléter.
    // Requis pour la tâche 3.
    
    Iterateur position(*this);
    if(derniere==NULL){		// Liste vide
    
    	derniere = new Cellule(e);
    	position.precedente = derniere -> suivante = derniere;
    }
    else
    {
    	position.precedente = derniere;
    	derniere -> suivante = new Cellule(e, derniere->suivante);
    	derniere = derniere -> suivante;
    }
    
    return position;

}


template <class T>
typename Liste<T>::Iterateur Liste<T>::enlever(const Iterateur& i)
{
    // À compléter.
    assert(this == &i.liste); // Verifie qu'on ajoute dans la bonne liste
    
    Iterateur position(i);
    
    Cellule* c = i.precedente;
    
    // c == NULL c'est un iterateur qui pointe a rien, donc fin de la liste
    assert(c != NULL && derniere != NULL);
    Cellule *temp = c->suivante;
    c->suivante = temp->suivante;
    delete temp;
    Cellule *retour = temp==derniere ? NULL : c;
    if(derniere == temp)
    	derniere = c;
    if(temp == c)
    	derniere = c = NULL;
    position.precedente = retour;
    return position;
    
}

template <class T>
void Liste<T>::enlever_debut(){
    // À compléter.
    // Requis pour la tâche 3.
    enlever(debut()); // Pas sur
}

template <class T>
typename Liste<T>::Iterateur Liste<T>::debut() const {
    return Iterateur(*this);
}

template <class T>
typename Liste<T>::Iterateur Liste<T>::fin() const {
    Iterateur iter(*this);
    iter.precedente = NULL;
    return iter;
}

template <class T>
typename Liste<T>::Iterateur Liste<T>::trouver(const T& e) const {
    // À compléter.
    // Probablement non requis pour la tâche #3.
    
    Iterateur iter(*this);
    while(iter && !(*iter == e))
    	iter++;
    return iter;
    
}

template <class T>
bool Liste<T>::operator == (const Liste& autre) const{
    if(this == &autre) return true;
    // À compléter.
    
	Iterateur iter_listeActuelle(*this);
	Iterateur iter_autre = autre.debut();
	
	// Cas de deux listes avec aucun element
	if(iter_listeActuelle.precedente == NULL && iter_autre.precedente == NULL)
		return true;
	
	while(iter_autre && iter_listeActuelle)
    {
    
    	if(*iter_autre != *iter_listeActuelle)
    		return false;
    		
    	++iter_listeActuelle;
    	++iter_autre;
    }
    
    if(iter_autre.precedente != NULL || iter_listeActuelle.precedente != NULL)
    	return false;
	

	return true;
}



//----------------------------------------------------//
template <class T>
Liste<T>::Iterateur::Iterateur(const Iterateur& i)
 : liste(i.liste)
{
    precedente = i.precedente;
}

template <class T>
Liste<T>::Iterateur::Iterateur(const Liste<T>& l)
 : liste(l)
{
    precedente = l.derniere;	// Iterateur pointe vers le premier
}

template <class T>
bool Liste<T>::Iterateur::operator !() const
{
    return precedente == NULL;
}

template <class T>
Liste<T>::Iterateur::operator bool() const
{
    return precedente != NULL;
}


template <class T>
bool Liste<T>::Iterateur::operator == (const Iterateur& autre) const
{
    return precedente == autre.precedente
           &&  &liste == &autre.liste;
}

template <class T>
bool Liste<T>::Iterateur::operator != (const Iterateur& autre) const
{
    return precedente != autre.precedente
           || &liste != &autre.liste;
}

// operator ++ () est le pré-incrément
template <class T>
typename Liste<T>::Iterateur& Liste<T>::Iterateur::operator ++ ()
{
    precedente = precedente->suivante;
    if(precedente==liste.derniere) precedente = NULL;
    return *this;
}

// operator ++ (int) est le post-incrément
template <class T>
typename Liste<T>::Iterateur Liste<T>::Iterateur::operator ++ (int)
{
    Iterateur temp(*this);
    precedente = precedente->suivante;
    if(precedente==liste.derniere) precedente = NULL;
    return temp;
}

template <class T>
const T& Liste<T>::Iterateur::operator *() const
{
    return liste[*this];
}

template <class T>
typename Liste<T>::Iterateur& Liste<T>::Iterateur::operator = (const Iterateur& autre)
{
    assert(&liste == &autre.liste);
    precedente = autre.precedente;
    return *this;
}

#endif

