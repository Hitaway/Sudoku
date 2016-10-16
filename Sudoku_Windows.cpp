#include<iostream>
#include<stdlib.h>
using namespace std;

#define DIM 3
#define TAILLE DIM*DIM

struct Jeu{                     //Structure de Jeu: est composée de deux champs.
    int grille[9][9];           //La grille qui contient les valeurs déjà placé, la valeur est à 0 si la valeur n'est pas connu.
    bool test[9][9][10];        //Les pages de test : test[lig][col][val] est une matrice booléenne,
                                //test[lig][col][val] vaut 1 s'il est possible que la valeur val soit à la position grille[lig][col].
};

typedef struct jeu jeu;

void aff(Jeu J);                //Procédure d'affichage : le paramètre est la structure de jeu.
void placer (Jeu &J, int lig, int col, int val);        //Procédure de placement précise : les paramètres sont la structure de jeu,
                                                        //la ligne, la colonne et la valeur à placer.
void saisie(Jeu &J);            //Procédure de saisi précise : on demande à l'utilsateur ligne, colonne et valeur.
int sizeDeS(string &s);         //Procédure qui compte les caracteres, la fonction vas renvoyer le nombre de caractère contenue dans la chaîne.
void saisie_rap(Jeu &J);        //Procédure de placement rapide : on saisi une chaine de caractère qui
                                //correspond à la grille lu en ligne en mettant 0 lorsque la valeur n'est pas connu.
void init(Jeu &J) ;             //Procédure d'initialisation : le paramètre est la structure de jeu.
bool simplif_lig(Jeu &J);       //Procédure de simplification de ligne qui vas placer une valeur si celle si n'apparait qu'une seul fois par ligne.
bool simplif_col(Jeu &J);       //Procédure de simplification de colonne qui vas placer une valeur si celle si n'apparait qu'une seul fois par colonne.
bool simplif_car(Jeu &J);       //Procédure de simplification de carré qui vas placer une valeur si celle si n'apparait qu'une seul fois par carré.
bool simplif_val(Jeu &J);       //Procédure de simplification de valeur qui vas placer une valeur si il n'y a qu'une valeur possible dans une case.
bool fin(Jeu J);                //Procédure qui test si la grille est remplie.
void finir_grille(Jeu &J);      //Procédure qui vas résoudre toute la grille.
void debloquer_case(Jeu &J);    //Procédure qui vas débloquage une valeur dans la grille.

void aff(Jeu J)                 //Fonction qui vas afficher la grille de jeu
{

    char luc=218,    //left up corner
         ruc=191,    //right up corner
         lbc=192,    //left bottom corner
         rbc=217,    //right bottom corner
         hl=196,     //horizontal line
         vl=179,     //vertical line
         tu=194,     //t up
         tb=193,     //t bottom
         tl=195,     //t left
         tr=180,     //t right
         tm=197,     //t middle
         esp = ' ',  //espace
         tab = '\t'; //tabulation

    cout << tab << tab << luc;
    for(int i=0 ; i<DIM ; i++){
        for(int j=0 ; j<DIM ; j++) cout << hl << hl << hl << hl;
        cout << hl;
    }
    cout << ruc << endl;

    for(int car_lig=0 ; car_lig<DIM ; car_lig++){

        cout << tab << tab << vl;
        for(int i=0 ; i<DIM ; i++){
            cout << luc;
            for(int j=0 ; j<DIM ; j++) cout << hl << hl << hl << tu;
            cout << "\b" << ruc;
        }
        cout << vl << endl;

        for(int car_col=0 ; car_col<DIM ; car_col++){

            cout << tab << tab << vl;
            for(int i=0 ; i<DIM ; i++){
                cout << vl;
                for(int j=0 ; j<DIM ; j++){
                    if(J.grille[DIM*car_lig+car_col][DIM*i+j] == 0) cout << esp << esp << esp << vl;
                    else cout << esp << J.grille[DIM*car_lig+car_col][DIM*i+j] << esp << vl;
                }
            }
            cout << vl <<  endl;

            cout << tab << tab << vl;
            for(int i=0 ; i<DIM ; i++){
                cout << tl;
                for(int j=0 ; j<DIM ; j++) cout << hl << hl << hl << tm;
                cout << "\b" << tr;
            }
            if(car_col < DIM-1) cout << vl << endl;

        }

        cout << "\r";
        cout << tab << tab << vl;
        for(int i=0 ; i<DIM ; i++){
            cout << lbc;
            for(int j=0 ; j<DIM ; j++) cout << hl << hl << hl << tb;
            cout << "\b" << rbc;
        }
        cout << vl << endl;

    }

    cout << tab << tab << lbc;
    for(int i=0 ; i<DIM ; i++){
        for(int j=0 ; j<DIM ; j++) cout << hl << hl << hl << hl;
        cout << hl;
    }
    cout << rbc << endl;
}


