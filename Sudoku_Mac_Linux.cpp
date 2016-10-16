#include<iostream>
#include<stdlib.h>
using namespace std;

struct Jeu{
    int grille[9][9];
    bool test[9][9][10];
};

typedef struct jeu jeu;

void aff(Jeu J);
void placer (Jeu &J, int lig, int col, int val);
void saisie(Jeu &J);
void saisie_rap(Jeu &J);
void init(Jeu &J) ;
bool simplif_lig(Jeu &J);
bool simplif_col(Jeu &J);
bool simplif_car(Jeu &J);
bool simplif_val(Jeu &J);
bool fin(Jeu J);
void finir_grille(Jeu &J);
void debloquer_case(Jeu &J);

void aff(Jeu J)
{
    cout << "\t\t -------Sudoku--------" <<endl;
    for (int i=0; i<9; i++)
    {
        cout << "\t\t";
        for (int j=0; j<9; j++)
        {
            cout <<  " " <<J.grille[i][j];
            if(j==2 || j==5)
                cout << " |";
        }
        cout <<endl;
        if (!((i+1)%3))
            cout << "\t\t ---------------------" <<endl;
    }
}

void placer (Jeu &J, int lig, int col, int val)
{
    if(J.test[lig][col][val]==0 && !(val==0))
        cout << "Cette valeur ne peut pas etre placer ici" <<endl;
    else
    {
        J.grille[lig][col]=val;
        aff(J);
        for (int i=0; i<9; i++)                 //Boucle qui vas initialiser la ligne ou se trouve la valeur a 0
                J.test[lig][i][val]=0;
        for (int j=0; j<9; j++)                 //Boucle qui vas initialiser la colone ou se trouve la valeur a 0
                J.test[j][col][val]=0;

        int compt_lig=0;                         //Test qui vas initialiser le carre ou se trouve la valeur a 0
        int compt_col=0;

        while(!(lig>=compt_lig && lig<compt_lig+3))
            compt_lig+=3;

        while(!(col>=compt_col && col<compt_col+3))
            compt_col+=3;

        for(int i=compt_lig; i<compt_lig+3; i++)
        {
            for(int j=compt_col; j<compt_col+3; j++)
            {
                J.test[i][j][val]=0;
            }
        }
    }
}

void saisie(Jeu &J)
{
    int lig, col, val;
    do{
        cout << "Saisir la ligne ou le chiffre se trouve: ";
        cin>>lig;
        lig--;
        cout << "Saisir la colonne ou le chiffre se trouve: ";
        cin>>col;
        col--;
        cout << "Saisir le chiffre que vous voulez inserer: ";
        cin>>val;
        cout<<endl;
    }while(lig<0 || lig>=9 || col<0 || col>=9 || col<0 || col>=9);
    placer (J, lig, col, val);
}

int sizeDeS(string &s)
{
    int compteur=0;
    while(s[compteur]!='\0')
        compteur++;
    return compteur;
}

void saisie_rap(Jeu &J)
{
    string s;
    int val;
    do{
        cout << "Saisir toute les valeurs (81 caracteres): ";
        cin>>s;
        if(!(sizeDeS(s)==81))
        {
            cout << "La chaine de caractere que vous avez saisie est pas egale a " << sizeDeS(s) << " caracteres veillez resaisir la chaine" <<endl;
        }
    }while(!(sizeDeS(s)==81));

    for (int lig=0; lig<9; lig++)
    {
        for (int col=0; col<9; col++)
        {
            val=s[col+9*lig]-'0';
            placer (J, lig, col, val);
            cout<<endl;
        }
    }
    aff(J);
}

void init(Jeu &J)               //Fonction qui vas initialiser la grille de jeu a 0
{
    for (int i=0; i<9; i++)     //Boucle pour initialiser grille jeu a 0
    {
        for (int j=0; j<9; j++)
            J.grille[i][j]=0;
    }

    for (int i=0; i<9; i++)     //Boucle pour initialise grille de test a 0
    {
        for (int j=0; j<9; j++)
        {
            for (int h=0; h<10; h++)
                J.test[i][j][h]=1;
        }
    }
}

bool simplif_lig(Jeu &J)
{
    int val=0;
    int col=0;
    int lig=0;
    int compteur=0;

    for(int val_temp=0; val_temp<=9; val_temp++)
    {
        for (int lig_temp=0; lig_temp<9; lig_temp++)
        {
            compteur=0;
            for (int col_temp=0; col_temp<9; col_temp++)
            {
                if(J.test[lig_temp][col_temp][val_temp]==1)
                {
                    compteur++;
                    lig=lig_temp;
                    col=col_temp;
                    val=val_temp;
                }
            }
        }
        if(compteur==1)
        {
            cout << "La valeur " << val << " ne peut etre placer que a la colonne " << col << " et a la ligne " << lig <<endl;
            placer(J, lig, col, val);
            return true;
        }
    }
    return false;
}

bool simplif_col(Jeu &J)
{
    int val=0;
    int col=0;
    int lig=0;
    int compteur=0;

    for(int val_temp=0; val_temp<=9; val_temp++)
    {
        for (int col_temp=0; col_temp<9; col_temp++)
        {
            compteur=0;
            for (int lig_temp=0; lig_temp<9; lig_temp++)
            {
                if(J.test[lig_temp][col_temp][val_temp]==1)
                {
                    compteur++;
                    lig=lig_temp;
                    col=col_temp;
                    val=val_temp;
                }
            }
            if(compteur==1)
            {
                cout << "La valeur " << val << " ne peut etre placer que a la colonne " << col << " et a la ligne " << lig <<endl;
                placer(J, lig, col, val);
                return true;
            }
        }
    }
    return false;
}

