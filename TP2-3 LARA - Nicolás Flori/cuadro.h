#ifndef CUADRO_H_INCLUDED
#define CUADRO_H_INCLUDED

#include <windows.h>
#include <stdio.h>

void gotoxy(short x, short y){
    HANDLE h;
    h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(h,pos);
}

void cuadro(short X, short Y, short ancho, short alto){
    int i, j;
    for(i=X; i<=X+ancho; i++){
        for(j=Y; j<=Y+alto; j++){
            gotoxy(i, j);

            if(i==X && j==Y){
                cout<<(char)201;}

            else if(i==X+ancho && j==Y){
                cout<<(char)187;}

            else if(i==X && j==Y+alto){
                cout<<(char)200;}

            else if(i==X+ancho && j==Y+alto){
                cout<<(char)188;}

            else if(j==Y || j==Y+alto){
                cout<<(char)205;}

            else if(i==X || i==X+ancho){
                cout<<(char)186;}
            }
        }
    }

#endif // CUADRO_H_INCLUDED
