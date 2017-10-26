// ============================================================
// ============ TABLEAUX DYNAMIQUES ET GENERIQUES =============
// ============================================================

// Representation - Tableau dynamique

template <class T>
class Tableau
{
	// Autre
	
	private:
		T* elements;
		int capacite;
		int nbElements;
		void redimensionner(int nouvCapacite);
};

// Operator =

template <class T>
Tableau<T>& Tableau<T>::operator=(const Tableau<T>& autre)
{
	if(this==&autre) return *this;
	nbElements = autre.nbElements;
	
	if(capacite<autre.nbElements){
		delete[] elements;
		capacite = autre.nbElements;
		elements = new T[capacite];
	}
	for(int i=0; i<nbElements;i++)
		elements[i] = autre.elements[i];
		
	return *this;
}

// Constructeur par copie

template <class T>
Tableau<T>::Tableau(const Tableau<T>& autre)
{
	capacite = autre.capacite;
	nbElements = autre.nbElements;
	elements = new T[capacite];
	for(int i = 0; i < nbElements; i++)
		elements[i] = autre.elements[i];
}


// ============================================================
// ========================= PILES ============================
// ============================================================

// IMPLEMENTATION PAR TABLEAU =================================

// Representation - Pile

template <class T>
class Tableau
{
	// Autre (...)
	
	/*
	private:
		T* data;
		int capacite;
		int s; // Index sur le sommet
	*/
	
	private:
		Tableau<T> elements;
		
};

// Sommet

template <class T>
const T& PileTableau<T>::sommet() const
{
	return elements[elements.taille() - 1];
}

// Ajouter

template <class T>
void PileTableau<T>::empiler(const T& element) const
{
	elements.ajouter(element);
}

template <class T>
T PileTableau<T>::depiler() 
{
	T result = sommet();
	elements.enlever(elements.taille() - 1);
	return result;
}

// IMPLEMENTATION AVEC CHAINE DE CELLULES =========================

// Representation - Pile chainee

template <class T>
class Pile
{
	// Autre (...)
	
	private:
		class Cellule{
			Cellule(const T& c, Cellule* s) : contenu(c), suivante(s)
			T contenu;
			Cellule *suivante;
		};
	Cellule* sommet;	
};

// Vide

template <class T>
bool Pile<T>::vide() const
{
	return sommet == NULL;
}


// Empiler

template <class T>
void Pile<T>::empiler(const T& element) 
{
	sommet = new Cellule(element, sommet);
}


// Depiler

template <class T>
void Pile<T>::depiler() 
{
	assert(sommet!=NULL);
	Cellule* suivante = sommet->suivante;
	delete sommet;
	sommet = suivante;
}


//*** Operateur == 

template <class T>
bool Pile<T>::operator==(const Pile<T>& autre) const 
{
	if(&autre == this) return true;
	
	Cellule* t = sommet;
	Cellule* a = autre.sommet;
	
	// Inclure comparaison de taille
	
	while(a)
	{
		if(t->contenu != a->contenu)
			return false;
		t = t->suivante;
		a = a->suivante;
	}
	return true;
}

//*** Operateur = (affectation)

template <class T>
Pile<T>& Pile<T>::operator==(const Pile<T>& autre)  
{
	if(&autre == this) return *this;
	
	Cellule** t = &somme;	// pointeur de pointeur pour naviguer l'objet courant
	Cellule* aut = autre.sommet;
	
	while(aut)
	{
		if((*t) == NULL)	// Cas si fin de la pile actuelle (plus petite que la pile copiee)
			*t = new Cellule(aut->contenu, NULL);
		else				// Cas general
			(*t)->contenu = aut->contenu;
			
		t = &((*t)->suivante);
		aut = aut->suivante;
	}
	
	// Cas si la pile actuelle est plus grande que la pile copiee
	aut = *t;
	*t = NULL;
	
	while(aut!=NULL)
	{
		Cellule *temp = aut->suivante;
		delete aut;
		aut = temp;
	}
	
	return *this;
}

// ============================================================
// ========================= FILES ============================
// ============================================================

// IMPLEMENTATION PAR TABLEAU CIRCULAIRE ======================

template <class T>
class File
{
	// Autre (...)
	
	private:
		T* elements;
		int capacite;
		int f;
		int r;
		int n;	
};

// Tete

template <class T>
const T& FileCirculaire<T>::tete() const
{
	assert(!vide());
	return elements[f];
}

// Enfiler

template <class T>
void FileCirculaire<T>::enfiler(const T& element) 
{
	assert(taille() < capacite);
	elements[r] = element;
	r = (r+1) % capacite;
	n++;
}

//Defiler

template <class T>
void FileCirculaire<T>::defiler() 
{
	assert(!vide());
	f = (f+1) % capacite;
	n--;
}


// IMPLEMENTATION AVEC CHAINE DE CELLULES =========================

// Representation file chaine de cellules

template <class T>
class File
{
	// Autre (...)
	
	private:
		class Cellule{
			public:
				Cellule(const T& c, Cellule *s = NULL) : contenu(c), suivante(s)
				T contenu;
				Cellule* suivante;
		};
		