void placer (Jeu &J, int lig, int col, int val)
{
    if(J.test[lig][col][val]==0 && !(val==0))           //Test: si la valeur de J.test[lig][col][val]=0 on ne place pas la valeur.
        cout << "Cette valeur ne peut pas etre placer ici" <<endl;
    else
    {
        J.grille[lig][col]=val;

        for (int i=0; i<9; i++)                         //Boucle qui vas initialiser la ligne ou se trouve la valeur a 0.
                J.test[lig][i][val]=0;
        for (int j=0; j<9; j++)                         //Boucle qui vas initialiser la colone ou se trouve la valeur a 0.
                J.test[j][col][val]=0;

        int compt_lig=0;
        int compt_col=0;

        while(!(lig>=compt_lig && lig<compt_lig+3))
            compt_lig+=3;

        while(!(col>=compt_col && col<compt_col+3))
            compt_col+=3;

        for(int i=compt_lig; i<compt_lig+3; i++)        //Boucle qui vas parcourir toute les lignes du carrée.
        {
            for(int j=compt_col; j<compt_col+3; j++)    //Boucle qui vas parcourir toute les collones du carrée.
            {
                J.test[i][j][val]=0;
            }
        }
    }
}

void saisie(Jeu &J)                 //Fonction qui vas demander à l'utilsateur la ligne, la colonne et la valeur.
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
    }while(lig<0 || lig>=9 || col<0 || col>=9 || col<0 || col>=9);  //Executer les instructions (saisie: val, lig, col) tant qu'il sont pas compris entre 0 et 9.
    system("cls");
    placer (J, lig, col, val);                                      //Fonction placer qui vas placer la valeur.
}

int sizeDeS(string &s)               //Fonction qui vas compter le nombre de caractère dans une chaine.
{
    int compteur=0;
    while(s[compteur]!='\0')         //Bancle tant qu'on n'est pas a la fin de la chaine de caractères on incrémente compteur.
        compteur++;
    return compteur;                 //Retourner l'entier compteur.
}

void saisie_rap(Jeu &J)             //Fonction qui vas permettre la saisi d'une chaine de caractère.
{
    string s;
    int val;
    do{
        cout << "Saisir toute les valeurs (81 caracteres): ";
        cin>>s;
        if(!(sizeDeS(s)==81))       //Test qui vas affichier un message si la chaîne de caractères n'est pas égale a 81 caractères.
        {
            cout << "La chaine de caractere que vous avez saisie est pas egale a " << sizeDeS(s) << " caracteres veillez resaisir la chaine" <<endl;
        }
    }while(!(sizeDeS(s)==81));      //Boucle qui vas éxecuter les instructions tant que la chaîne de caractères n'est pas égale à 81 caractères.
    for (int lig=0; lig<9; lig++)
    {
        for (int col=0; col<9; col++)
        {
            val=s[col+9*lig]-'0';
            placer (J, lig, col, val);
            cout<<endl;
        }
    }
}

void init(Jeu &J)               //Fonction qui vas initialiser la grille de jeu a 0.
{
    for (int lig=0; lig<9; lig++)     //Boucle pour initialiser grille jeu a 0.
    {
        for (int col=0; col<9; col++)
            J.grille[lig][col]=0;
    }

    for (int lig=0; lig<9; lig++)     //Boucle pour initialise grille de test a 0.
    {
        for (int col=0; col<9; col++)
        {
            for (int val=0; val<10; val++)
                J.test[lig][col][val]=1;
        }
    }
}

bool simplif_lig(Jeu &J)            //Fonction qui vas simplifier la ligne et qui vas placer une valeur si celle si n'apparait qu'une seul fois par ligne.
{
    int val=0, col=0, lig=0, compteur=0;

    for(int val_temp=0; val_temp<=9; val_temp++)                //Boucle qui vas executer les instruction pour chaque valeur (0 à 9).
    {
        for (int lig_temp=0; lig_temp<9; lig_temp++)            //Boucle qui vas parcourir chaque ligne de la grille de test.
        {
            compteur=0;
            for (int col_temp=0; col_temp<9; col_temp++)        //Boucle qui vas parcourir chaque collone de la grille de test.
            {
                if(J.test[lig_temp][col_temp][val_temp]==1)
                {
                    compteur++;
                    lig=lig_temp;           //lig vas permettre de stocker la valeur de la ligne pour peut être sens reservir dans le prochain test.
                    col=col_temp;           //col vas permettre de stocker la valeur de la collone pour peut être sens reservir dans le prochain test.
                    val=val_temp;           //val vas permettre de stocker la valeur pour peut etre sens reservir dans le prochain test.
                }
            }
        }
        if(compteur==1)                     //Test qui vas éxecuter les instructions si compteur=1 donc si une seul valeur peut être placer sur la ligne.
        {
            cout << "\t La valeur " << val << " ne peut etre placer que a la colonne " << col << " et a la ligne " << lig <<endl;
            placer(J, lig, col, val);
            return true;
        }
    }
    return false;
}

