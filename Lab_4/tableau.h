/* UQAM / Département d'informatique
   INF3105 - Structures de données et algorithmes
   Squelette pour classe générique Tableau<T> pour le TP1 et Lab3.

   AUTEUR(S):
    1) Nom + Code permanent du l'étudiant.e 1
    2) Nom + Code permanent du l'étudiant.e 2
*/

#if !defined(_TABLEAU___H_)
#define _TABLEAU___H_

#include <assert.h>
#include <iostream>

using namespace std;

template <class T>
class Tableau{

  public:
    Tableau(int capacite_initiale=30);
    Tableau(const Tableau&);
    ~Tableau();

    // Ajouter un element à la fin
    void           ajouter(const T& element);
    // Vider le tableau
    void           vider();
    // Retourne le nombre d'éléments dans le tableau
    int            taille() const;

    // Insère element à position index. Les éléments à partir de index sont décalés d'une position.
    void           inserer(const T& element, int index=0);

    // Enlève l'element à position index. Les éléments après index sont décalés d'une position après.
    void           enlever(int index=0);

    // Cherche et retourne la position de l'élément. Si non trouvé, retourne -1.
    int            chercher(const T& element);

    const T&       operator[] (int index) const;
    T&             operator[] (int index);

    bool           operator == (const Tableau<T>& autre) const;
    Tableau<T>&    operator = (const Tableau<T>& autre);


  // Fonction privée ajoutée
  public:
    
 	void 		   redimensionner(int nouvelleCapacite);
 	void 		   afficher() const;

  private:
    T*             elements;
    int            nbElements;
    int            capacite;
};

// ====================================================================================
// ======================== Définitions ===============================================
// ====================================================================================

// ======================== Constructeurs et destructeurs =============================

template <class T>
Tableau<T>::Tableau(int capacite_initiale)
{
    elements = new T[capacite_initiale]; 
    capacite = capacite_initiale;
    nbElements = 0;
}
// Verified


template <class T>
Tableau<T>::Tableau(const Tableau& autre)
{
    // Copie des attributs
	capacite = autre.capacite;
	nbElements = autre.nbElements;
	
	// Création du nouveau tableau
	elements = new T[capacite];
	for(int i = 0; i < nbElements; i++)
	{
		elements[i] = autre.elements[i];
	}
}
// Verified


template <class T>
Tableau<T>::~Tableau()
{
    delete[] elements;
    elements = NULL;
}
// Verified


// ======================== Fonctions à définir =======================================

template <class T>
int Tableau<T>::taille() const
{   
   return (nbElements);
}
// OK


template <class T>
inline void Tableau<T>::ajouter(const T& item)
{
    // À compléter
    if(nbElements >= capacite)
    {
    	redimensionner(capacite * 2);
    }
	
    elements[nbElements] = item;
    nbElements++;	
	
}
// Verified



template <class T>
void Tableau<T>::inserer(const T& element, int index)
{

	assert((index < capacite) && (index >= 0));	// L'index choisi fait partie du tableau

    if(!(nbElements < capacite))	// S'assure qu'il reste au moins une place dans le tableau
    {
    	redimensionner(capacite*2);
    }
    
	for(int i = nbElements; i > index; i--)
	{
		elements[i] = elements[i - 1];
	}
		
	elements[index] = element;
		
	nbElements++;
}
// OK


template <class T>
void Tableau<T>::enlever(int index)
{
    assert((index < capacite) && (index >= 0));	// L'index choisi fait partie du tableau
	
	if(index < nbElements)
	{
		for(int i = index; i < (nbElements-1); i++)
		{
			elements[i] = elements[i+1];
		}	
			
		nbElements--;
	}				
}
// OK

template <class T>
int Tableau<T>::chercher(const T& element)
{
    // À compléter
    // Voir la fonction Tableau<T>::contient() dans les notes de cours à la page 47.
    // Il suffit de l'adapter pour retourner la position au lieu d'un booléen.
    
    for(int i = 0; i < nbElements; i++)
    {
    	if(elements[i] == element)
    		return i;
    }
    
  	return -1;
}
// OK


template <class T>
void Tableau<T>::vider()
{
    delete[] elements; 
    elements = new T[capacite];
    
    nbElements = 0;
}
// OK


template <class T>
inline const T& Tableau<T>::operator[] (int index) const
{
    //assert(index < nbElements);
    return elements[index];
}
// Verified

template <class T>
inline T& Tableau<T>::operator[] (int index)
{
    //assert(index < nbElements);
    return elements[index];
}
// Verified


template <class T>
Tableau<T>& Tableau<T>::operator = (const Tableau<T>& autre)
{

	if(this==&autre) return *this;
	
	nbElements = autre.nbElements;
	
	if(capacite < autre.nbElements || autre.nbElements*2 < capacite)
	{
		delete[] elements;
	 	capacite = autre.capacite;
	 	elements = new T[capacite];
	}
	
	for(int i = 0; i < nbElements; i++)
		elements[i] = autre.elements[i];

    return *this;
}
// Verified



template <class T>
bool Tableau<T>::operator == (const Tableau<T>& autre) const
{
    if(this==&autre) return true;
	
	if(nbElements != autre.nbElements) return false;
	
	for(int i=0; i<nbElements;i++)
	{
		if(!(elements[i]==autre.elements[i]))
			return false;
	}

    return true;
}
// OK


// ======================== Fonctions additionnelles ==================================


template <class T>
void Tableau<T>::afficher() const
{
	if(nbElements == 0)
		std::cout << "Le tableau est vide" << std::endl;
    for(int i = 0; i < nbElements; i++)
    {
    	std::cout << elements[i] << " ";
    }
    std::cout << std::endl;
}
// Verified


template <class T>
void Tableau<T>::redimensionner(int nouvelleCapacite) 
{
    T* elementsTemp = new T[nouvelleCapacite];	// Double la capacite
		
	// Transfert des elements
	for(int i = 0; i < nbElements; i++)
	{
		elementsTemp[i] = elements[i];
	}
		
	//Delete de l'ancien tableau et transfert du pointeur
	delete[] elements;
	elements = elementsTemp;
						
	// Changement des attributs
	capacite = nouvelleCapacite;
	
}
// Verified



#endif //define _TABLEAU___H_
