#include<stdio.h>

void afficheTab4(int (*t)[4]){
    for(int i=0;i<=3;i++){
        printf("\n");
        for(int j=0;j<=3;j++)
            printf(" %d ", t[i][j] );
            }
        printf("\n \n");
}


/*Seconde version de resoudCase: On va calculer le nombres d'indices auxquelles chaque case a acces:
    -un indice est un nombre sur la grille qui se trouve sur la ligne, la colonne ou dans la meme cellule que la case 
    -si 3 indices sont trouves alors nous pourrons dire que le resultat trouve est le bon
    ATTENTION: chacun des indices trouves devra etre differents afin de fournir un resultat valide*/

_Bool resoudCase(int *ValTrouve, int (*t)[4], int ligne, int colonne){
    
    /*On accede d'abord a la position de la case opposee (case en diagonale au sein de la meme cellule)*/
    int positionLigne,positionColonne;

    if(ligne%2==0)
        positionLigne=ligne+1;
    else
        positionLigne=ligne-1;
    
    if(colonne%2==0)
        positionColonne=colonne+1;
    else
        positionColonne=colonne-1;
    
    /*Ce tableau sera rempli au fur et a mesure de la decouverte des indices
        -on testera a la fin les valeurs de ce tableau
        -si une composante du tableau est superieur a 1 le resultat est rejete
        -si la somme de toute les cases est superieur a 3 le resultat est rejete*/
    
    int tableauControlIndice[5]={0,0,0,0,0};
    
    /*On cherche des indices dans la ligne et la colonne de la case*/
    for(int i=0;i<=3;i++){
            
            if(tableauControlIndice[t[ligne][i]]==0)
                tableauControlIndice[t[ligne][i]]++;
            
            if(tableauControlIndice[t[i][colonne]]==0)
                tableauControlIndice[t[i][colonne]]++;
            }
    
    /*on cherche si un indice est present dans la case oppose*/
    if(tableauControlIndice[t[positionLigne][positionColonne]]==0)
        tableauControlIndice[t[positionLigne][positionColonne]]++;
    
    /*on regarde maintenant l'ensemble de nos indices*/
    int indicesDifferents = 0;
    for(int j=1;j<=4;j++){
        if(tableauControlIndice[j]==0)
            *ValTrouve=j;
        indicesDifferents=indicesDifferents+tableauControlIndice[j];
        }
    
    if(indicesDifferents==3)
        return 1;
    else
        return 0;
}

_Bool solveur(int (*t)[4]){
    int nbCaseTrouvees=0,caseDechifree=0;
    
    for(int i=0;i<=3;i++){
        for(int j=0;j<=3;j++){
            
            if(t[i][j]>0)
                nbCaseTrouvees++;
            
            else{
                if(resoudCase(&caseDechifree,t,i,j)){
                    t[i][j]=caseDechifree;
                    nbCaseTrouvees++;
                        
                        }
                    
                /*Test si toutes les cases ont ete trouve a la fin d'un tour, si non on redemarre du debut*/
                
                if(i+j==6){
                    if(nbCaseTrouvees==15)
                        return 1;
                    else{
                        i=0;
                        j=0;
                        nbCaseTrouvees=0;
                            }
                    }
                }
            }
        }
        return 0;
}


int main(){
int t[4][4]={{0,3,4,0},
             {4,0,0,2},
             {1,0,0,3},
             {0,2,1,0}};

afficheTab4(t);

solveur(t);
    afficheTab4(t);

return 0;
}