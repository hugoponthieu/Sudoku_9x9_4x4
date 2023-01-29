#include<stdio.h>

void afficheSudoku(int (*sudoku)[9]){
    printf("\n");
    for(int i=0;i<=8;i++){
        printf("\n");
        for(int j=0;j<=8;j++)
            printf(" %d ",sudoku[i][j]);}
    printf("\n");
}

void afficheTab(int (*tab)){
    printf("\n");
    for(int i=0;i<=9;i++)
        printf(" %d ",tab[i]);
    printf("\n");
}
//Dans resoudCase on teste la position de la ligne puis dans testColonne on test la position de la colonne
//cette fonction prend en entree tableauValeursTrouvees et incremente
void nombreDansLaMemeCellule(int (*sudoku)[9],int *tableauValeursTrouvees,int ligne,int colonne){
    //dans une cellule on attribue a chaque case un coef 
    int position=ligne%3-(colonne%3)*3;
   // printf(" %d ",position);
    //bcp trop loin pour etre clair a l'ecrit
    int a, b ;
    switch(position){
        case 0: a=1;b=1;break;
        case -6: a=1;b=-1;break;
        case -4: a=-1;b=-1;break;
        case 2: a=-1;b=1;break;
        case -3: a=1;b=1;break;
        case -1: a=-1;b=1;break;
        case 1: a=1;b=1;break;
        case -5: a=-1;b=1;break;
    }

   // printf("ab");
    switch(position){
        case -4:
        case 2 :
        case -6 :
        case 0 :
            for(int i=ligne+a;i<=ligne+2*a;i++)
                for(int j=colonne+b;j<=colonne+2*b;j++)
                    if(tableauValeursTrouvees[sudoku[i][j]]==0){
                        tableauValeursTrouvees[sudoku[i][j]]++;
                        }
                     //   printf("case");
                        break;
        case -3 :
        case -1 :
        for(int k=ligne+a;k<=ligne+2*a;k++)
                for(int l=colonne+b;l<=colonne+2*b;l+=2)
                    if(tableauValeursTrouvees[sudoku[k][l]]==0){
                            tableauValeursTrouvees[sudoku[k][l]]++;}
                            break;

        case -5 :
        case 1 :
        for(int k=colonne+a;k<=colonne+2*a;k++)
                for(int l=ligne+b;l<=ligne+2*b;l+=2)
                    if(tableauValeursTrouvees[sudoku[l][k]]==0){
                            tableauValeursTrouvees[sudoku[l][k]]++;}
                            break;                    

        case -2 :  
        for(int m=ligne-1;m<=ligne+1;m=m+2)
                for(int l=colonne-1;l<=colonne+1;l=l+2){
                  //  printf("case [%d][%d]",m,l);
                         if(tableauValeursTrouvees[sudoku[m][l]]==0){
                            tableauValeursTrouvees[sudoku[m][l]]++;}
                                }
                            
                            break;

    }
}

_Bool resoudCase(int (*sudoku)[9],int ligne, int colonne,int *caseTrouvee){
    //On creerd'abord le tableau de liste des reponses
    int tableauValeursTrouvees[10]={0};
    //Seconde etape trouver les indices dans les colonnes et les lignes
    for(int i=0;i<=8;i++){
        if(tableauValeursTrouvees[sudoku[ligne][i]]==0)
            tableauValeursTrouvees[sudoku[ligne][i]]++;
        if(tableauValeursTrouvees[sudoku[i][colonne]]==0)
            tableauValeursTrouvees[sudoku[i][colonne]]++;
    }
    nombreDansLaMemeCellule(sudoku,tableauValeursTrouvees,ligne,colonne);
    //afficheTab(tableauValeursTrouvees);
    int nbCaseTrouvee=0;

    for(int i=1;i<=9;i++)
        {nbCaseTrouvee=nbCaseTrouvee+tableauValeursTrouvees[i];
            if(tableauValeursTrouvees[i]==0)
                *caseTrouvee=i;}
    //printf("%d ",nbCaseTrouvee);
    if(nbCaseTrouvee==8){
        return 1;
    }
    else{
        return 0;
    }
}

//Chaque case peut etre resolu il faut maintenant appliquer note algo a chaque case 

void solveur(int (*sudoku)[9]){
    int caseTrouvee,nombreDeCaseTrouvee=0;
    
    for(int i=0;i<=8;i++)
        for(int j=0;j<=8;j++){
            //printf(" %d ",nombreDeCaseTrouvee);
            if(sudoku[i][j]>0)
                nombreDeCaseTrouvee++;
            else{
            if(resoudCase(sudoku,i,j,&caseTrouvee))
                {//printf("%d ",caseTrouvee);
                //afficheSudoku(sudoku);
                sudoku[i][j]=caseTrouvee;
                nombreDeCaseTrouvee++;
                //printf(" case[%d][%d] ",i,j);
                }
            //int k=i+j;
            //printf(" %d i=%d j=%d\n ",k,i,j);
            if(i+j==16){printf("a");
                if(nombreDeCaseTrouvee==80){
                    printf("%d ",nombreDeCaseTrouvee);
                    break;}
                else{printf("a");
                    i=0;
                    j=0;
                    nombreDeCaseTrouvee=0;
                    }
                }
            }
                
        }
    }


int main(){
    int sudoku[9][9]={
            {5,0,0,0,0,2,6,3,8},
            {6,3,2,4,0,9,0,0,0},
            {0,0,0,6,3,0,2,4,0},
            {0,5,0,0,0,7,4,0,3},
            {0,0,0,0,0,6,8,5,1},
            {2,0,0,0,0,0,9,0,0},
            {9,0,0,5,6,3,1,0,0},
            {3,0,0,0,9,0,0,0,0},
            {4,0,0,8,0,1,0,0,7}};
    afficheSudoku(sudoku); 
    solveur(sudoku);
    afficheSudoku(sudoku);
    return 0;

}