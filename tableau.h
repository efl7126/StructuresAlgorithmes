/* UQAM / Département d'informatique
   INF3105 - Structures de données et algorithmes
   Squelette pour classe générique Tableau<T> pour le TP1 et Lab3.

   AUTEUR(S):
    1) Jules Ndjerandouba + NDJJ15047609
    2) Francois-Guillaume Landry + LANF06109305
*/

#if !defined(_TABLEAU___H_)
#define _TABLEAU___H_

#include <assert.h>

// =======================================================================
// =================== Déclarations de la classe Tableau =================
// =======================================================================


template <class T>
class Tableau{

  public:
    Tableau(int capacite_initiale = 10);
    Tableau(const Tableau&);
    ~Tableau();

    // Ajouter un element à la fin
    void           ajouter(const T& element);
    // Vider le tableau
    void           vider();
    // Retourne le nombre d'éléments dans le tableau
    int            taille() const;

    // Insère element à position index. Les éléments à partir de index 
    // sont décalés d'une position.
    void           inserer(const T& element, int index=0);

    // Enlève l'element à position index. Les éléments après index sont 
    // décalés d'une position après.
    void           enlever(int index=0);

    // Cherche et retourne la position de l'élément. Si non trouvé, retourne -1.
    int            chercher(const T& element);

	// Opérateurs de sélection
    const T&       operator[] (int index) const;
    T&             operator[] (int index);

	// Opérateur d'égalité
    bool           operator == (const Tableau<T>& autre) const;
    // Opérateur d'affectation
    Tableau<T>&    operator = (const Tableau<T>& autre);
    
    // Affiche le contenu du tableau
	void 		   afficher() const;


  // Fonctions privées ===================================================
  private:
    
    // Redimensionnement du tableau lorsque la capacité est atteinte
 	void 		   redimensionner(int nouvelleCapacite);
 	

  // Attributs ===========================================================
  private:
    T*             elements;
    int            nbElements;
    int            capacite;
};


// =======================================================================
// ==================== Définitions ======================================
// =======================================================================


// =================== Constructeurs et destructeurs =====================


// Constructeur avec la capacité initiale comme argument
template <class T>
Tableau<T>::Tableau(int capacite_initiale)
{
    elements = new T[capacite_initiale]; 
    capacite = capacite_initiale;
    nbElements = 0;
}


// Constructeur par copie
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


// Destructeur
template <class T>
Tableau<T>::~Tableau()
{
    delete[] elements;
    elements = NULL;
}


// =================== Autres méthodes à définir =====================


// Retourne la taille du tableau
template <class T>
int Tableau<T>::taille() const
{   
   return (nbElements);
}


// Ajout d'un élément à la fin du tableau
template <class T>
inline void Tableau<T>::ajouter(const T& item)
{
    if(nbElements >= capacite)
    {
    	redimensionner(capacite * 2);
    }
	
    elements[nbElements] = item;
    nbElements++;	
	
}

// Insertion d'un élément à un indice du tableau
template <class T>
void Tableau<T>::inserer(const T& element, int index)
{
	// S'assure que l'index choisi fait partie du tableau
	assert((index < capacite) && (index >= 0));	

	// S'assure qu'il reste au moins une case vide dans le tableau
    if(!(nbElements < capacite))	
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


// Enlèvement d'un élément situé à un indice du tableau
template <class T>
void Tableau<T>::enlever(int index)
{
	// S'assure que l'index choisi fait partie du tableau
    assert((index < capacite) && (index >= 0));	
	
	if(index < nbElements)
	{
		for(int i = index; i < (nbElements-1); i++)
		{
			elements[i] = elements[i+1];
		}	
			
		nbElements--;
	}				
}


// Recherche linéaire d'un élément dans le tableau. Retourne l'indice
// de l'élément si l'élément en question est trouvé.
template <class T>
int Tableau<T>::chercher(const T& element)
{
    
    for(int i = 0; i < nbElements; i++)
    {
    	if(elements[i] == element)
    		return i;
    }
    
  	return -1;
}


// Vide le tableau en éliminant tous les éléments
template <class T>
void Tableau<T>::vider()
{
	if(elements != NULL)
    	delete[] elements; 
    elements = new T[capacite];
    
    nbElements = 0;
}


// Opérateur de sélection permettant seulement l'accès
template <class T>
const T& Tableau<T>::operator[] (int index) const
{
	// La vérification que l'indice est situé à l'intérieur de l'espace 
	// d'adressage du tableau est enlevée par souci d'efficacité
	
    // assert(index < nbElements);
    return elements[index];
}


// Opérateur de sélection permettant la mofification
template <class T>
T& Tableau<T>::operator[] (int index)
{
    //assert(index < nbElements);
    
    return elements[index];
}


// Opérateur d'affectation
template <class T>
Tableau<T>& Tableau<T>::operator = (const Tableau<T>& autre)
{

	// Si l'argument est le même objet que l'objet courant
	if(this==&autre) return *this;	 
	
	nbElements = autre.nbElements;
	
	// La capacité de l'objet courant est modifiée si elle est inférieure
	// à celle de l'objet copié, ou si elle est largement supérieure
	// (plus que 2x plus grande).
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


// Opérateur d'égalité
template <class T>
bool Tableau<T>::operator == (const Tableau<T>& autre) const
{
	// Si l'argument est le même objet que l'objet courant
    if(this==&autre) return true;
	
	if(nbElements != autre.nbElements) return false;
	
	for(int i=0; i<nbElements;i++)
	{
		if(!(elements[i]==autre.elements[i]))
			return false;
	}

    return true;
}


// Affichage des éléments du tableau pour fins de déboggage
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


// Méthode de redimensionnement du tableau
template <class T>
void Tableau<T>::redimensionner(int nouvelleCapacite) 
{
    T* elementsTemp = new T[nouvelleCapacite];	
		
	// Transfert des éléments
	for(int i = 0; i < nbElements; i++)
	{
		elementsTemp[i] = elements[i];
	}
		
	//Delete de l'ancien tableau et transfert du pointeur
	delete[] elements;
	elements = elementsTemp;
						
	// Changement de l'attribut capacite
	capacite = nouvelleCapacite;
	
}


#endif //define _TABLEAU___H_
