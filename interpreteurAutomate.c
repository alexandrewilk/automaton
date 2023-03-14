#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"interpreteurAutomate.h"
#include"stack.h"


/*
@requires: automate est un path vers un fichier automate
@assigns: nothing
@ensures: Retourne un pointeur vers un array qui contient tous les bytes du fichier
*/
char* lireAutomate(char automate[]){
    FILE * fPointer;   
    int fLen;
    char* bytes;
    fPointer=fopen(automate, "rb"); // on ouvre le fichier en mode binaire
    fseek(fPointer, 0, SEEK_END);  // on place l'offset à la fin du fichier
    fLen=ftell(fPointer);       // on connait la taille du fichier car on s'est placé à  sa fin
    rewind(fPointer);           // on remet l'offset au début 
    bytes=malloc(fLen* sizeof(char));       // on sait maintenant quelle place réserver pour stocker les bytes du fichiers dans bytes
    fread(bytes, fLen, 1, fPointer);        // et on ecrits ces bytes dans bytes
    fclose(fPointer);
    return bytes;
}

/*
@requires: automate représente les bytes d'un automate 
@assigns: nothing
@ensures: Retourne nombre d'états de l'automate
*/
int nombreEtat(char buf[]){
    int i=2;
    while(buf[i]!=10){
        i+=1;
    }
    int puiss10NbEtat = i -3;//puissance de 10 max du nombre d'états
    double nbrEtatd=0; //On va utiliser pow, on passe par un double que l'on transformera en int à la fin
    int k=2;
    while(buf[k]!=10){// on lit tous les bytes corespondant au nombre
        int a;
        switch(buf[k]){// on fait corespondre le byte encodé en ascii à son chiffre
            case 48:
            {a=0;}
            break;
            case 49:
            {a=1;}
            break;
            case 50:
            {a=2;}
            break;
            case 51:
            {a=3;}
            break;
            case 52:
            {a=4;}
            break;
            case 53:
            {a=5;}
            break;
            case 54:
            {a=6;}
            break;
            case 55:
            {a=7;}
            break;
            case 56:
            {a=8;}
            break;
            case 57:
            {a=9;}
            break;
            default:
            {printf("Nombre d'état n'a pas pu être lu");
            return 0;}
        }
        nbrEtatd+= a * pow(10, puiss10NbEtat);// on calcule le nombre d'état, la puissance de 10 diminuant lorsque l'on se déplace vers la droite
        puiss10NbEtat = puiss10NbEtat -1;
        k+=1;
    }
    int nbrEtat=nbrEtatd;// on retransforme notre double en int
    return nbrEtat;
}

/*
@requires: buf est un array représentant les bytes du fichier de l'automate
@assigns: nothing
@ensures: Retourne un pointeur vers un array qui contient tous les s, c, s' tel que décale(s,c)=s'
*/
int* createDecale(char buf[]){
    int i=0;                        //On se place à la bonne ligne....
    while(buf[i]!=10)
        i+=1;
    i=i+1;
    while(buf[i]!=10)
        i+=1; 
    i=i+1; 
    while(buf[i]!=10)
        i+=1;
    i=i+1;
    while(buf[i]!=10)
        i+=1;
    i=i+1;                  // On est ligne 5 c'est bon
    int tailleDecale=0;
    int indiceDebutLigne=i;
    while(buf[i]!= -83){  // On calcule la taille qui va être prise par l'array représentant décale pour pouvoir faire un malloc
        i+=1;
        tailleDecale+=1;
    }
    int * decale = malloc((tailleDecale+1)*sizeof(int));
    int k=0;
    while(buf[indiceDebutLigne]!=-83){  // On remplit l'array représentant decale par les valeurs lues dans le fichier
        decale[k]=buf[indiceDebutLigne];
        k+=1;
        indiceDebutLigne+=1;
    }
    decale[tailleDecale+1]=-100;   // on met un byte de fin (arbitrairement -100) qui nous sera utile plus tard
    return decale;
}