bool simplif_col(Jeu &J)            //Fonction qui vas simplifier la colonne et qui vas placer une valeur si celle si n'apparait qu'une seul fois par colonne.
{
    int val=0, col=0, lig=0, compteur=0;

    for(int val_temp=0; val_temp<=9; val_temp++)                //Boucle qui vas executer les instruction pour chaque valeur (0 à 9).
    {
        for (int col_temp=0; col_temp<9; col_temp++)            //Boucle qui vas parcourir chaque collone de la grille de test.
        {
            compteur=0;
            for (int lig_temp=0; lig_temp<9; lig_temp++)        //Boucle qui vas parcourir chaque ligne de la grille de test.
            {
                if(J.test[lig_temp][col_temp][val_temp]==1)
                {
                    compteur++;
                    lig=lig_temp;           //lig vas permettre de stocker la valeur de la ligne pour peut être sens reservir dans le prochain test.
                    col=col_temp;           //col vas permettre de stocker la valeur de la collone pour peut être sens reservir dans le prochain test.
                    val=val_temp;           //val vas permettre de stocker la valeur pour peut etre sens reservir dans le prochain test.
                }
            }
            if(compteur==1)                 //Test qui vas éxecuter les instructions si compteur=1 donc si une seul valeur peut être placer sur la ligne.
            {
                cout << "\t La valeur " << val << " ne peut etre placer que a la colonne " << col << " et a la ligne " << lig <<endl;
                placer(J, lig, col, val);
                return true;
            }
        }
    }
    return false;
}

bool simplif_car(Jeu &J)                //Fonction qui vas simplifier le carré et qui vas placer une valeur si celle si n'apparait qu'une seul fois par carré.
{
    int val=0, col=0, lig=0, compteur=0;

    for(int val_temp=0; val_temp<=9; val_temp++)                //Boucle qui vas executer les instruction pour chaque valeur (0 à 9).
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
                            lig=3*lig_car+i;                    //lig vas permettre de stocker la valeur de la ligne pour peut être sens reservir dans le prochain test.
                            col=3*col_car+j;                    //col vas permettre de stocker la valeur de la collone pour peut être sens reservir dans le prochain test.
                            val=val_temp;                       //val vas permettre de stocker la valeur pour peut etre sens reservir dans le prochain test.
                        }
                    }
                }
                if(compteur==1)         //Test qui vas éxecuter les instructions si compteur=1 donc si une seul valeur peut être placer sur la ligne.
                {
                    cout << "\t La valeur " << val << " ne peut etre placer que a la colonne " << col << " et a la ligne " << lig <<endl;
                    placer(J, lig, col, val);
                    return true;
                }
            }
        }
    }
    return false;
}

bool simplif_val(Jeu &J)            //Fonction qui vas simplifier la valeur et qui vas placer une valeur si il n'y a qu'une valeur possible dans une case.
{
    int compteur=0, val=0;

    for (int lig=0; lig<9; lig++)                           //Boucle qui vas parcourir chaque ligne de la grille de test.
    {
        for (int col=0; col<9; col++)                       //Boucle qui vas parcourir chaque collone de la grille de test.
        {
            if(J.grille[lig][col]!=0) continue;
            compteur=0;
            for(int val_temp=0; val_temp<=9; val_temp++)    //Boucle qui vas executer les instruction pour chaque valeur (0 à 9).
            {
                if(J.test[lig][col][val_temp]==1)
                {
                    compteur++;
                    val=val_temp;                            //val vas permettre de stocker la valeur pour peut etre sens reservir dans le prochain test.
                }
            }
            if(compteur==1)         //Test qui vas éxecuter les instructions si compteur=1 donc si une seul valeur peut être placer sur la ligne.
            {
                cout << "\t La valeur " << val << " ne peut etre placer que a la colonne " << col << " et a la ligne " << lig <<endl;
                placer(J, lig, col, val);
                return true;
            }
        }
    }
    return false;
}

bool fin(Jeu J)                             //Fonction qui test si la grille est remplie.
{
    bool Fin_jeu=true;

    for (int lig=0; lig<9; lig++)           //Boucle qui vas parcourir chaque ligne de la grille de jeu.
    {
        for (int col=0; col<9; col++)       //Boucle qui vas parcourir chaque collone de la grille de jeu.
        {
            if(J.grille[lig][col]==0)       //Si a l'intersection de col et lig c'est egale a 0 la variable Fin_jeu passe a false.
                Fin_jeu=false;
        }
    }
return (Fin_jeu);                           //Retourner la variable Fin_Jeu (true ou false) pour savoir si le sudoku est finit.
}

