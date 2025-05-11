
//FICHIER main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "animal.h"
#include "refuge.h"


// Fonction qui affiche le menu des actions disponibles et retourne le choix de l'utilisateur
int menu(){
int option;
printf(" ____________________________________________________MENU___________________________________________________\n");
printf("1. Rechercher un ou plusieurs animaux dans le refuge.\n");
printf("2. Ajouter un animal qui a ete confie au refuge.\n");
printf("3. Supprimer un animal qui a ete adopte du refuge.\n");
printf("Veuillez choisir l'action a realiser (1,2 ou 3) : ");
scanf("%d", &option);
printf(" ___________________________________________________________________________________________________________\n");
    return option;
}

// Fonction principale
int main(){
srand(time(NULL));
printf("____________________________________________________________________________________________________________\n");
printf("                                     BIENVENUE AU CHENIL ChenYI-Tech !                                      \n");
printf("____________________________________________________________________________________________________________\n\n");
Animal **refuge = NULL; // Pointeur vers un tableau de pointeurs d'animaux, initialement vide
int i, nb_r, choix, taille = 0, id;
char continuer;
refuge = charger_refuge(&taille, "animaux/refuge.txt");
do{ // Boucle principale du programme, permet de répéter les actions tant que l'utilisateur le souhaite
    choix = menu();
    if(choix == 1){ // Option : Recherche d'un ou plusieurs animaux
        if(taille == 0){ // Cas 1 : Le tableau est vide, on ne peut pas effectuer de recherche
            printf("\nVous ne pouvez pas rechercher d'animaux car le refuge est vide.\n");
        }else{ // Cas 2 : Le tableau n'est pas vide, on peut effectuer des recherches
        printf("\nCombien d'animaux souhaitez-vous rechercher ? : ");
        scanf("%d", &nb_r);
        printf("\nVeuillez saisir au minimum deux parametres de recherche (Tapez 'X' si vous ne connaissez pas un parametre).\n");
        for(i = 0; i < nb_r; i++){ // Boucle pour effectuer autant de recherches que l'utilisateur le souhaite
            char nom[50], espece[50], tranche_age[50];
            int nb_p;
            do{ // Boucle pour saisir les critères de recherche (nom, espèce, tranche d'âge)
                nb_p = 0;
                printf("\nVeuillez saisir le nom de l'animal recherche : ");
                scanf("%49s", nom);
                if(strcmp(nom, "X") != 0){ // Si l'utilisateur ne saisit pas "X"
                    nb_p++; //
                }
                printf("\nVeuillez saisir l'espece de l'animal recherche : ");
                scanf("%49s", espece);
                if (strcmp(espece, "X") != 0){
                    nb_p++;
                }
                printf("\nVeuillez saisir la tranche d'age de l'animal recherche: ");
                scanf("%49s", tranche_age);
                if(strcmp(tranche_age, "X") != 0){
                    nb_p++;
                }
                if(nb_p < 2){ // Si moins de 2 critères ont été renseignés
                    printf("\nVeuillez remplir au moins deux champs pour effectuer une recherche valide.\n");
                }
                }while(nb_p < 2); // Boucle jusqu'à ce qu'au moins deux critères soient renseignés
                rechercher_Animal(refuge, taille, nom, espece, tranche_age); // Appel de la fonction de recherche d'animaux
            }
            }
    }else if(choix == 2){ // Option : Accueil d'un animal au refuge
        Animal *a = constructeur(refuge, taille); // Création d'un nouvel animal
        refuge = ajouter_Animal(refuge, &taille, a); // Ajout de l'animal au refuge
    }else if(choix == 3){  // Option : Adoption d'un animal du refuge
        if(taille == 0){ // Cas 1 : Le tableau est vide, on ne peut pas adopter d'animal
            printf("\nVous ne pouvez pas adopter d'animaux car le refuge est vide.\n");
        }else{ // Cas 2 : Le tableau n'est pas vide, on peut adopter un animal à partir d'un ID
            printf("\nVeuillez saisir l'identifiant de l'animal a adopter : ");
            scanf("%d", &id);
            refuge = enlever_Animal(refuge, &taille, id); // Suppression de l'animal adopté du refuge
        }
    }else{ // Si l'utilisateur entre une option invalide
        printf("\nOption invalide.\n");
    }

    // Affichage du nombre d'animaux par espèce et par tranche d'âge
    tableau_espece(refuge, taille);
    tableau_age(refuge, taille);

    do{ // Boucle qui vérifie la validité de la réponse de l'utilisateur
        printf("\n\nSouhaitez-vous effectuer une autre action ? (O/N) : ");
        scanf(" %c", &continuer);
        printf("\n");
    }while(continuer != 'O' && continuer != 'o' && continuer != 'N' && continuer != 'n');
}while(continuer == 'O' || continuer == 'o'); // Reprendre tant que l'utilisateur veut continuer

sauvegarder_refuge(refuge, taille, "animaux/refuge.txt");

printf("\nMerci pour votre visite !\n");

// Libération de la mémoire allouée pour chaque animal dans le refuge
for(int i = 0; i < taille; i++){
    free((*(refuge + i))->nom);
    free((*(refuge + i))->espece);
    free((*(refuge + i))->commentaire);
    free(*(refuge + i));// Libération de l'animal
}
free(refuge); // Libération du tableau de refuge

    return 0;
}
