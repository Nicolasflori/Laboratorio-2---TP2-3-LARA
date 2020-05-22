#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include "funciones.h"
#include "cuadro.h"
#include "plato.h"
#include "clientes.h"
#include "pedidos.h"

// Declaraciones

void menuConfig();
bool crear_copia_seg();
bool restaurar_copia_seg();
bool copia_seg();
bool copia_seg_platos();
bool copia_seg_clientes();
bool copia_seg_pedidos();
bool restaurar_seg();
bool restaurar_seg_platos();
bool restaurar_seg_clientes();
bool restaurar_seg_pedidos();

// Definiciones

void config(){

    int opc;
    system("COLOR 8F");

    while(true){
        cls();
        menuConfig();

        cout << "Ingresar opci\242n: ";
        cin >> opc;

        switch(opc){
            case 1:
                crear_copia_seg();
            break;
            case 2:
                restaurar_copia_seg();
            break;
            case 0:
                return;
            break;
            default:
                error();
            break;
        }
    }
}

void menuConfig (){
    cuadro(4, 1, 38, 15);
    gotoxy(13,3);
    cout << "MEN"<<(char)233<<" CONFIGURACI"<<(char)224<<"N" << endl;
    gotoxy(8,6);
    cout << "1) Realizar Copia de Seguridad" << endl;
    gotoxy(8,8);
    cout << "2) Restaurar Copia de Seguridad" << endl;
    gotoxy(8,12);
    cout << "0) Volver al Men\243 Principal" << endl << endl;
    gotoxy(8,14);
}

