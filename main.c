#include<stdio.h>
#include<stdlib.h>
#include "stack.h"
#include "interpreteurAutomate.h"

int main(int argc, char * argv[]){
    if(argc!=2){
        fprintf(stderr, "Utilisation: ./NOM_EXECUTABLE NOM_AUTOMATE.aut \n");
        exit(EXIT_FAILURE);
    }
    char * bytesAutomate = lireAutomate(argv[1]);       // On attribue les arrays corespondant aux fonctions actions(s,c), reduit(s), branchement(s, A), decale(s, c) 
    int nbEtat = nombreEtat(bytesAutomate);
    int *actions=createActions(bytesAutomate, nbEtat);
    int *reduit1=createComposante1Reduit(bytesAutomate, nbEtat);int *reduit2 = createComposante2Reduit(bytesAutomate, nbEtat);
    int *branchement=createBranchement(bytesAutomate);
    int *decale=createDecale(bytesAutomate);
    printf("fichier %s correctement lu, tapez vos entrées (/q pour quitter) \n", argv[1]);
    char input[256];
    char *buf=malloc(256*sizeof(char));
    int i;
    while(input[0]!= '/'&& input[1]!='q'){     // on lit chaque ligne entrée par l'utilisateur
        for(i=0; i<256; i++)               // ici j'initialise juste mon entrée car jai eu des soucis quand je ne le faisais pas
            input[i]=0;
        fgets(input, 256, stdin);   //je lis la ligne en entrée
        sscanf(input, "%s", buf);    // je l'écris dans input au format string
        parcours(input, actions, reduit1, reduit2, branchement, decale);  // on parcours l'entrée selon l'algorithme
    }
    free(buf);
    return 0;
}


