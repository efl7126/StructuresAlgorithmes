// ============================================================
// ====================== ARBRE GENERAL =======================
// ============================================================

// Representation - Arbre general

template <class T>
class Arbre
{
	private:
		class Noeud{
		
		private:
			T contenu;
			Noeud* parent;
			Liste<Noeud*> enfants;
		};
		
	Noeud* racine;
} 

// Parcours en preordre

template <class T>
void Arbre<T>::afficherPreOrdre() const{
	afficherPreOrdre(racine);
}

template <class T>
void Arbre<T>::afficherPreOrdre(Noeud* n) const{
	
	if(n==NULL) return;
	std::cout << n->contenu << "";	// Affichage de la racine en premier
	
	Liste<Noeud*>::Iterateur iter = n->enfants.debut(); // Iterateur sur le premier enfant
	
	while(iter)
		afficherPreOrdre(*iter++);
	
}

// Parcours en postordre

template <class T>
void Arbre<T>::afficherPostOrdre() const{
	afficherPostOrdre(racine);
}

template <class T>
void Arbre<T>::afficherPostOrdre(Noeud* n) const{
	
	if(n==NULL) return;
	
	Liste<Noeud*>::Iterateur iter = n->enfants.debut(); // Iterateur sur le premier enfant
	
	while(iter)
		afficherPreOrdre(*iter++);
		
	std::cout << n->contenu << "";	// Affichage de la racine en dernier
	
}


// Parcours en largeur

template <class T>
void Arbre<T>::afficherLargeur(){
	
	File<Noeud*> noeuds_a_visiter;
	
	if(racine!=NULL)
		noeuds_a_visiter.enfiler(racine);	// Enfiler la racine
	
	while(!noeuds_a_visiter.estVide())
	{
		Noeud* courant = noeuds_a_visiter.defiler();
		std::cout << courant->contenu << ""; // Affichage
		
		Liste<Noeud*>::Iterateur iter = courant->enfants.debut();
		while(iter)
			noeuds_a_visiter.enfiler(*iter++);
	}
}


// ============================================================
// ========== ARBRE BINAIRE DE RECHERCHE ======================
// ============================================================

// Representation - Arbre binaire

template <class T>
class ArbreBinaire
{
	// Manque qqchose
	
		private:
		struct Noeud
		{
			T contenu;
			Noeud* gauche;
			Noeud* droite;
		};
		
	Noeud* racine;
} ;

// Representation - Arbre binaire de recherche

template <class T>
class ArbreBinRech : public ArbreBinaire
{
	public:
		bool contient(const T& element) const;
		const T* rechercher(const T& element) const;
		void inserer(const T& element);
	private:
		const T* rechercher(Noeud* n, const T& element) const;
		void inserer(Noeud*& n, const T& element);
	
		private:
		struct Noeud
		{
			T contenu;
			Noeud* gauche;
			Noeud* droite;
		};
		
	Noeud* racine;
} 

// Parcours en inordre

template <class T>
void ArbreBinaire<T>::afficher_inordre(){
	afficher_inordre(racine);
}

template <class T>
void ArbreBinaire<T>::afficher_inordre(Noeud* n){
	
	if(n==NULL) return;
	afficher_inordre(n->gauche);
	std::cout << n->contenu << "";
	afficher_inordre(n->droite);
}


// =======================================================

// Recherche

template <class T>
bool ArbreBinRech<T>::contient(const T& element) const{
	return rechercher(racine, element)!=NULL;
}

// Version avec == et >
template <class T>
const T* ArbreBinRech<T>::rechercher(Noeud* noeud, const T& element) const
{
	if(noeud==NULL) return NULL;
	if(element == noeud->contenu)	// Cas egal
		return &(noeud->contenu);
	if(element < noeud -> contenu)
		return rechercher(noeud->gauche, element);	// Cas plus petit
	else	// Cas plus grand
		return rechercher(noeud->droite, element);
		
}


