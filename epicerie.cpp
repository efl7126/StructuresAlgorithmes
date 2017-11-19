/*  AUTEUR(S):
    1) Ndjerandouba Jules + NDJJ15047609
    2) François-Guillaume Landry + LANF06109305
*/

#include <iostream>
#include "epicerie.h"
#include "arbremap.h"
#include "date.h"
#include "pointst.h"
#include <limits>
#include <math.h> 

// ==========================================================================
// ==================== Méthodes de la classe Epicerie ======================
// ==========================================================================


// =============== Contructeurs ===========================

Epicerie::Epicerie()
{
}

Epicerie::Epicerie(string _nom, PointST _position)
	: nom(_nom), position(_position)
{
}

// =============== Surcharge d'opérateurs ===========================

bool Epicerie::operator<(const Epicerie& autre) const{
    
    return(nom < autre.nom);
}

// =============== Autres méthodes ===========================

// Cette méthode sert à insérer un objet Aliment dans l'attribut arbreAliment de la classe Epicerie
void Epicerie::insererAliment(const string& nomAliment, const int& quantite, const Date& dateExpiration)
{	
	// Si le même aliment avec la même date d'expiration est déjà dans l'arbre, simplement
	// augmenter la quantité disponible
	if(arbreAliments[nomAliment].contient(dateExpiration))
	{
    	arbreAliments[nomAliment][dateExpiration].getQuantite() += quantite;
    }
    // Sinon, ajouter un nouvel objet Aliment
    else
    	arbreAliments[nomAliment][dateExpiration] = Aliment(nomAliment, quantite, dateExpiration);
}

void Epicerie::inventaire(Date& dateActuelle) {

	// Itérer sur chaque aliment
	typename ArbreMap<string, ArbreMap<Date, Aliment> >::Iterateur i = arbreAliments.debut();  
	for(;i;++i)
	{
		int quantiteParAliment = 0;
	
		// Itérer sur chaque date d'expiration
		typename ArbreMap<Date, Aliment>::Iterateur j = arbreAliments[i.cle()].rechercherEgalOuSuivant(dateActuelle);  
		for(;j;++j)
		{
			// Ajouter la quantité d'aliment associée à la date d'expiration si la date actuelle est plus petite
			if(dateActuelle < j.valeur().getDateExpiration())
				quantiteParAliment += j.valeur().getQuantite();
		}
		
		if(quantiteParAliment != 0)
			std::cout << i.cle() << " " << quantiteParAliment << "\t";	
	}
}

// ==========================================================================
// ==================== Méthodes de la classe Aliment =======================
// ==========================================================================


// =============== Contructeurs ===========================

Aliment::Aliment()
{
	nomAliment = " ";
	quantite = 0;
	dateExpiration = Date(0,0,0);
}

Aliment::Aliment(string _nomAliment, int _quantite)
	: nomAliment(_nomAliment), quantite(_quantite)
{
	dateExpiration = Date(0,0,0);
}

Aliment::Aliment(string _nomAliment, int _quantite, Date _date)
	: nomAliment(_nomAliment), quantite(_quantite), dateExpiration(_date)
{
}


// ==========================================================================
// ==================== Méthodes de la classe Carte =========================
// ==========================================================================


// =============== 1) Méthodes associées à la commande INVENTAIRE =============== 


// Cette méthode affiche l'inventaire d'une épicerie
void Carte::inventaire(string nomEpicerie){

	arbreEpiceries[nomEpicerie].inventaire(dateActuelle);
	
	std::cout << ";";
}


// =============== 2) Méthodes associées à la commande PLACER =============== 

// Cette méthode insère une nouvelle épicerie dans l'arbre arbreEpiceries de la classe Carte 
void Carte::insererEpicerie(string& nomEpicerie, PointST& position) {	
    	
    arbreEpiceries[nomEpicerie] = Epicerie(nomEpicerie, position);
    	
}


// =============== 3) Méthodes associées à la commande RECOMMANDER ===============    