bool crear_copia_seg(){
    char confir;
    bool copio;
    system("cls");
    cout << "Esta seguro que desea realizar una copia de seguridad? (S/N): ";
    cin  >> confir;

    if (confir=='S' or confir=='s'){
            copio = copia_seg();

            if (copio == true){
                cout << "Copia de seguridad realizada con exito."<<endl;
                system("pause");
                return true;
            } else {
                cout << "No se pudo realizar la copia de seguridad."<<endl;
                system("pause");
                return true;
            }
        }
        else if (confir=='N' or confir=='n'){
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
};

bool copia_seg(){

    bool copio;

    copio = copia_seg_platos();

    if (copio == true){
        copio = copia_seg_clientes();
        if (copio == true){
            copio = copia_seg_pedidos();
            if (copio == true){
                return copio;
            }
        }
    }else{return copio;}

};

bool copia_seg_platos(){

    int cant_platos;
    bool guardo;

    cant_platos = cantidad_platos();

    plato *vec;
    vec = (plato *) malloc(cant_platos * sizeof(plato));
    if (vec == NULL){
        cout << "No hay memoria para continuar con la ejecucion.";
        system("pause");
        return true;
    }

    FILE *p;
    p = fopen(PATH_PLATO, "rb");
    if (p == NULL){
        free(vec);
        cout << "El archivo de platos no existe.";
        system("pause");
        return true;
    }

    fread(&vec[0], sizeof(plato), cant_platos, p);
    fclose(p);

    FILE *b;
    b = fopen("platos.bkp", "wb");
    guardo = fwrite(&vec[0], sizeof(plato), cant_platos, b);
    fclose(b);
    free(vec);
    return guardo;

};

bool copia_seg_clientes(){

    int cant_clientes;
    bool guardo;

    cant_clientes = cantidad_clientes();

    cliente *vec;
    vec = (cliente *) malloc(cant_clientes * sizeof(cliente));
    if (vec == NULL){
        cout << "No hay memoria para continuar con la ejecucion.";
        system("pause");
        return true;
    }

    FILE *p;
    p = fopen(PATH_CLIENTE, "rb");
    if (p == NULL){
        free(vec);
        cout << "El archivo de clientes no existe.";
        system("pause");
        return true;
    }

    fread(&vec[0], sizeof(cliente), cant_clientes, p);
    fclose(p);

    FILE *b;
    b = fopen("clientes.bkp", "wb");
    guardo = fwrite(&vec[0], sizeof(cliente), cant_clientes, b);
    fclose(b);
    free(vec);
    return guardo;
};

bool copia_seg_pedidos(){

    int cant_pedidos;
    bool guardo;

    cant_pedidos = cantidad_pedidos();

    pedido *vec;
    vec = (pedido *) malloc(cant_pedidos * sizeof(pedido));
    if (vec == NULL){
        cout << "No hay memoria para continuar con la ejecucion.";
        system("pause");
        return true;
    }

    FILE *p;
    p = fopen(PATH_PEDIDO, "rb");
    if (p == NULL){
        free(vec);
        cout << "El archivo de pedidos no existe.";
        system("pause");
        return true;
    }

    fread(&vec[0], sizeof(pedido), cant_pedidos, p);
    fclose(p);

    FILE *b;
    b = fopen("pedidos.bkp", "wb");
    guardo = fwrite(&vec[0], sizeof(pedido), cant_pedidos, b);
    fclose(b);
    free(vec);
    return guardo;
};

bool restaurar_copia_seg(){
    char confir;
    bool restaurar;
    system("cls");
    cout << "Esta seguro que desea restaurar la copia de seguridad? (S/N): ";
    cin  >> confir;

    if (confir=='S' or confir=='s'){
            restaurar = restaurar_seg();

            if (restaurar == true){
                cout << "Copia de seguridad restaurada con exito."<<endl;
                system("pause");
                return true;
            } else {
                cout << "No se pudo restaurar la copia de seguridad."<<endl;
                system("pause");
                return true;
            }
        }
        else if (confir=='N' or confir=='n'){
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
};

bool restaurar_seg(){

    bool restauro;

    restauro = copia_seg_platos();

    if (restauro == true){
        restauro = copia_seg_clientes();
        if (restauro == true){
            restauro = copia_seg_pedidos();
            if (restauro == true){
                return restauro;
            }
        }
    }else{return restauro;}

};

bool restaurar_seg_platos(){

    int cant_platos;
    bool guardo;

    cant_platos = cantidad_platos();

    plato *vec;
    vec = (plato *) malloc(cant_platos * sizeof(plato));
    if (vec == NULL){
        cout << "No hay memoria para continuar con la ejecucion.";
        system("pause");
        return true;
    }

    FILE *p;
    p = fopen("platos.bkp", "rb");
    if (p == NULL){
        free(vec);
        cout << "El archivo de restauracion de platos no existe.";
        system("pause");
        return true;
    }

    fread(&vec[0], sizeof(plato), cant_platos, p);
    fclose(p);

    FILE *b;
    b = fopen(PATH_PLATO, "wb");
    guardo = fwrite(&vec[0], sizeof(plato), cant_platos, b);
    fclose(b);
    free(vec);
    return guardo;

};
bool restaurar_seg_clientes(){

    int cant_clientes;
    bool guardo;

    cant_clientes = cantidad_clientes();

    cliente *vec;
    vec = (cliente *) malloc(cant_clientes * sizeof(cliente));
    if (vec == NULL){
        cout << "No hay memoria para continuar con la ejecucion.";
        system("pause");
        return true;
    }

    FILE *p;
    p = fopen("clientes.bkp", "rb");
    if (p == NULL){
        free(vec);
        cout << "El archivo de restauracion clientes no existe.";
        system("pause");
        return true;
    }

    fread(&vec[0], sizeof(cliente), cant_clientes, p);
    fclose(p);

    FILE *b;
    b = fopen(PATH_CLIENTE, "wb");
    guardo = fwrite(&vec[0], sizeof(cliente), cant_clientes, b);
    fclose(b);
    free(vec);
    return guardo;
};
bool restaurar_seg_pedidos(){

    int cant_pedidos;
    bool guardo;

    cant_pedidos = cantidad_pedidos();

    pedido *vec;
    vec = (pedido *) malloc(cant_pedidos * sizeof(pedido));
    if (vec == NULL){
        cout << "No hay memoria para continuar con la ejecucion.";
        system("pause");
        return true;
    }

    FILE *p;
    p = fopen("pedidos.bkp", "rb");
    if (p == NULL){
        free(vec);
        cout << "El archivo de restauracion pedidos no existe.";
        system("pause");
        return true;
    }

    fread(&vec[0], sizeof(pedido), cant_pedidos, p);
    fclose(p);

    FILE *b;
    b = fopen(PATH_PEDIDO, "wb");
    guardo = fwrite(&vec[0], sizeof(pedido), cant_pedidos, b);
    fclose(b);
    free(vec);
    return guardo;
};

#endif // CONFIG_H_INCLUDED