// Recherche -- Version non recursive

template <class T>
bool ArbreBinRech<T>::contient(const T& element) const{
	return rechercher(element)!=NULL;
}

template <class T>
const T* ArbreBinRech<T>::rechercher(const T& element) const
{
	Noeud*n = racine;
	
	while(n!=NULL)
	{
		if(element < n->contenu)
			n = n->gauche;
		else if(n->contenu < element)
			n = n->droite;
		else
			return &(n->contenu);
	}
	return NULL;	
}

 
// Insertion (ebauche 3)

template <class T>
bool ArbreBinRech<T>::inserer(const T& e) const{
	inserer(racine, e);
}

template <class T>
void ArbreBinRech<T>::inserer(Noeud*& n, const T& e) 
// Pointeur recu par reference permet d'unifier le cas de la racine et les autres cas
{
	if(n == NULL)
		n = new Noeud(e);
	else if(e == n->contenu)
		n->contenu = e;
	else if(e < n->contenu)
		inserer(n->gauche,e);
	else
		inserer(n->droite,e);
}

// Version non recursive d'inserer
template <class T>
void ArbreBinRech<T>::inserer(const T& e) 
{
	Noeud**n = &racine;	// n est un pointeur de pointeur
	while(n != NULL)
	{
		if(e < (*n)->element)
			n = &((*n)->gauche);
		else if((*n)->element < e)
			n = &((*n)->droite);
		else
		{
			(*n)->element = e;
			return;
		}	
	}
	*n = new Noeud(e);
}
	

// Enlevement dans un arbre de recherche binaire --------------------------------

template <class T>
Noeud* ArbreBinRech<T>::trouverMin(Noeud* n) const
{
	if(n!=NULL)
	{
		while(n->gauche != NULL)
			n = n->gauche;
			
		return n;
	}
}


template <class T>
void ArbreBinRech<T>::supprimerMin(Noeud*& n) const
{
	assert(n != NULL);
	
	if(n->gauche != NULL)
		supprimerMin(n->gauche);
	else
	{
		Noeud* tmp = n;
		n = n->droite;	// Le pointeur est passe par reference! PAS SUR
		delete temp;
	}
}

template <class T>
void ArbreBinRech<T>::enlever(const T& e, Noeud*& n) const
{
	assert(n != NULL);
	
	if(e < n->contenu) // Cas de gauche
		enlever(e,n->gauche);
	else if(n->contenu < e) // Cas de droite
		enlever(e,n->droite);
	// Ensuite, par defaut, on a trouve l'element
	else if(n->gauche != NULL && n->droite != NULL) //CAS 3 : A deux enfants
	{
		n->contenu = trouverMin(n->droite)->contenu; // On cherche le minimum dans le s-a droit et on remplace la valeur
		supprimerMin(n->droite);
	}
	else // CAS 2 : 1 enfant (et 0 enfant?)
	{
		Noeud* tmp = n;
		
		n = (n->gauche != NULL) ? n->gauche : n->droite;
		
		delete tmp; // OK
	}
	
}

// Vider

template <class T>
ArbreBinaire<T>::~ArbreBinaire()
{
	vider();
}

template <class T>
void ArbreBinaire<T>::vider()
{
	vider(racine);
	racine = NULL;
}

template <class T>
void ArbreBinaire<T>::vider(Noeud *n)
{
	if(n == NULL) return;
	vider(n->gauche);
	vider(n->droite);
	delete n;				// Ressemble post-ordre
}

// Constructeur par copie

template <class T>
ArbreBinaire<T>::ArbreBinaire(const ArbreBinaire& autre)
: racine(NULL)
{
	copier(autre.racine, racine);
}

template <class T>
void ArbreBinaire<T>::copier(const Noeud* source, Noeud*& noeud)
: racine(NULL)
{
	if(source!=NULL)
	{
		noeud = new Noeud(source->contenu);
		copier(source->gauche, noeud->gauche);
		copier(source->droite, noeud->droite);		// Ressemble pre-ordre
	}
}

