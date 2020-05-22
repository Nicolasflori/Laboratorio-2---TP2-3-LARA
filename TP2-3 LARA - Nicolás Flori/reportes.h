#ifndef REPORTES_H_INCLUDED
#define REPORTES_H_INCLUDED

#include "funciones.h"
#include "cuadro.h"

// Declaraciones

// Definiciones

void reportes(){
    system("COLOR D0");
    gotoxy(1,1);
    cuadro (1,1,64,6);
    gotoxy(22,3);
    cout<<"FUNCI"<<(char)224<<"N EN DESARROLLO."<<endl;
    gotoxy(5,5);
    cout<<"Presione cualquier tecla para volver al men\243 principal."<<endl;
    cout<<endl<<endl;
    system("pause");
}

#endif // REPORTES_H_INCLUDED
