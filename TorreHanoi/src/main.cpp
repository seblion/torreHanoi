#include <iostream>
#include <windows.h>
#include <iomanip>
using namespace std;

#define NIVEL 4
#define DELAY 100000

int TA[NIVEL];
int TB[NIVEL];
int TC[NIVEL];

enum color { azul = 1, verde, turqueza, rojo, rosa, amarillo};
string setColor(color c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
    return "";
}

string drawNivelTorre(const int nroDisk)
{
    string space= string(NIVEL-nroDisk, ' '), disk= string(nroDisk, '-');
    return space + disk + "|"+ disk + space;
}

int getTopDisco(int torre[])
{
    int i=0;
    for (; i < NIVEL; i++)
        if (torre[i]==0)
            break;
    return i;
}

void moveDisco(int torreIni[], int torreFin[])
{
    int ini=getTopDisco(torreIni), fin=getTopDisco(torreFin) ;
  
    if (ini>0)
        ini--;

    torreFin[fin]=torreIni[ini];
    torreIni[ini]=0;
}

bool validarMov(int torreFin[])
{
    int Disco = getTopDisco(torreFin);
    if(Disco<=1)
        return true;
    if (torreFin[Disco-1] < torreFin[Disco-2])
        return true;
    return false;
}

void drawTorres()
{
    cout << "\x1B[2J\x1B[H";
    cout<< setColor(rojo) << "\n\t TORRE DE HANOI" <<endl <<endl << setColor(azul);
    for(int n=NIVEL-1;n>= 0; n--)
        cout<<drawNivelTorre(TA[n]) <<drawNivelTorre(TB[n]) <<drawNivelTorre(TC[n])
            <<endl;
    cout<< setw(5)<<"A"<< setw(9)<<"B"<< setw(9) <<"C"<<endl <<endl;

}

void testShowMatriz()
{
    cout<< endl<<"TA:  ";
    for (auto &&n : TA)
         cout <<n <<", ";
    cout<<"     TOP: " << getTopDisco(TA);
    cout<< endl<<"TB:  ";
    for (auto &&n : TB)
         cout <<n <<", ";
    cout<<"     TOP: " << getTopDisco(TB);
    cout<< endl<<"TC:  ";
    for (auto &&n : TC)
         cout <<n <<", ";
    cout<<"     TOP: " << getTopDisco(TC);
    cout<<endl;
}

bool validarIngreso(string opc)
{
    for (auto &&torre : {"a","b","c"})
        if(opc==torre)
            return true;
    return false;
}

void jugar()
{
    int *TI, *TF;
    string torreIni="", torreFin="";
    int finalizar=0;
    do
    {
        do
        {
            try
            {
                cout<< setColor(turqueza)<<endl << "(x) en ambas entradas para salir" <<endl;;
                cout<< "(?) Sacar disco de TORRE: ";
                getline(cin, torreIni);
                cout<<endl << "(?) Poner disco en TORRE: ";
                getline(cin, torreFin);
                cin.clear();
                if (torreIni =="x" && torreFin =="x")
                {
                    finalizar++;
                    break;
                }
                if(     torreIni != torreFin 
                        && validarIngreso(torreIni) 
                        && validarIngreso(torreFin) )
                    break;
                throw invalid_argument("Opc no valida");
            }
            catch(...)
            {
                torreIni = torreFin = "";
                cout<< setColor(rojo) << "\n    :( Opcion no valida... "; 
            }

        } while(true);

        if (torreIni == "a") TI=TA;
        if (torreIni == "b") TI=TB;
        if (torreIni == "c") TI=TC;  
        
        if (torreFin == "a") TF=TA;
        if (torreFin == "b") TF=TB;
        if (torreFin == "c") TF=TC;

        moveDisco(TI, TF);
        drawTorres();
        if(!validarMov(TF))
        {
            cout <<endl << "movimiento no permitido - perdiste" << endl;
            finalizar++;
        }

        if(getTopDisco(TC)==4)
        {
            cout <<endl << "ganaste!!!" << endl;
            finalizar++;
        }
    } while(finalizar==0);
}

int main()
{
    int disco = NIVEL;
    for (int i = 0; i < NIVEL; i++)
    {
        TA[i] = TB[i] = TC[i] = 0;
        TA[i] = disco--;  
    }

        drawTorres();
        jugar();
    
    cout<< "Se ha terminado el juego" <<endl;
    return 0;
    exit;
}