// Cette méthode ajoute des pointeurs, vers les objets Epicerie contenus dans l'attribut 
// arbreEpiceries, à l'intérieur du tableau tableauEpiceries (qui est aussi un attribut de Carte). 
// Cette étape supplémentaire permet de calculer les distances de parcours de facon plus efficace 
// en facilitant l'accès aux épiceries : O(1) dans un tableau vs O(log n) dans un arbre.
void Carte::peuplerTableauEpiceries(bool premierPlacement) {
    
    if(!premierPlacement)
    	tableauEpiceries.vider();	// Vider le tableau précédent
    	
    typename ArbreMap<string, Epicerie>::Iterateur i = arbreEpiceries.debut();  
	for(;i;++i)
	{
		tableauEpiceries.ajouter(&i.valeur());
	}
		
	//tableauEpiceries.afficher();
}
    
void Carte::genererCombinaisons(int nbMaxEpicerie, int nbMaxEpiceriePrecedent) {

	// Cette méthode appelle la fonction combiner(), qui retourne toutes les combinaisons
	// d'épiceries possibles pour un ensemble de k épiceries, en fonction du nombre d'épiceries
	// stockées dans le tableauEpiceries. L'objectif est donc d'obtenir tous les trajets possibles
	// sans considérer l'ordre de visite des épiceries (qui sera déterminé plus tard). Il sera ensuite
	// possible d'enlever les combinaisons infaisables selon la commande, avant d'évaluer l'ordre 
	// de visite. Le but de cette approche est de sauver du temps d'exécution.
    	 	
    Tableau<int> tableauIndicesEpiceries;	// Tableau contenant les indices des éléments de tableauEpiceries
    Pile<int> combinaisonIndices;			// Pile qui sera utilisée pour générer des combinaisons d'indices
    	
    // Ajout des indices des éléments de tableauEpiceries
    for(int i = 0; i < tableauEpiceries.taille(); i++)
    {
    	tableauIndicesEpiceries.ajouter(i);
    }
    	
    // Génération de toutes les combinaisons possibles de k épiceries, k = 1, 2, 3... N
    // où N = min(nbMaxEpicerie, nombre d'éléments dans tableauEpiceries)
    	
    for(int nbElementsCombinaison = nbMaxEpiceriePrecedent; 
    nbElementsCombinaison <= (nbMaxEpicerie < tableauEpiceries.taille() ? nbMaxEpicerie : tableauEpiceries.taille()); 
    nbElementsCombinaison++)
    {
    	combiner(0,nbElementsCombinaison, tableauIndicesEpiceries, combinaisonIndices);
    }
    	
    // Affichage des combinaisons
    /*
    for(int j = 0; j < tableauCombinaisons.taille(); j++)
    	tableauCombinaisons[j].afficher();
    */
    	
}
    
void Carte::combiner(int offset, int k, Tableau<int>& tableauIndicesEpiceries, Pile<int>& combinaisonIndices) {
	
	// IMPORTANT: Cette méthode est inspirée du code à l'adresse suivante : 
	// https://stackoverflow.com/questions/12991758/creating-all-possible-k-combinations-of-n-items-in-c
	// Cette méthode retourne l'ensemble des combinaisons formées à partir de k épiceries.
	// Le résultat est stocké dans une pile, dont les éléments sont ensuite transférés vers un tableau.
	// Ce tableau est alors ajouté dans le tableau 2D 'tableauCombinaisons'(attribut de la classe Carte).
	// 'tableauCombinaisons' contiendra toutes les combinaisons possibles à partir de k indices d'épiceries.
	
	if (k == 0) {	// Génération d'une combinaison
		Pile<int> resultat = combinaisonIndices;
		Tableau<int> tab;
		while(!resultat.vide())
			tab.ajouter(resultat.depiler());
		tableauCombinaisons.ajouter(tab);
		return;
	  }
	  	
	for (int i = offset; i <= tableauIndicesEpiceries.taille() - k; ++i) {
		combinaisonIndices.empiler(tableauIndicesEpiceries[i]);
		combiner(i+1, k-1,tableauIndicesEpiceries, combinaisonIndices);
		combinaisonIndices.depiler();
	}
}
	