bool simplif_car(Jeu &J)
{
    int val=0;
    int col=0;
    int lig=0;
    int compteur=0;

    for(int val_temp=0; val_temp<=9; val_temp++)
    {
        for(int lig_car=0; lig_car<3; lig_car++)
        {
            for(int col_car=0; col_car<3; col_car++)
            {
                compteur=0;
                for(int i=0; i<3; i++)
                {
                    for(int j=0; j<3; j++)
                    {
                        if(J.test[3*lig_car+i][3*col_car+j][val_temp]==1)
                        {
                            compteur++;
                            lig=3*lig_car+i;
                            col=3*col_car+j;
                            val=val_temp;
                        }
                    }
                }
                if(compteur==1)
                {
                    cout << "La valeur " << val << " ne peut etre placer que a la colonne " << col << " et a la ligne " << lig <<endl;
                    placer(J, lig, col, val);
                    return true;
                }
            }
        }
    }
    return false;
}

bool simplif_val(Jeu &J)
{
    int compteur=0;
    int val=0;

    for (int lig=0; lig<9; lig++)
    {
        for (int col=0; col<9; col++)
        {
            if(J.grille[lig][col]!=0) continue;
            compteur=0;
            for(int val_temp=0; val_temp<=9; val_temp++)
            {
                if(J.test[lig][col][val_temp]==1)
                {
                    compteur++;
                    val=val_temp;
                }
            }
            if(compteur==1)
            {
                cout << "La valeur " << val << " ne peut etre placer que a la colonne " << col << " et a la ligne " << lig <<endl;
                placer(J, lig, col, val);
                return true;
            }
        }
    }
    return false;
}

bool fin(Jeu J)
{
    bool Fin_jeu=true;

    for (int i=0; i<9; i++)
    {
        for (int j=0; j<9; j++)
        {
            if(J.grille[i][j]==0)
                Fin_jeu=false;
        }
    }

    for (int i=0; i<9; i++)
    {
        for (int j=0; j<9; j++)
        {
            for (int h=0; h<10; h++)
            {
                if(J.test[i][j][h]==1)
                    Fin_jeu=false;
            }
        }
    }
return (Fin_jeu);
}

void finir_grille(Jeu &J)
{
    while(fin(J)==false)
    {
        simplif_car(J);
        simplif_lig(J);
        simplif_col(J);
        simplif_val(J);
    }
    aff(J);
}

void debloquer_case(Jeu &J)
{
        if (simplif_car(J)==true)
            cout << "car" <<endl;   //Provisoire
        else if (simplif_lig(J)==true)
            cout << "lig" <<endl;   //Provisoire
        else if (simplif_col(J)==true)
            cout << "col" <<endl;   //Provisoire
        else if (simplif_val(J)==true)
            cout << "val" <<endl;   //Provisoire
        else
            cout << "Aucune valeur na plus etre placer" <<endl;
}

int main()
{
    int choix;
    Jeu J;
    init(J);
    cout << "\t  ######  ##     ## ########   #######  ##    ## ##     ## \n" <<
            "\t ##    ## ##     ## ##     ## ##     ## ##   ##  ##     ## \n" <<
            "\t ##       ##     ## ##     ## ##     ## ##  ##   ##     ## \n" <<
            "\t  ######  ##     ## ##     ## ##     ## #####    ##     ## \n" <<
            "\t       ## ##     ## ##     ## ##     ## ##  ##   ##     ## \n" <<
            "\t ##    ## ##     ## ##     ## ##     ## ##   ##  ##     ## \n" <<
            "\t  ######   #######  ########   #######  ##    ##  #######  \n" <<endl;

    while(fin(J)==false)
    {
        cout << "\t\t\t       MENU:"            <<endl;
        cout << "\t\t\t 1.Reinitialiser grille" <<endl;
        cout << "\t\t\t 2.Saisi precise"        <<endl;
        cout << "\t\t\t 3.Saisi rapide"         <<endl;
        cout << "\t\t\t 4.Resoudre le Sudoku"   <<endl;
        cout << "\t\t\t 5.Debloquer une case"   <<endl;
        cout << "\t\t\t 0.Stop"                 <<endl;
        cout << "\t\t\t      Choix : ";
        cin>>choix;

        switch(choix){
            case(0):    return 0;
                    break;
            case(1):    init(J);
                    break;
            case(2):    saisie(J);
                    break;
            case(3):    saisie_rap(J);
                    break;
            case(4):    finir_grille(J);
                    break;
            case(5):    debloquer_case(J);
                    break;
            default:    cout << "Veillez faire un choix" <<endl;
            system("clear");
        }
    }
    aff(J);
    cout << "\t  #####     #     #####  #     # ####### ######  \n" <<
            "\t #     #   # #   #     # ##    # #       #     # \n" <<
            "\t #        #   #  #       # #   # #       #     # \n" <<
            "\t #  #### #     # #  #### #  #  # #####   ######  \n" <<
            "\t #     # ####### #     # #   # # #       #   #   \n" <<
            "\t #     # #     # #     # #    ## #       #    #  \n" <<
            "\t  #####  #     #  #####  #     # ####### #     # \n" <<endl;
return 0;
}
