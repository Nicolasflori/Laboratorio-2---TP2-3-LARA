#ifndef PEDIDOS_H_INCLUDED
#define PEDIDOS_H_INCLUDED

#include "funciones.h"
#include "cuadro.h"
#include "clientes.h"
#include "plato.h"

// Declaraciones

const char *PATH_PEDIDO = "pedidos.dat";

struct pedido {
    int ID;
    int IDCliente;
    int IDPlato;
    int cantidad;
    float precio_unitario;
    tm fecha_pedido;
    float valoracion;
    int estado;
};

void menuPedidos();
void nuevo_pedido();
bool editar_pedido();
void listar_pedido_id();
void listar_todos_pedidos();
bool eliminar_pedidos();
bool cargar_pedido(pedido *p);
bool guardar_pedido(pedido);
int buscar_pedido(int);
pedido leer_pedido(int);
void listar_pedido(pedido);
bool sobrescribir_pedido(pedido, int);
int cantidad_pedidos();
bool validar_fecha(pedido *p);
void listar_pedido_tabla(pedido);
void encabezado_pedidos();

// Definiciones

void pedidos (){

    int opc;
    system("COLOR 2F");

    while(true){
        cls();
        menuPedidos();

        cout << "Ingresar opci\242n: ";
        cin >> opc;

        switch(opc){
            case 1:
                nuevo_pedido();
            break;
            case 2:
                editar_pedido();
            break;
            case 3:
                listar_pedido_id();
            break;
            case 4:
                listar_todos_pedidos();
            break;
            case 5:
                eliminar_pedidos();
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

void menuPedidos (){
    cuadro(4, 1, 38, 15);
    gotoxy(17,3);
    cout << "MEN"<<(char)233<<" PEDIDOS" << endl;
    gotoxy(8,5);
    cout << "1) Nuevo Pedido" << endl;
    gotoxy(8,6);
    cout << "2) Modificar Pedido" << endl;
    gotoxy(8,7);
    cout << "3) Listar Pedido por ID" << endl;
    gotoxy(8,8);
    cout << "4) Listar todos los Pedidos" << endl;
    gotoxy(8,12);
    cout << "0) Volver al Men\243 Principal" << endl << endl;
    gotoxy(8,14);
}

void nuevo_pedido(){
    cls();
    pedido reg;
    if (cargar_pedido(&reg)){
        if (guardar_pedido(reg)){
            cout << "Pedido cargado correctamente."<<endl;
            system("pause");
        }
        else{
            cout << "No se pudo guardar el pedido en el archivo."<<endl;
            system("pause");
        }
    }
    else{
        cout << "No se pudo cargar el pedido." <<endl;
        system("pause");
        return;
    }
};

bool cargar_pedido(pedido *p){

    p->ID = cantidad_pedidos() + 1;

    cout << "ID del Cliente: ";
    cin >> p->IDCliente;

    int idc_buscado;
    idc_buscado = buscar_cliente(p->IDCliente);

    if (idc_buscado < 0){
        cout << "El ID del Cliente no existe.";
        return false;
    }

    cout << "ID del Plato: ";
    cin >> p->IDPlato;

    int idp_buscado;
    idp_buscado = buscar_plato(p->IDPlato);

    if (idp_buscado < 0 ){
        cout << "El ID del Plato no existe.";
        return false;
    }

    cout << "Cantidad del pedido: ";
    cin  >> p->cantidad;

    if (p->cantidad <= 0){
        cout << "La cantidad del pedido no puede ser 0 o negativa.";
        return false;
    }

    int pos = buscar_plato(p->IDPlato);
    if (pos >= 0){
        plato reg = leer_plato(pos);

    p->precio_unitario = reg.valorVenta;
    }

    cout << "Fecha del pedido: ";
    cout << "Dia: ";
    cin  >> p->fecha_pedido.tm_mday;
    cout << "Mes: ";
    cin  >> p->fecha_pedido.tm_mon;
    cout << "Anio: ";
    cin  >> p->fecha_pedido.tm_year;

    bool fecha;
    fecha = validar_fecha(p);

    if (fecha == false){
        cout << "Fecha Invalida."<<endl;
        return false;
    }

    cout << "Valoracion: ";
    cin  >> p->valoracion;

    if (p->valoracion < 0 || p->valoracion > 10){
        cout << "La valoracion debe ser un numero entre 0 y 10.";
        return false;
    }

    p->estado  = 1;

    return true;
}

bool validar_fecha(pedido *p){
    if (p->fecha_pedido.tm_mday < 1 || p->fecha_pedido.tm_mday > 31){
        return false;
    } else if (p->fecha_pedido.tm_mon < 1 || p->fecha_pedido.tm_mon > 12){
        return false;
    } else if (p->fecha_pedido.tm_year < 2000 || p->fecha_pedido.tm_year > 2020){
        return false;
    }
    if ((p->fecha_pedido.tm_mon == 4 || p->fecha_pedido.tm_mon == 6 || p->fecha_pedido.tm_mon == 9 || p->fecha_pedido.tm_mon == 11) && (p->fecha_pedido.tm_mday == 31)){
        return false;
    } else if ((p->fecha_pedido.tm_mon == 2) && (p->fecha_pedido.tm_year % 4 == 0) && p->fecha_pedido.tm_mday > 29){
        return false;
    } else if ((p->fecha_pedido.tm_mon == 2) && (p->fecha_pedido.tm_year % 4 != 0) && p->fecha_pedido.tm_mday > 28){
        return false;
    }
    return true;
}

// Guardar pedido en archivo - Si no existe el archivo se crea
bool guardar_pedido(pedido reg){
    bool guardo;
    FILE *p;
    p = fopen(PATH_PEDIDO, "ab");
    if (p == NULL){
        return false;
    }
    guardo = fwrite(&reg, sizeof(pedido), 1, p);
    fclose(p);
    return guardo;
}

bool editar_pedido(){
    system("cls");
    int id_buscado, pos;
    cout << "ID del pedido a modificar: ";
    cin >> id_buscado;
    pos = buscar_pedido(id_buscado);

    if (pos >= 0){

        pedido reg = leer_pedido(pos);
        cout << endl;
        listar_pedido(reg);
        cout << endl << "Nuevo Estado del Pedido: ";
        cin  >> reg.estado;

        if (reg.estado < 1 || reg.estado > 3){
            cout << "El estado debe ser 1 (en curso), 2 (completado) o 3 (cancelado).";
            return false;
        }

     if (sobrescribir_pedido(reg, pos)){
            cout << endl << "Pedido Modificado."<<endl;
            system("pause");
        }
        else {
            cout << "No se modific\242 el pedido."<<endl;
            system("pause");
            return false;
        }
    }
    else {
        cout << "No existe el pedido."<<endl;
        system("pause");
        return false;
    }
};

//Reemplazar registro
bool sobrescribir_pedido(pedido reg, int pos){
    bool escribio;
    FILE *p;
    p = fopen(PATH_PEDIDO, "rb+");
    if (p == NULL){
        return false;
    }
    fseek(p, pos * sizeof(pedido), SEEK_SET);
    escribio = fwrite(&reg, sizeof(pedido), 1, p);
    fclose(p);
    return escribio;
}

// Buscar pedido por ID
int buscar_pedido(int id_buscado){
    pedido reg;
    int i=0;
    FILE *p;
    p = fopen(PATH_PEDIDO, "rb");
    if (p == NULL){
        return -2;
    }
    while (fread(&reg, sizeof(pedido), 1, p)){
        if (reg.ID == id_buscado){
            fclose(p);
            return i;
        }
        i++;
    }
    fclose(p);
    return -1;
}

pedido leer_pedido(int pos){
    pedido reg;
    FILE *p;
    p = fopen(PATH_PEDIDO, "rb");
    if (p == NULL){
        reg.ID = -1;
        return reg;
    }
    fseek(p, pos * sizeof(pedido),SEEK_SET);
    fread(&reg, sizeof(pedido), 1, p);
    fclose(p);
    return reg;
}

// Layout de listado de pedidos
void listar_pedido(pedido reg){

    if (reg.estado == 2 || reg.estado == 1){

    cout << "ID: " << reg.ID << endl;
    cout << "ID del Cliente: " << reg.IDCliente << endl;
    cout << "ID del Plato: " << reg.IDPlato << endl;
    cout << "Cantidad: " << reg.cantidad << endl;
    cout << "Precio Unitario: " << reg.precio_unitario << endl;
    cout << "Fecha del Pedido: " << reg.fecha_pedido.tm_mday << " / " << reg.fecha_pedido.tm_mon << " / " << reg.fecha_pedido.tm_year << endl;
    cout << "Valoracion: " << reg.valoracion << endl;
    cout << "Estado: " << reg.estado<<endl;
    }
}

void encabezado_pedidos(){

    cout << left;
    cout << setw(4) << "ID";
    cout << setw(16) << "ID del Cliente";
    cout << setw(14) << "ID del Plato";
    cout << setw(10) << "Cantidad";
    cout << setw(17) << "Precio Unitario";
    cout << setw(18) << "Fecha del Pedido";
    cout << setw(12) <<  "Valoracion";
    cout << setw(8) << "Estado" << endl;
    cout << "----------------------------------------------------------------------------------------------------------------------------"<<endl;

};

void listar_pedido_tabla(pedido reg){

    if (reg.estado == 2 || reg.estado == 1){
        cout << left;
        cout << setw(4)  << reg.ID;
        cout << setw(16)  << reg.IDCliente;
        cout << setw(14) << reg.IDPlato;
        cout << setw(10) << reg.cantidad;
        cout << setw(17) << reg.precio_unitario;
        cout << setw(2) << reg.fecha_pedido.tm_mday << "/" <<setw(2)<< reg.fecha_pedido.tm_mon << "/" <<setw(13)<< reg.fecha_pedido.tm_year;
        cout << setw(12) << reg.valoracion;
        cout << setw(8) << reg.estado<<endl;
    }
}

void listar_pedido_id(){
    system("cls");
    int id_buscado, pos;
    cout << "ID del Pedido a buscar: ";
    cin >> id_buscado;
    pos = buscar_pedido(id_buscado);
    if (pos >= 0){
        pedido reg = leer_pedido(pos);

        if (reg.estado == 2 || reg.estado == 1){
            system("cls");
            cout<<"--------- ID: "<<reg.ID<<" ---------"<<endl;
            listar_pedido(reg);
            cout<<"-------------------------"<<endl;
            cout<<endl;
            system("pause");
        }
        else {
            system("cls");
            cout << "No existe el ID buscado" << endl;
            system("pause");
        }
    }
    else{
        system("cls");
        cout << "No existe el ID buscado" << endl;
        system("pause");
    }
};

void listar_todos_pedidos(){
    cls();
    HWND hwnd = GetConsoleWindow();
    if ( hwnd != NULL){ SetWindowPos(hwnd, 0, 0, 0, 1100, 800, SWP_SHOWWINDOW);}
    pedido reg;
    int cant = cantidad_pedidos(), i;
    encabezado_pedidos();
    for(i=0; i<cant; i++){
        reg = leer_pedido(i);
        if (reg.estado == 2 || reg.estado == 1){
            listar_pedido_tabla(reg);
        }
    }
    system("pause");
};

//Obtener cantidad de registros
int cantidad_pedidos(){
    int bytes, cr;
    FILE *p;
    p = fopen(PATH_PEDIDO, "rb");
    if (p == NULL){
        return 0;
    }
    fseek(p, 0, SEEK_END);
    bytes = ftell(p);
    cr = bytes / sizeof(pedido);
    fclose(p);
    return cr;
}


bool eliminar_pedidos(){
    system("cls");
    int id_buscado, pos;
    char borrar;

    cout << "ID del Pedido a eliminar: ";
    cin >> id_buscado;
    pos = buscar_pedido(id_buscado);
    if (pos >= 0){
        pedido reg = leer_pedido(pos);
        cout << endl;
        listar_pedido(reg);
        cout << endl << "Desea eliminar el pedido seleccionado? (S/N): ";
        cin >> borrar;

        if (borrar=='S' or borrar=='s'){
            FILE *p;
            p = fopen(PATH_PEDIDO, "rb+");
            if (p == NULL){
               // return false;
            }
            fread(&reg, sizeof(reg), 1, p);
            while(!feof(p)){
                if(reg.ID == id_buscado){
                    fseek(p, ftell(p) - sizeof(reg), SEEK_SET);
                    reg.estado = 3;
                    fwrite(&reg, sizeof(reg), 1, p);
                    break;
                }
                fread(&reg, sizeof(reg), 1, p);
            }
            fclose(p);
        cout << endl;
        cout << "Pedido eliminado." << endl;
        system("pause");
        return true;
        }

        else if (borrar=='N' or borrar=='n'){

            cout << endl;
            cout << "Acci\242n cancelada." << endl;;
            system("pause");
            return false;
        }
        else {
            error();
        }
    }
    else{
    system("cls");
    cout << "El ID es incorrecto." << endl;;
    system("pause");
    return false;
    }
};


#endif // PEDIDOS_H_INCLUDED