// L'objectif de cette méthode est de rejeter les combinaisons d'épiceries obtenues 
// précédemment qui ne permettent pas de satisfaire à la commande d'épicerie.
void Carte::evaluerCombinaisons(Commande& cmd, int nbMaxEpiceries) {
		
	for(int combo = 0; combo < tableauCombinaisons.taille(); combo++)
    {
    	bool combinaisonImpossible = false;
    	Commande cmdCopie = cmd;
    	Tableau<int> combinaison = tableauCombinaisons[combo];
    	
    	// Si la taille de la combinaison est plus grande que nbMaxEpiceries, il n'est pas
    	// nécessaire d'évaluer le reste des combinaisons. En effet, les combinaisons sont générées
    	// en ordre de taille par la méthode combiner().
    	if(combinaison.taille() > nbMaxEpiceries)
			break;
	
		// Copie de l'arbre d'aliments de la commande
		ArbreMap<string, Aliment> arbreAlimentsCmdCopie = cmdCopie.getArbreAliments();
	
	
		// Itérer sur chaque aliment de la commande
		typename ArbreMap<string, Aliment>::Iterateur i = arbreAlimentsCmdCopie.debut();  
		for(;i;++i)
		{	
			string nomAliment = i.cle();
		
			// Itérer sur chaque epicerie de la combinaison
			for(int j = 0; j < combinaison.taille(); ++j)
			{
				int indiceEpicerie = combinaison[j];
				ArbreMap<string, ArbreMap<Date, Aliment> >& arbreAlimentsEpicerie = tableauEpiceries[indiceEpicerie]->getArbreAliments();
				
			
				// Si l'epicerie de contient pas l'aliment en question, sauter d'epicerie
				if(!arbreAlimentsEpicerie.contient(nomAliment))
					continue;
				
				// Iterer sur chaque date d'expiration
				typename ArbreMap<Date, Aliment>::Iterateur k = arbreAlimentsEpicerie[nomAliment].rechercherEgalOuSuivant(dateActuelle);  
				for(;k;++k)
				{
					// Si l'épicerie contient un aliment recherché et que la date 
					// actuelle précède la date d'expiration, retirer la quantité disponible à l'épicerie
					// de la quantité inscrite dans la commande.
					if(dateActuelle < k.cle())
					{
						arbreAlimentsCmdCopie[nomAliment].getQuantite() -= 
							arbreAlimentsEpicerie[nomAliment][k.cle()].getQuantite();	
					}
					
				} // Iter date expiration
				
				if(arbreAlimentsCmdCopie[nomAliment].getQuantite() <= 0)
					break;
					
			} // Iter epicerie
			
			// Si pour un aliment quelconque de la commande, la quantité est demeurée positive
			// après le passage à chaque epicerie, cela indique que la combinaison ne permet pas
			// de remplir la commande.
			if(arbreAlimentsCmdCopie[nomAliment].getQuantite() > 0)
			{
				combinaisonImpossible = true;
				break;
			}
			
		} // Iter combinaison
	
		// Si la combinaison est possible, ajouter dans le tableau 'tableauCombinaisonsPossibles' 
		// (attribut de la calsse Epicerie)
		
		if(!combinaisonImpossible)
			tableauCombinaisonsPossibles.ajouter(combinaison);
	}
}

