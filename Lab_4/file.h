/*
  INF3105 - Structures de données et algorithmes
  UQAM / Département d'informatique
*/

#if  !defined(__FILE_H__)
 #define  __FILE_H__

template <class T> class File
{
  public:
    File();
    ~File();
    File(const File<T>& autre);

    void  enfiler(const T&);
    T     defiler();
    void  defiler(T&);
    bool  vide() const {return queue==NULL;}
    void vider();
    File<T>& operator=(const File<T>& autre);

  private:

    class Cellule
    {
      public:
        Cellule(const T& e, Cellule* c=NULL);
        T          element;
        Cellule*   suivante;
    };

    Cellule *queue;
};

/*
 Puisque File<T> est une classe générique, toutes ses définitions doivent être
 inclues après les déclarations. On peut quand même séparer les déclarations et
 les définitions en deux fichiers (file.h et file.hcc), à condition d'inclure le
 deuxième (file.hcc) à la fin du premier (file.h). Ainsi, un fichier source
 (.cc, .cpp, c++) qui inclut file.h inclura indirectement aussi file.hcc.

*/

//#include "file.hcc"
/**** Début des définitions pouvant être mises dans file.hcc. ****/

// Les deux directives suivante sont utiles lorsqu'un fichier file.hcc est utilisé.
#if !defined(__FILE_HCC__)
#define __FILE_HCC__

#include <assert.h>

template <class T>
File<T>::File()
{
    queue = NULL;
}

template <class T>
File<T>::~File()
{
    // À compléter.
	while(!vide())
		defiler();

}

// Constructeur par copie
template <class T>
File<T>::File(const File<T>& autre)
{

	Cellule** t = &queue;
	Cellule* i = (autre.queue)->suivante;
	
	do
	{
		*t = new Cellule(i -> element, queue);
		t = &((*t)->suivante);
		i = i -> suivante;
	} while(i != (autre.queue)->suivante);
	
	// Mettre la queue a la fin
	Cellule* debut = queue;
	while(queue->suivante != debut)
		queue = queue->suivante;
	
}

template <class T>
void File<T>::vider()
{
	while(!vide())
		defiler();
		
	queue = NULL;
}

template <class T>
File<T>::Cellule::Cellule(const T& e, Cellule* c)
: element(e), suivante(c)
{
}

template <class T>
void File<T>::enfiler(const T& e)
{
    // À compléter.
    if(queue == NULL) // Cas 1 : File vide
    {
    	queue = new Cellule(e);
    	queue->suivante = queue;
    }
    else	// Cas 2 : Tout autre cas
    	queue = queue->suivante = new Cellule(e, queue->suivante);   	
    	
}

template <class T>
T File<T>::defiler()
{
	// À compléter.
    Cellule* c = queue -> suivante;
    
    if(queue == c) // Cas d'une seule cellule
    	queue = NULL;
    else
    	queue->suivante = c->suivante;
    
    
    T result = c->element;   
    delete c;

    return result;
}

template <class T>
void File<T>::defiler(T& r)
{
    // À compléter.
    Cellule* c = queue -> suivante;
    
    if(queue == c) // Cas d'une seule cellule
    	queue = NULL;
    else
    	queue->suivante = c->suivante;
    delete c;
}


template <class T>
File<T>& File<T>::operator=(const File<T>& autre)
{

	vider();

	Cellule** t = &queue;
	Cellule* i = (autre.queue)->suivante;
	
	do
	{
		//std::cout << "Ajout element : " << i -> element << std::endl;;
		*t = new Cellule(i -> element, queue);
		t = &((*t)->suivante);
		i = i -> suivante;
		//std::cout << "i pointe vers l'element : " << i -> element << std::endl;;
		
	} while(i != (autre.queue)->suivante);
	
	// Cas 1 seul ajout
	if(queue->suivante == NULL)
		queue->suivante = queue;
	
	//std::cout << "Fin boucle 1" << std::endl;
	
	// Mettre la queue a la fin =================================================
	//std::cout << "Adresse Queue Suiv" << queue->suivante << std::endl;
	Cellule* debut = queue;
	//std::cout << "Adresse Debut" << debut << std::endl;
	while(queue->suivante != debut) 
		queue = queue->suivante;
	
	
	//std::cout << "Fin boucle 2" << std::endl;
	File<T> &refFile = *this;

    return refFile;
}


// Ce #endif est utile si mis dans file.hcc
#endif
/**** Fin des définitions pouvant être mises dans file.hcc. ****/



#endif