		Cellule* queue;
};

// Vide

template <class T>
bool File<T>::vide() const
{
	return queue == NULL;
}

// Tete

template <class T>
const T& File<T>::tete() const
{
	assert(queue!=NULL);
	return queue->suivante->contenu;
}

//Enfiler

template <class T>
void File<T>::enfiler(const T& element) 
{
	if(queue==NULL){
		queue = new Cellule(element);
		queue->suivante = queue;
	}
	else
		queue = queue->suivante = new Cellule(e,queue->suivante);
}


//Defiler

template <class T>
void File<T>::defiler() 
{
	Cellule* c = queue->suivante;
	
	if(queue==c)
		queue = NULL; 
	else
		queue->suivante = c->suivante;
	delete c;
}

//Vider (version 2)

template <class T>
void File<T>::vider() 
{
	Cellule* fin = queue;
	while(queue!=NULL)
	{
		Cellule *suivante = queue->suivante;
		if(suivant==fin)
			suivante = NULL;
		delete queue;
		queue = suivante;
	}

}


//Operator =

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
	
	// Cas 1 seul ajout (cela est il vraiment necessaire... oui)
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


// ============================================================
// ========================= LISTES ===========================
// ============================================================

// Representation

template <class T>
class Liste
{
	// Autre (...)
	
	struct Cellule{
		Cellule(const T& c, Cellule* s): suivante(s)
		{
			contenu = c;
		}
		T contenu;
		Cellule* suivante;
	
	private:
		Cellule* derniere;	
};

// Insertion (sans iterateur)

template <class T>
Cellule* Liste<T>::inserer(const T& element, Cellule *position) 
{
	if(derniere==NULL) // Cas de liste vide
	{
		derniere = new Cellule(element);
		position = derniere->suivante = derniere;
	}
	else if(position == NULL) // Insertion a la fin
	{
		position = derniere;
		derniere->suivante = new Cellule(element, derniere->suivante);
		derniere = derniere->suivante; // Deplacement du pointeur derniere vers la derniere cellule
	}
	else
		position->suivante = new Cellule(element,position->suivante);
	return position;
}

// Enlevement (sans iterateur)

template <class T>
Cellule* Liste<T>::enlever(Cellule *position) 
{
	assert(position!=NULL && derniere!= NULL) // position a la fin ou file vide
	
	Cellule* temp = position->suivante;
	position->suivante = temp->suivante;
	delete temp;
	
	// Cas de l'enlevement de la cellule a la fin de la liste
	Cellule* retour = temp==derniere ? NULL : position;
	if(derniere == temp) 
		derniere = position;
	
	// Cas de l'enlevement de la derniere cellule
	if(temp==position)
		derniere = position = NULL;
		
	return position;
}


// ITERATEUR ---------------------------------------------------


// Representation

template <class T>
class Liste
{
	class Iterateur{
		private:
			Cellule* precedente;
			const Liste& liste;
	};
};


// Vider

template <class T>
void Liste<T>::vider() 
{
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
	
}

template <class T>
const Liste<T>& Liste<T>::operator=(const Liste<T>& autre)
{
	if(this == &autre) return *this;
	vider();
	for(Iterateur ia = autre.debut();ia;++ia)
		inserer_fin(*ia);
		
	return *this;
}


// Insertion 

template <class T>
typename Liste<T>::Iterateur Liste<T>::inserer(const T& e, const Iterateur& i) 
{

	assert(this == &i.liste);
	
	Iterateur position(i);
	
	Cellule*c = i.precedente;

	if(derniere==NULL) // Cas de liste vide
	{
		derniere = new Cellule(e);
		derniere->suivante = derniere;
	}
	else if(c == NULL) // Insertion a la fin
	{
		c = derniere;
		derniere->suivante = new Cellule(e, derniere->suivante);
		derniere = derniere->suivante; 
	}
	else
		c->suivante = new Cellule(e,c->suivante);
	
	position.precedente = c;
	return position;
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


// Enlevement

template <class T>
typename Liste<T>::Iterateur Liste<T>::enlever(const Iterateur& i) 
{
	assert(this == &i.liste);
	
	Iterateur position(I);
	Cellule* c = i.precedente;
	
	assert(c != NULL && derniere != NULL); // Fin de liste ou liste vide
	Cellule* temp = c->suivante;
	c->suivante = temp->suivante;
	delete temp;
	
	// Cas de l'enlevement de la cellule a la fin de la liste
	Cellule* retour = temp==derniere ? NULL : c;
	if(derniere == temp) 
		derniere = c;
	
	// Cas de l'enlevement de la derniere cellule
	if(temp==c)
		derniere = c = NULL;
		
	position.precedente = retour;
		
	return position;
}

// Trouver

template <class T>
typename Liste<T>::Iterateur Liste<T>::trouver(const T& e) const {

	Iterateur iter(*this);
	while(iter && !(*iter == e))
		iter++;
	return iter;
}

// Operateur ==

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
	
	// Cas d'une liste plus longue que l'autre
	if(iter_autre.precedente != NULL || iter_listeActuelle.precedente != NULL)
    	return false;
    	
    return true;
  
}



