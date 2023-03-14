#ifndef _INTERPRETEURAUTOMATE_H
#define _INTERPRETEURAUTOMATE_H

/*
@requires: automate est un path vers un fichier automate
@assigns: nothing
@ensures: Retourne un pointeur vers un array qui contient tous les bytes du fichier
*/
char* lireAutomate(char automate[]);

/*
@requires: automate représente les bytes d'un automate 
@assigns: nothing
@ensures: Retourne nombre d'états de l'automate
*/
int nombreEtat(char automate[]);

/*
@requires: buf est un array représentant les bytes du fichier de l'automate, nbrEtat est le nombre d'états de l'automate
@assigns: nothing
@ensures: Retourne un pointeur vers un array qui contient toutes les valeurs de action(s,c)
*/
int * createActions(char buf[], int nbrEtat);

/*
@requires: buf est un array représentant les bytes du fichier de l'automate, nbrEtat est le nombre d'états de l'automate
@assigns: nothing
@ensures: Retourne un pointeur vers un array qui contient toutes les valeurs du premier élément du tuple réduit(s)
*/
int * createComposante1Reduit(char buf[], int nbrEtat);

/*
@requires: buf est un array représentant les bytes du fichier de l'automate, nbrEtat est le nombre d'états de l'automate
@assigns: nothing
@ensures: Retourne un pointeur vers un array qui contient toutes les valeurs du second élément du tuple réduit(s)
*/
int * createComposante2Reduit(char buf[], int nbrEtat);

/*
@requires: buf est un array représentant les bytes du fichier de l'automate
@assigns: nothing
@ensures: Retourne un pointeur vers un array qui contient tous les s, c, s' tel que décale(s,c)=s'
*/
int *createDecale(char automate[]);

/*
@requires: buf est un array représentant les bytes du fichier de l'automate
@assigns: nothing
@ensures: Retourne un pointeur vers un array qui contient tous les s, A, s' dans cet ordre tel que branchement(s,A)=s'
*/
int * createBranchement(char automate[]);

/*
@requires: A est un caractère du langage ascii, s est un état de l'automate, branchement[] est un array qui contient tous les s, A, s' dans cet ordre tel que branchement(s, A) = s'
@assigns: nothing
@ensures: retourne s' tel quel branchement(s, A) = s'
*/
int branchementValeur(char A, int s, int branchement[]);

/*
@requires: c est un caractère du langage ascii, s est un état de l'automate, decale[] est un array qui contient tous les s, A, s' dans cet ordre tel que branchement(s, A) = s'
@assigns: nothing
@ensures: retourne s' tel quel decale(s, c) = s'
*/
int decaleValeur(char c, int s, int decale[]);

/*
@requires: entree est l'array qui contient l'entree de l'utilisateur; actions est l'array qui contient toutes les valeurs de action(s,c)
                                                                      reduit1 est l'array qui contient la 1e composante de reduit(s) pour tout etat s
                                                                      reduit2 est l'array qui contient la 2e composante de reduit(s) pour tout etat s
                                                                      branchement est l'array qui contient tous les triplets s c s' où branchement(s, c) = s'
                                                                      decale est l'array qui contient tous les triplets s A s' où  decale(s, A) = s'
@assigns: nothing
@ensures: parcours l'entrée suivant l'algorithme donné sur la page du projet, Affiche accepted si le mot fait parti du langage
                                                                              Affiche rejected et l'endroit où l'algo a reperé une erreur qui le mot
                                                                                                                        ne fait pas parti du langage.
*/
void parcours(char entree[], int actions[], int reduit1[], int reduit2[], int branchement[], int decale[]);

#endif