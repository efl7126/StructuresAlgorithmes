/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    Automne 2017 | TP2
    http://ericbeaudry.uqam.ca/INF3105/tp2/   

    AUTEUR(S):
     1) Nom + Code permanent du l'étudiant.e 1
     2) Nom + Code permanent du l'étudiant.e 2
*/
#include <fstream>
#include <iostream>
#include <string>
#include <cassert>
#include <cmath>
#include <limits>
#include "date.h"
#include "epicerie.h"
#include "pointst.h"

using namespace std;


void traiterCommandeRecommander(Carte& carte, PointST& position, int nbMaxEpicerie,
double distanceMaximale, Commande& cmd, bool genererCombinaisons, bool premiereCommandeRecommander, int nbMaxEpiceriePrecedent);

int tp2(istream& entree){
    
    /* 
       La classe Carte possède un Arbre Map comme attribut qui contient toutes les épiceries
       spécifiées par la commande PLACER (arbreEpiceries). La classe Carte comporte également la majorité
       des méthodes utilisées pour déterminer le trajet le plus rapide.
    */
    
    Carte carte;
    
    Date maintenant;	// Instanciation d'un objet de la classe Date qui contiendra la date
    					// actuelle spécifiée par la commande DATE.
    					
    bool premiereCommandePlacer = true;
    bool premiereCommandeRecommander = true;
    
    bool regenererCombinaisons = true;	// Si le tableau contenant les combinaisons d'epiceries doit être regénéré
    int nbMaxEpiceriesPrecedent = 0;	// Le plus grand nbMaxEpicerie spécifié depuis la dernière commande PLACER
    
    
    // Lecture des commandes ==============================================================
    while(entree){
    
        string typecommande;
        entree >> typecommande;
        
        if(!entree) break; // détection fin ==> sortie
        
        if(typecommande=="RECOMMANDER"){
            
            PointST p;
            int nbMaxEpiceries=0;	// Nombre maximal d'épiceries pouvant être visitées par trajet
            double maxdistance=0;	// Distance maximale pouvant être parcourue dans un trajet
            Commande c;
            char deuxpoints=0;
            entree >> p >> nbMaxEpiceries >> maxdistance >> deuxpoints >> c;
            assert(deuxpoints==':');
            
            // Lorsqu'une commande RECOMMANDER est spécifiée, les combinaisons d'indices d'épiceries (possibles et
            // non possibles pour remplir une commande) sont tout d'abord générées. Le booléen regenererCombinaisons
            // indique si ces combinaisons doivent être regénérées en entier (suite à l'ajout d'une épicerie avec la
            // commande PLACER). 
            if(!regenererCombinaisons)
            {
            	// Si le nbMaxEpiceries de la commande actuelle est plus petit ou égal que nbMaxEpiceriesPrecedent, 
            	// les combinaison nécessaires ont déjà été générées.
           		if(nbMaxEpiceriesPrecedent >= nbMaxEpiceries)
            		traiterCommandeRecommander(carte, p, nbMaxEpiceries, maxdistance, c, false, premiereCommandeRecommander, 1);
            	// Si le nbMaxEpiceries de la commande actuelle est plus grand que nbMaxEpiceriesPrecedent, 
            	// les combinaison nécessaires pour n éléments, nbMaxEpiceriesPrecedent < n <= nbMaxEpiceries, doivent
            	// être générées.  
            	else 
            		traiterCommandeRecommander(carte, p, nbMaxEpiceries, maxdistance, c, true, premiereCommandeRecommander, nbMaxEpiceriesPrecedent + 1);
            	
            	// Affecter à nbMaxEpiceriesPrecedent le maximum de nbMaxEpiceriesPrecedent et nbMaxEpiceries
            	nbMaxEpiceriesPrecedent = nbMaxEpiceriesPrecedent < nbMaxEpiceries ? nbMaxEpiceries : nbMaxEpiceriesPrecedent;
            	
            }
            // Si le booléen regenererCombinaisons est true, regénérer toutes les combinaisons.
            else
            {
            	traiterCommandeRecommander(carte, p, nbMaxEpiceries, maxdistance, c, true, premiereCommandeRecommander, 1);
            	nbMaxEpiceriesPrecedent = 0;
            }
           
            regenererCombinaisons = false;
            premiereCommandeRecommander = false;
                       
            
        }else if(typecommande=="RAMASSER"){
            
            Tableau<string> tabEpiceries;
            
            Commande c;
            entree >> c;
            string nomepicerie;
            entree >> nomepicerie;
            
            // Ajout ---------------------------------------
            tabEpiceries.ajouter(nomepicerie);
            
            while(entree && nomepicerie!=";" && nomepicerie!=" ;" && nomepicerie!="; "){
                
                entree >> nomepicerie;
                
                tabEpiceries.ajouter(nomepicerie);
            }
            
            carte.ramasserProduits(tabEpiceries, c);
            

        }else if(typecommande=="APPROV"){
            string nomepicerie;
            char deuxpoints=0;
            entree >> nomepicerie >> deuxpoints;
            assert(deuxpoints==':');
            string nomproduit;
            entree >> nomproduit;
            
            // Ajout ---------------------------------------
            
            // Obtient une référence sur l'épicerie à laquelle il faut approvisionner
            Epicerie& refEpicerie = carte.getArbreEpiceries()[nomepicerie];
            
            while(entree && nomproduit!=";"){
                int quantite;
                Date dateexpiration;
                entree >> quantite >> dateexpiration;
                
                // Pour chaque produit, faire l'insertion dans l'épicerie contenue dans arbreEpiceries
                refEpicerie.insererAliment(nomproduit, quantite, dateexpiration);
                
                entree >> nomproduit;
            }
           
            cout << "OK";
            
        }else if(typecommande=="PLACER"){
            PointST position;
            string nom;
            char pointvirgule=0;
            entree >> nom >> position >> pointvirgule;
            assert(pointvirgule==';');
            
            // Ajout ---------------------------------------

            // Insertion de l'épicerie à placer
            carte.insererEpicerie(nom,position);
            // Remplir le tableauEpiceries. Cette étape supplémentaire permet de calculer les 
            // distances de parcours de facon plus efficace en facilitant l'accès aux épiceries : 
            // O(1) dans un tableau vs O(log n) dans un arbre.
            carte.peuplerTableauEpiceries(premiereCommandePlacer);	
            
            cout << "OK";
            
			premiereCommandePlacer = false;
			regenererCombinaisons = true;	// Après l'ajout d'une épicerie, il faut regénérer les combinaisons
											// d'épiceries.
            
        }else if(typecommande=="INVENTAIRE"){
            string nomepicerie;
            char pointvirgule=0;
            entree >> nomepicerie>> pointvirgule;
            assert(pointvirgule==';');
            
            // Ajout ---------------------------------------
            
            carte.inventaire(nomepicerie);
            
 
        }else if(typecommande=="DATE"){
            char pointvirgule=0;
            entree >> maintenant >> pointvirgule;
            assert(pointvirgule==';');
            
            // Ajout ---------------------------------------
            
            carte.fixerDateActuelle(maintenant);
            
            cout << "OK";
            
        }else{
            cout << "Commande '" << typecommande << "' invalide!" << endl;
            return 2;
        }
        cout << endl;
        entree >> ws; // force la lecture d'un espace blanc.
    }
    return 0;
}
// syntaxe d'appel : ./tp2 [nomfichier.txt]
int main(int argc, const char** argv){
    // Gestion de l'entrée :
    //  - lecture depuis un fichier si un argument est spécifié;
    //  - sinon, lecture depuis std::cin.
    if(argc>1){
         std::ifstream entree_fichier(argv[1]);
         if(entree_fichier.fail()){
             std::cerr << "Erreur d'ouverture du fichier '" << argv[1] << "'" << std::endl;
             return 1;
         }
         return tp2(entree_fichier);
    }else
         return tp2(std::cin);        

    return 0;
}

// Cette fonction est appelée pour traiter la commande RECOMMANDER
void traiterCommandeRecommander(Carte& carte, PointST& position, int nbMaxEpicerie,
double distanceTotalMax, Commande& cmd, bool genererCombinaisons, bool premiereCommandeRecommander, int nbMaxEpiceriePrecedent)
{
	// Si la totalité des combinaisons doivent être générées, il faut d'abord vider le
	// tableau qui contient ces combinaisons.
	if(genererCombinaisons)
	{
		if(!premiereCommandeRecommander && nbMaxEpiceriePrecedent == 1)
			carte.viderTableauCombinaisons();
		carte.genererCombinaisons(nbMaxEpicerie, nbMaxEpiceriePrecedent);
	}
	
	carte.evaluerCombinaisons(cmd, nbMaxEpicerie);
	carte.trouverCheminLePlusCourt(position, distanceTotalMax);
	carte.viderTableaux();

}