// Operateur d'affectation =

template <class T>
ArbreBinaire<T>& ArbreBinaire<T>::operator=(const ArbreBinaire& autre)
{
	if(this == &autre) return *this;
	vider()
	copier(autre.racine, racine);
	return *this;
}


// ============================================================
// ========== ARBRE AVL =======================================
// ============================================================

// Representation - Arbre AVL

template <class T>
class Arbre
{	
	private:
		class Noeud
		{
			T element;
			Noeud* gauche;
			Noeud* droite;
			int equilibre;
		};
		
	Noeud* racine;
} ;

// Insertion ---------------------------------------------

template <class T>
void Arbre<T>::inserer(const T& e){
	inserer(racine,e);
}

template <class T>
bool Arbre<T>::inserer(Noeud*& n, const T& e){
	if(n==NULL)	// On est rendu au bout d'une feuille
	{
		n = new Noeud(e);
		return true;
	}
	if(e < n->element)	// Cas de gauche
	{
		if(inserer(n->gauche,e))
		{
			n->equilibre++;
			if(n->equilibre==0) return false;
			if(n->equilibre==1) return true;
			assert(n->equilibre==2);
			if(n->gauche->equilibre==-1)
				rotationDroiteGauche(n->gauche)
			rotationGaucheDroite(n);
		}
		return false;	//Si l'appel d'insertion a gauche retourne 0, ou si on fait une rotation
	}
	else if(n->element < e) // Cas de droite
	{
		if(inserer(n->droite,e))
		{
			n->equilibre--;
			if(n->equilibre==0) return false;
			if(n->equilibre==-1) return true;
			assert(n->equilibre==-2);
			if(n->droite->equilibre==1)
				rotationGaucheDroite(n->droite)
			rotationDroiteGauche(n);
		}
		return false;
	}
	else // L'element est deja present
	{
		n->contenu = e;
		return false;	// L'equilibre n'a pas change
	}	
}


// Rotation gauche droite ---------------------------------------------

template <class T>
void Arbre<T>::rotationGaucheDroite(Noeud*& racineSousArbre){
	
	Noeud* a = racineSousArbre->gauche;
	Noeud* b = racineSousArbre;
	
	// Calcul des equilibres
	int ea = a->equilibre;
	int eb = b->equilibre;
	int ebp = - (ea > 0 ? ea : 0) - 1 + eb;
	int eap = ea + (ebp < 0 ? ebp : 0) - 1;
	
	a->equilibre = eap;
	b->equilibre = ebp;
	
	// Changement des pointeurs
	
	b->gauche = a->droite;
	a->droite = b;
	racineSousArbre = a;
}


// Rotation droite gauche ---------------------------------------------

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
    
    //----
    racinesousarbre->droite = temp->gauche;
    temp->gauche = racinesousarbre;
    racinesousarbre = temp;
}

// Enlevement


template <class T>
void Arbre<T>::supprimer(const T& e) const
{
	supprimer(e, racine);
}

template <class T>
void Arbre<T>::supprimer(const T& e, Noeud*& n) 
{
	if(e < n->contenu) // Cas de gauche
	{
		bool r = false;
		if(supprimer(e, n->gauche))
		{
			(n->equilibre)--;
			if(n->equilibre == 1) return false;
			if(n->equilibre == 0) return true;
			r = n->droite->equilibre != 0;
			if(n->droite->equilibre==1)
				rotationGaucheDroite(n->droite);
			rotationDroiteGauche(n);
		}
		return r;
	}
	
	if(n->element < e) // Cas de droite
	{
	}
	
	// Cas e == n->element
	Noeud* temp = n;
	
	if(n->gauche == NULL)	// 1 element a droite
	{
		n = n->droite;
		delete temp;
		return true;
	}
	if(n->droite == NULL)	// 1 element a gauche
	{
		n = n->gauche;
		delete temp;
		return true;
	}
	
	// Cas avec deux enfants
	
	n->contenu = trouverMax(n->gauche);
	n = temp;
	return supprimer(n->contenu, n->gauche);
	
}