/*
@requires: buf est un array représentant les bytes du fichier de l'automate
@assigns: nothing
@ensures: Retourne un pointeur vers un array qui contient tous les s, A, s' dans cet ordre tel que branchement(s,A)=s'
*/
int * createBranchement(char buf[]){
    int i=0;                // On se place à la bonne ligne....
    while(buf[i]!=10)
        i+=1;
    i=i+1;
    while(buf[i]!=10)
        i+=1; 
    i=i+1; 
    while(buf[i]!=10)
        i+=1;
    i=i+1;
    while(buf[i]!=10)
        i+=1;
    i=i+1;
    while(buf[i]!=-83)
        i=i+1;
    i=i+3;                  // On est ligne 5, et on a passé les bytes représentant décale : on lit ceux représentant branchement
    int tailleBranchement=0;
    int indiceDebutBranchement=i;
    while(buf[i]!= -83){   // On calcule la taille qui va être prise par l'array représentant branchement pour pouvoir faire un malloc
        i+=1;
        tailleBranchement+=1;
    } 
    int * branchement = malloc((tailleBranchement+1)*sizeof(int));
    int k=0;
    while(buf[indiceDebutBranchement]!=-83){   // On remplit l'array représentant branchement par les valeurs lues dans le fichier
        branchement[k]=buf[indiceDebutBranchement];
        k+=1;
        indiceDebutBranchement+=1;
    }
    branchement[tailleBranchement+1]=-100;
    return branchement;
}
/*
@requires: buf est un array représentant les bytes du fichier de l'automate, nbrEtat est le nombre d'états de l'automate
@assigns: nothing
@ensures: Retourne un pointeur vers un array qui contient toutes les valeurs du second élément du tuple réduit(s)
*/
int * createComposante2Reduit(char buf[], int nbrEtat){
    int i=0;
    int k=0;
    int * composante2Reduit = malloc(nbrEtat*sizeof(int)); // on reserve l'espace nescessaire pour l'array représentant la 2e composante de reduit(s)
     while(buf[i]!=10)       // On se place à la bonne ligne....
        i+=1;
    i=i+1;
    while(buf[i]!=10)
        i+=1; 
    i=i+1; 
    while(buf[i]!=10)
        i+=1;
    i=i+1;
    while(buf[i]!=10){              // on est bien ligne 4, on remplit l'array par ses valeurs lue dans le fichier
        composante2Reduit[k]=buf[i];
        i+=1;
        k+=1;
    }
    return composante2Reduit;
}
/*
@requires: buf est un array représentant les bytes du fichier de l'automate, nbrEtat est le nombre d'états de l'automate
@assigns: nothing
@ensures: Retourne un pointeur vers un array qui contient toutes les valeurs du premier élément du tuple réduit(s)
*/
int * createComposante1Reduit(char buf[], int nbrEtat){
    int i=0;
    int k=0;
    int * composante1Reduit = malloc(nbrEtat*sizeof(int)); // on reserve l'espace nescessaire pour l'array représentant la 1e composante de reduit(s)
    while(buf[i]!=10)               // On se place à la bonne ligne....
        i+=1;
    i=i+1;
    while(buf[i]!=10)
        i+=1; 
    i=i+1; 
    while(buf[i]!=10){  // on est bien ligne 3, on remplit l'array par ses valeurs lue dans le fichier
        composante1Reduit[k]=buf[i];
        k+=1;
        i+=1;
    }
    return composante1Reduit;
}
/*
@requires: buf est un array représentant les bytes du fichier de l'automate, nbrEtat est le nombre d'états de l'automate
@assigns: nothing
@ensures: Retourne un pointeur vers un array qui contient toutes les valeurs de action(s,c)
*/
int * createActions(char buf[], int nbrEtat){
    int * listeAction = malloc(nbrEtat*128*sizeof(int));
    int i=0;
    while(buf[i]!=10){
        i+=1;
    }
    int k=0;
    i=i+1;
    while(buf[i]!=10){
        listeAction[k]=buf[i];
        k+=1;
        i+=1;
    }
    return listeAction;
}
/*
@requires: A est un caractère du langage ascii, s est un état de l'automate, branchement[] est un array qui contient tous les s, A, s' dans cet ordre tel que branchement(s, A) = s'
@assigns: nothing
@ensures: retourne s' tel quel branchement(s, A) = s'
*/
int branchementValeur(char A, int s, int branchement[]){
    int i=0;
    int sprime=-1;
    while(branchement[i]!=-100){   // On parcours tout l'array...
        if(branchement[i]==A && i%3==1 && branchement[i-1]==s) // A la recherche de l'état s et du caractère A
            sprime= branchement[i+1];           // pour attribuer s'
        i+=1;
    }
    if(sprime==-1)
        exit(EXIT_FAILURE);
    return sprime; 
}
/*
@requires: c est un caractère du langage ascii, s est un état de l'automate, decale[] est un array qui contient tous les s, A, s' dans cet ordre tel que branchement(s, A) = s'
@assigns: nothing
@ensures: retourne s' tel quel decale(s, c) = s'
*/
int decaleValeur(char c, int s, int decale[]){
    int i=0;
    int sprime=-1;
   while(decale[i]!=-100){          //On parcourt tout l'array....
        if(decale[i]==c && i%3==1 && decale[i-1]==s)  // a la recherche de l'état s et du caractere c
            sprime=decale[i+1];                 // pour attribuer s'
        i+=1;
    }
    if(sprime ==-1){
        printf("PAS DE TUPLE DECALE(S,C) CORESPONDANT DANS LE FICHIER\n");
        exit(EXIT_FAILURE);}
    return sprime;
}

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
void parcours(char entree[], int actions[], int reduit1[], int reduit2[], int branchement[], int decale[]){
    stack pileEtat = initStack();
    push(&pileEtat, 0);
    int bool =0; int currentAction; int i=0; int currentState; int k; char A;
    while(bool==0){  //On reste dans la boucle tant que le mot n'est pas accepté ou rejeté
        currentState = pileEtat->val;      // On lit l'état courant
        currentAction = actions[currentState* 128 + entree[i]];  // on lit l'action a faire : on connait le caractère courant et l'état courant
        switch(currentAction){    
            case 0 :
            {
                printf("Rejected\n"); 
                printf("Erreur au niveau du caractère %c en position %d de l'input\n ", entree[i], i+1);
                bool = 1;} break;
            case 1 : 
            {printf("Accepted\n"); bool =1;} break;
            case 2:
            {
                push(&pileEtat, decaleValeur(entree[i], currentState, decale)); // on empile l'état donné par decale(s, c)
                i+=1;  // on passe au caractère suivant
            } break;
            case 3:
            {
                for(k=0;k<reduit1[currentState];k++) // on dépile n fois suivant la 1 e composante de reduit(s)
                    pop(&pileEtat);
                A = reduit2[currentState];  
                currentState = pileEtat->val;  // on a le nouvel etat courant 
                push(&pileEtat, branchementValeur(A, currentState, branchement)); // on empile l'état donnée par  la fonction branchement, on reste au même caractère
            } break;
            default:
            {printf ("erreur lors du parcours !\n"); bool =1;}
        }
    }
}