void finir_grille(Jeu &J)                   //Fonction qui vas résoudre toute la grille.
{
    system("cls");
    while(fin(J)==false)                    //Boucle qui vas éxecuter les instructions tant que le sudoku n'est pas finit.
    {
        simplif_car(J);
        simplif_lig(J);
        simplif_col(J);
        simplif_val(J);
    }
    cout << "\n Le sudoku a ete resolue voici la liste des different placement fait si dessus" <<endl;
    cout << " Veillez appuyer sur un touche du clavier (une touche de l'alphabet): ";
    char c;
    cin>>c;
    return;
}

void debloquer_case(Jeu &J)                 //Fonction qui vas débloquage une valeur dans la grille.
{
        if (simplif_car(J)==true)
            return;
        else if (simplif_lig(J)==true)
            return;
        else if (simplif_col(J)==true)
            return;
        else if (simplif_val(J)==true)
            return;
        else
            return;
}

int main()       //Fonction principale qui nous serviras pour le choix avec le Menu.
{
    int choix;   //Declarer la valeur choix.
    Jeu J;       //Declarer le type structure.

    cout << "\n\t    ######  ##     ## ########   #######  ##    ## ##     ## \n" <<
              "\t   ##    ## ##     ## ##     ## ##     ## ##   ##  ##     ## \n" <<
              "\t   ##       ##     ## ##     ## ##     ## ##  ##   ##     ## \n" <<
              "\t    ######  ##     ## ##     ## ##     ## #####    ##     ## \n" <<
              "\t         ## ##     ## ##     ## ##     ## ##  ##   ##     ## \n" <<
              "\t   ##    ## ##     ## ##     ## ##     ## ##   ##  ##     ## \n" <<
              "\t    ######   #######  ########   #######  ##    ##  #######  \n" <<endl;
    init(J);     //Fonction d'initialisation qui vas initialiser la grille de jeu et la grille de test.
    aff(J);      //Cette fonction vas afficher la grille de jeu.

    while(fin(J)==false)    //Boucle qui vas s'executer tant que la fonction fin(J) r'envoi false (tant que la grille n'est pas pleine).
    {
        cout << "\t\t\t       MENU:"            <<endl;
        cout << "\t\t\t 1.Reinitialiser grille" <<endl;
        cout << "\t\t\t 2.Saisi precise"        <<endl;
        cout << "\t\t\t 3.Saisi rapide"         <<endl;
        cout << "\t\t\t 4.Resoudre le Sudoku"   <<endl;
        cout << "\t\t\t 5.Debloquer une case"   <<endl;
        cout << "\t\t\t 0.Stop"                 <<endl;
        cout << "\t\t\t      Choix : ";
        cin>>choix;         //saisir choix pour savoir quel action vous voulez éxecuter.

        switch(choix){
            case(0):    return 0;
                    break;
            case(1):    init(J);            //Fonction d'initialisation qui vas initialiser la grille de jeu et la grille de test.
                        system("cls");      //permet de netoyer la console.
                        aff(J);
                    break;
            case(2):    saisie(J);          //Fonction de saisi précise : on demande à l'utilsateur ligne, colonne et valeur.
                        aff(J);
                    break;
            case(3):    saisie_rap(J);      //saisi une chaine de caractère qui correspond à la grille lu en ligne en mettant 0 lorsque la valeur n'est pas connu.
                        system("cls");
                        aff(J);
                    break;
            case(4):    finir_grille(J);    //Fonction qui vas résoudre toute la grille.
                        system("cls");
                        aff(J);
                    break;
            case(5):    system("cls");
                        debloquer_case(J);  //Fonction qui vas débloquage une valeur dans la grille.
                        aff(J);
                    break;
            default:    system("cls");
                        cout << "Veillez faire un choix" <<endl;
                        aff(J);
        }
    }
    cout << "\n\t     #####     #     #####  #     # ####### ######    \n" <<
              "\t    #     #   # #   #     # ##    # #       #     #   \n" <<
              "\t    #        #   #  #       # #   # #       #     #   \n" <<
              "\t    #  #### #     # #  #### #  #  # #####   ######    \n" <<
              "\t    #     # ####### #     # #   # # #       #   #     \n" <<
              "\t    #     # #     # #     # #    ## #       #    #    \n" <<
              "\t     #####  #     #  #####  #     # ####### #     #   \n" <<endl;
return 0;
}