// L'objectif de cette méthode est de trouver le chemin le plus court en fonction d'une
// combinaison d'épiceries à parcourir.
void Carte::trouverCheminLePlusCourt(PointST positionInitiale, double distanceTotalMax) {
		
		
		// Génère les permutations possibles pour chaque combinaison d'épiceries permettant
		// de remplir la commande 
		genererPermutations();
		
		
		double distanceMin = distanceTotalMax;  // Correspond à la distance maximale permise dans la commande RECOMMANDER
		
		int indiceComboOptimal = 0, indicePermutOptimal = 0;
		
		
		// Itérer sur chaque combinaison
		for(int combo = 0; combo < tableauPermutations.taille(); combo++)
		{
			// Itérer sur chaque permutation
			for(int permut = 0; permut < tableauPermutations[combo].taille(); permut++)
			{
				double distance = 0;
				PointST pointPrecedent = positionInitiale;
				
				// Itérer sur chaque indice d'épicerie contenue dans la permutation
				for(int h = 0; h < tableauPermutations[combo][permut].taille(); h++)
				{
					int indiceEpicerie = tableauPermutations[combo][permut][h];
					PointST pointSuivant = tableauEpiceries[indiceEpicerie]->getPosition();
				
					// Ajouter la distance entre le point précédent (épicerie précédente ou
					// point de départ) et le point suivant (prochaine épicerie)
					
					distance = distance + pointPrecedent.distance(pointSuivant);
				
					pointPrecedent = pointSuivant;
			
				}
				
				// Ajouter la distance entre la dernière épicerie de la combinaison et 
				// le retour au point de départ
				distance += pointPrecedent.distance(positionInitiale);
				
				// Si la distance calculée est la plus petite jusqu'à date, sauvegarder.
				if(distance < distanceMin)
				{
					distanceMin = distance;
					indiceComboOptimal = combo;
					indicePermutOptimal = permut;
				}
			}
		}
		
		// Si aucune distance inférieure à 'distanceTotalMax' n'a été trouvée, il n'y a
		// aucun trajet possible. 
		if(distanceMin == distanceTotalMax)
		{
			std::cout << "IMPOSSIBLE";	
		}
		else
		{
			Tableau<int> indicesEpiceriesAVisiter = tableauPermutations[indiceComboOptimal][indicePermutOptimal];
			std::cout << round(distanceMin) << "m";
		
			// Affichage des épiceries
			for(int h = indicesEpiceriesAVisiter.taille() - 1; h >= 0; h--)
			{
				std::cout << " " << tableauEpiceries[indicesEpiceriesAVisiter[h]]->getNom();
			}
		}
}
	

	
// L'objectif de cette fonction est de générer les permutations possibles pour chaque combinaison 
// d'épiceries permettant de remplir la commande (stockées dans 'tableauCombinaisonsPossibles')	
void Carte::genererPermutations() {
    	
    	for(int i = 0; i < tableauCombinaisonsPossibles.taille(); i++)
    	{
    		tableauPermutations.ajouter(Tableau<Tableau<int> >());
    		permuter(tableauCombinaisonsPossibles[i].taille(), tableauCombinaisonsPossibles[i].taille(), tableauCombinaisonsPossibles[i], i);
    	}
    	
  
 		//Afficher
 		/*
    	for(int i = 0; i < combinaisonsPossibles.taille(); i++)	// QUESTION
    	{
    		for(int j = 0; j < tableauPermutations[i].taille(); j++)
    		{
    			(tableauPermutations[i][j]).afficher();
    		}
    	}
    	*/  	
}

    
void Carte::permuter(int k, int taille, Tableau<int> tabCombinaison, int indiceCombinaison) {

	// IMPORTANT: Cette méthode est inspirée du code disponible à l'adresse suivante : 
	// https://stackoverflow.com/questions/17396222/how-to-generate-all-permutations-of-an-array-in-sorted-order
	// Cette méthode retourne les tuples correspondant aux permutations de k éléments possibles à partir d'une
	// combinaison de k épiceries. Chaque permutation est représentée par un tableau d'indices d'épiceries 
	// ('tabCombinaison') qui est alors ajouté à l'attribut 'tableauPermutations' de Carte. 
	
		if (k == 0) {
		
			// Génération d'une permutation
			tableauPermutations[indiceCombinaison].ajouter(tabCombinaison);	
	  	}
	  	else
	  	{
			for (int i = k - 1; i >= 0; i--) {
				echanger(i,k-1,tabCombinaison);
				permuter(k-1,taille,tabCombinaison,indiceCombinaison);
				echanger(i,k-1,tabCombinaison);
		  	}
		}
		
		return;
}

// Fonction echanger appelée par permuter() 	
void Carte::echanger(int x, int y, Tableau<int>& tabCombinaison) {
	
		int temp = tabCombinaison[x];
		tabCombinaison[x] = tabCombinaison[y];
		tabCombinaison[y] = temp;
		
		return;
}


// =============== Fonctions de suppression ===========================

void Carte::viderTableaux() {
	
	tableauCombinaisonsPossibles.vider();
	tableauPermutations.vider();
	
}

void Carte::viderTableauCombinaisons() {
	
	tableauCombinaisons.vider();
	
}


// =============== 4) Méthodes associées à la commande RAMASSER =============== 

