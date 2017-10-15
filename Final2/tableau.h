/* UQAM / Département d'informatique
   INF3105 - Structures de données et algorithmes
   Squelette pour classe générique Tableau<T> pour le TP1 et Lab3.

   AUTEUR(S):
    1) Jules Ndjerandouba + NDJJ15047609
    2) Francois-Guillaume Landry + Code permanent du l'étudiant.e 2
*/

#if !defined(_TABLEAU___H_)
#define _TABLEAU___H_

#include <assert.h>

// =======================================================================
// =================== Déclaration de la classe Tableau ==================
// =======================================================================


template <class T>
class Tableau{

  public:
    Tableau(int capacite_initiale = 30);
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

	// Opérateurs de sélection
    const T&       operator[] (int index) const;
    T&             operator[] (int index);

	// Opérateur d'égalité
    bool           operator == (const Tableau<T>& autre) const;
    // Opérateur d'affectation
    Tableau<T>&    operator = (const Tableau<T>& autre);
    
    // Affiche le contenu du tableau
	void 		   afficher() const;
	
	// Permet de trier un tableau de pointeurs en fonction d'un attribut des objets pointés.
	// L'objectif pour le TP1 est de trier les stations en fonction du temps de marche
	// point d'origine -> station sans avoir à déplacer les objets Station mêmes.
	void 		   trierTableauPointeurs();


  // Fonctions privées ===================================================
  private:
    
    // Redimensionnement du tableau lorsque la capacité est atteinte
 	void 		   redimensionner(int nouvelleCapacite);
 	
 	// Implémentation du tri rapide pour trier un tableau de pointeurs en fonction
	// de l'attribut tempsMarche1 des objets Station pointés.
	void           triRapidePointeursTempsMarche1(T *tab, int n);
	
	// Fonction d'échange
	void           swap(T& element1, T& element2);


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
    delete[] elements; 
    elements = new T[capacite];
    
    nbElements = 0;
}


// Opérateur de sélection permettant seulement l'accès
template <class T>
inline const T& Tableau<T>::operator[] (int index) const
{
	// La vérification que l'indice est situé à l'intérieur
	// de l'espace d'adressage du tableau est enlevée par souci d'efficacité
    //assert(index < nbElements);
    return elements[index];
}


// Opérateur de sélection permettant la mofification
template <class T>
inline T& Tableau<T>::operator[] (int index)
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


// =================== Méthodes spécifiques au TP1 ======================


// Permet de trier un tableau de pointeurs en fonction d'un attribut des objets pointés.
// L'objectif pour le TP1 est de trier les stations en fonction du temps de marche
// point d'origine -> station sans avoir à déplacer les objets Station mêmes.
template <class T>
void Tableau<T>::trierTableauPointeurs()
{	
	triRapidePointeursTempsMarche1(elements, nbElements);
}

// Implémentation du tri rapide pour trier un tableau de pointeurs en fonction
// de l'attribut tempsMarche1 des objets Station pointés.
// L'implémentation du tri rapide est tirée de la diapositive 27 de la présentation
// INF3105 - Analyse et complexité algorithmique.
template <class T>
void Tableau<T>::triRapidePointeursTempsMarche1(T *tab, int n)
{
	// Seulement un tri partiel est effectué puisque cela semble épargner du temps
	// d'exécution pour les cas testés
	if(n<=16) return;
	
	// Le pivot choisi est la valeur médiane
	int p = (n-1)/2;
	
	// Placement du pivot 
	swap(tab[0],tab[p]);
	
	
	int k = 0;

	// Algorithme permettant de séparer les petits et les grands 
	for(int i = 1; i < n; i++)
		// Comparaison des temps de marche du point d'origine jusqu'à la première station
		if((tab[i]->tempsMarche1) < (tab[0]->tempsMarche1))		
			swap(tab[++k],tab[i]);
	
	swap(tab[0],tab[k]);
	
	triRapidePointeursTempsMarche1(tab,k);
	triRapidePointeursTempsMarche1(tab+k+1,n-k-1);

}

// Fonction d'échange des éléments
template <class T>
void Tableau<T>::swap(T& element1, T& element2)
{
	T temp = element2;
	element2 = element1;
	element1 = temp;
}


#endif //define _TABLEAU___H_