// Vider

template <class T>
void ArbreAVL<T>::vider(Noeud*& noeud)
{
	if(noeud == NULL)
		return;
	
	// Post-ordre
	vider(noeud->gauche);
	vider(noeud->droite);
	
	delete noeud;
	noeud = NULL;

}

// Copier
template <class T>
void ArbreAVL<T>::copier(const Noeud* source, Noeud*& noeud) const
{
	if(source == NULL)
		return;
	
	noeud = new Noeud(source->contenu);
	noeud->equilibre = source->equilibre;
	
	// Pre-ordre
	
	copier(source->gauche, noeud->gauche);
	copier(source->droite, noeud->droite);
}


// Hauteur
template <class T>
int  ArbreAVL<T>::hauteur() const{

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


// Max de l'arbre

template <class T>
const T& ArbreAVL<T>::max(Noeud* n) const
{
	Iterateur iter(*this);
	iter.courant = racine;
	
	if(iter.courant != NULL)
	{
		while(iter.courant->droite != NULL)
		{
			iter.courant = iter.courant->droite;
		}
	}
	
	return (iter.courant)->contenu;
	
}


// Debut de l'arbre

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

// Fin de l'arbre

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::fin() const
{
	Iterateur iter(*this);
	iter.courant = NULL;
    return iter;	
}

// Rechercher

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
		else
		{
			iter.courant = n;
		}
	}
	
	iter.chemin.vider();
	
	return iter;
	
}


// Rechercher egal ou precedent

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
		else
		{
			return rechercher(e);
		}
	}
	
	if(dernier != NULL)
		return rechercher(dernier->contenu);
		
	return Iterateur(*this);
}


// Recherche Egal ou Suivant

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercherEgalOuSuivant(const T& e) const
{

	Noeud* n = racine;
	Noeud* suivant = NULL;
	Pile<Noeud*> pile;
	
	while(n)
	{
		if(e < n->contenu)
		{
			pile.empiler(n);
			n = n->gauche;
		}
		else if(n->contenu < e)
		{
			n = n->droite;
		}
		else
		{
			return rechercher(e);
		}
	}
	
	if(!pile.vide())
	{
		suivant = pile.depiler();
		return rechercher(suivant->contenu);
	}
	
	return Iterateur(*this);
}
			


// Iterateur ===============================================

// Representation - Iterateur

template <class T>
class Arbre
{	
	class Iterateur
	{
		private:
			const Arbre& arbre;
			Noeud* courant;
			Pile<Noeud*> chemin;
		friend class
	};
		
	Noeud* racine;
} ;


// Constructeur (une des deux versions)

template <class T>
Arbre<T>::Iterateur::Iterateur(const Arbre a) : arbre(a)
{
	courant = arbre.racine;
	if(courant == NULL) return;
	while(courant->gauche != NULL)
	{
		chemin.empiler(courant);
		courant = courant->gauche;
	}
}

// Pre-increment

template <class T>
const Iterateur& Arbre<T>::Iterateur::operator++()
{
	assert(courant!=NULL);
	Noeud* suivant = courant->droite;
	
	while(suivant!=NULL)	// Empiler tous les elements de gauche apres celui de droite
							// Donnera le min du s-a droite
	{
		chemin.empiler(suivant);
		suivant=suivant->gauche;
	}
	if(!chemin.vide())
		courant = chemin.depiler();
	else			// La pile est vide, donc on s'est seulement deplace a droite
		courant = NULL;
	return *this;
} 

// Post-incrément

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::Iterateur::operator++(int)
{
	Iterateur copie(*this);
	operator++();
	return copie;
}


