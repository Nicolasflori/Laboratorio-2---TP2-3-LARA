#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include "cuadro.h"

// Definiciones

// Layout Menú Principal
void menuPrincipal(){
    gotoxy(16,3);
    cout << "MEN"<<(char)233<<" PRINCIPAL" << endl;
    gotoxy(8,5);
    cout << "1) Platos" << endl;
    gotoxy(8,6);
    cout << "2) Clientes" << endl;
    gotoxy(8,7);
    cout << "3) Pedidos" << endl;
    gotoxy(8,8);
    cout << "4) Reportes" << endl;
    gotoxy(8,9);
    cout << "5) Configuraci\242n" << endl;
    gotoxy(8,11);
    cout << "0) Salir del programa" << endl << endl;
    gotoxy(8,14);
}

//Pantalla de despedida
void pantalla_fin(){
    gotoxy(1,1);
    cuadro (1,1,32,4);
    gotoxy(6,3);
    cout<<"Gracias por usar LARA!."<<endl;
    cout<<endl;
}

// Desactivar Cursor de la Consola para la presentación
void ShowConsoleCursor(bool showFlag){
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CURSORINFO;

    GetConsoleCursorInfo(out, &CURSORINFO);
    CURSORINFO.bVisible = showFlag;
    SetConsoleCursorInfo(out, &CURSORINFO);
}

// Pantalla de bienvenida
void presentacion(){
    gotoxy(28,4);
    cout << "Bienvenido!";
    gotoxy(10,6);
    cout <<" _____         __      _______         __      \n" ;
    gotoxy(10,7);
    cout <<"|_   _|       /  \\    |_   __ \\       /  \\     \n" ;
    gotoxy(10,8);
    cout <<"  | |        / /\\ \\     | |__) |     / /\\ \\    \n" ;
    gotoxy(10,9);
    cout <<"  | |   _   / ____ \\    |  __ /     / ____ \\   \n" ;
    gotoxy(10,10);
    cout <<" _| |__/ |_/ /    \\ \\_ _| |  \\ \\_ _/ /    \\ \\_ \n" ;
    gotoxy(10,11);
    cout <<"|________|____|  |____|____| |___|____|  |____|\n" ;
    gotoxy(14,14);
    cout <<"Presione cualquier tecla para comenzar"<<endl;
    cout <<endl<<endl<<endl<<endl;

    ShowConsoleCursor(false);
    system("pause");
    system ("cls");
}

// PopUp Opción Incorrecta
void error (){
    system("cls");
    cout<<"Opci\242n incorrecta."<<endl;
    system("pause");
    system("cls");
}

// Salir del programa
bool fsalir (bool continuar){

char salir;

 cout << "Salir del programa? (S/N):";
 cin  >> salir;

    if (salir=='S' or salir=='s'){
            return false;
        }
        else if (salir=='N' or salir=='n'){
            return true;
            system("cls");
            }
            else {
                system("cls");
                cout<<"Opci\242n incorrecta."<<endl;
                cout<<endl;
                system("pause");
                return true;
                }
            }

#endif // FUNCIONES_H_INCLUDED