// Cette méthode ramasse les produits spécifiés dans la commande RAMASSER
// en passant par les épiceries (dans l'ordre) dont le nom est contenu dans le
// tableau 'tabEpiceries'

	
void Carte::ramasserProduits(Tableau<string>& tabEpiceries, Commande cmdCopie) {
		
	
	// Itérer sur chaque aliment de la commande
	typename ArbreMap<string, Aliment>::Iterateur iterCmd = cmdCopie.getArbreAliments().debut();  
	for(;iterCmd;++iterCmd)
	{
	
		string nomAliment = iterCmd.cle();
		Aliment& refAlimentCommande = cmdCopie.getArbreAliments()[nomAliment]; // Reference sur l'aliment de la commande visite
		
		// Itérer sur chaque épicerie 	
		for(int i = 0; i < tabEpiceries.taille(); i++)
		{	
		
			if(refAlimentCommande.getQuantite() == 0)
				break;
			
			// Itérateur sur l'épicerie correspondante dans 'arbreEpiceries'
			typename ArbreMap<string, Epicerie>::
				Iterateur iterEpicerie = arbreEpiceries.rechercher(tabEpiceries[i]);	
		
			if(!iterEpicerie)
				continue;
		
			ArbreMap<string, ArbreMap<Date, Aliment> >& refArbreAliments = iterEpicerie.valeur().getArbreAliments();
			
		
			if(refArbreAliments.contient(nomAliment))	// Si l'épicerie contient l'élement recherché dans la commande
			{
			
				// Générer une pile des aliments disponibles dans l'épicerie en fonction de la date d'expiration 
				
				Pile<Aliment*> pilePointeursAliments;
				
				
				// Itérer sur les dates
				typename ArbreMap<Date, Aliment>::Iterateur iterDate = refArbreAliments[nomAliment].debut();  
				for(;iterDate;++iterDate)
				{
					pilePointeursAliments.empiler(&(iterDate.valeur()));
				}
					
				// --------------- Ramasser les produits de la commande --------------------

				while(!pilePointeursAliments.vide())
				{
					Aliment* pAlimentCourant = pilePointeursAliments.depiler();
					
					if(dateActuelle < pAlimentCourant->getDateExpiration() && 
						pAlimentCourant->getQuantite() > 0)	// Pour chaque date d'expiration de la pile
					{
					
						// Si l'épicerie possède l'aliment en plus petite quantité que celle requise par la commande
						if(refAlimentCommande.getQuantite() - pAlimentCourant->getQuantite() >= 0)
						{
							// Soustraire la quantité disponible de la commande
							refAlimentCommande.getQuantite() -= pAlimentCourant->getQuantite();
					
							// Enlever la quantité de l'inventaire de l'epicerie
							pAlimentCourant->getQuantite() = 0;
						}
						else // Si l'épicerie possède l'aliment en plus grande quantité que celle requise par la commande
						{
							// Enlever la quantité de l'inventaire de l'epicerie
							pAlimentCourant->getQuantite() -= refAlimentCommande.getQuantite();
					
							// La commande est terminee
							refAlimentCommande.getQuantite() = 0;
						}
					}
				} // Iter date d'expiration
			}	
			
		} // Iter épicerie
		
	} // Iter aliment	
	
	// Affichage ==============================================
	
	bool manque = false;
		
	typename ArbreMap<string, Aliment>::Iterateur k = cmdCopie.getArbreAliments().debut();  
	for(;k;++k)
	{
		Aliment& refAliment = cmdCopie.getArbreAliments()[k.cle()];
		
		if(refAliment.getQuantite() > 0)
		{
			if(!manque)
				std::cout << "MANQUE ";
			std::cout << refAliment.getNomAliment() << " " << refAliment.getQuantite() << "\t";
			manque = true;
		}
	}
	if(!manque)
		std::cout << "COMPLET";
	else
		std::cout << " ;";
}
	
// ================== Fonctions d'affichage ===============================
	
	
void Carte::afficherContenuEpiceries() {
    	
    typename ArbreMap<string, Epicerie>::Iterateur i = arbreEpiceries.debut();  
	for(;i;++i)
	{
		std::cout << i.valeur() << endl;
	}
}
    

// ==========================================================================
// ============================ Fonctions amies =============================
// ==========================================================================


istream& operator>>(istream& is, Commande& c){
    string nomproduit;
    is >> nomproduit;
    while(is && nomproduit!=";"){
		int quantite;
		is >> quantite;
		
		Aliment alimentAjouter(nomproduit, quantite);
		c.arbreAliments[nomproduit] = alimentAjouter;
		
		is >> nomproduit;
    }
    return is;
}

ostream& operator << (ostream& os, const Epicerie& epicerie)
{ 
    os 	<< epicerie.nom << std::endl;
    
    //epicerie.arbreAliments.afficher();
    
    return os;
}

ostream& operator << (ostream& os, const Aliment& aliment)
{ 
    os 	<< aliment.nomAliment << " " << aliment.quantite << " " << aliment.dateExpiration;
    
    return os;
}



