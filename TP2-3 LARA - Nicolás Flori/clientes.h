#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

#include "funciones.h"
#include "cuadro.h"

// Declaraciones

const char *PATH_CLIENTE = "clientes.dat";

struct cliente {
    int ID;
    char apellidos[50];
    char nombres[50];
    char mail[50];
    char domicilio[100];
    int CP;
    tm fechanac;
    bool estado;
};

void menuClientes();
void nuevo_cliente();
bool editar_cliente();
void listar_cliente_id();
void listar_todos_clientes();
bool eliminar_clientes();
bool cargar_cliente(cliente *);
bool guardar_cliente(cliente);
int buscar_cliente(int);
cliente leer_cliente(int);
void listar_cliente(cliente);
int cantidad_clientes();
bool sobrescribir_cliente(cliente, int);
bool validar_fecha(cliente *p);
void encabezado_clientes();
void listar_cliente_tabla(cliente);

// Definiciones

void clientes (){

    int opc;
    system("COLOR 4e");

    while(true){
        cls();
        menuClientes();

        cout << "Ingresar opci\242n: ";
        cin >> opc;

        switch(opc){
            case 1:
                nuevo_cliente();
            break;
            case 2:
                editar_cliente();
            break;
            case 3:
                listar_cliente_id();
            break;
            case 4:
                listar_todos_clientes();
            break;
            case 5:
                eliminar_clientes();
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

void menuClientes (){
    cuadro(4, 1, 38, 15);
    gotoxy(16,3);
    cout << "MEN"<<(char)233<<" CLIENTES" << endl;
    gotoxy(8,5);
    cout << "1) Nuevo Cliente" << endl;
    gotoxy(8,6);
    cout << "2) Modificar Cliente" << endl;
    gotoxy(8,7);
    cout << "3) Listar Cliente por ID" << endl;
    gotoxy(8,8);
    cout << "4) Listar todos los Clientes" << endl;
    gotoxy(8,9);
    cout << "5) Eliminar Clientes" << endl;
    gotoxy(8,12);
    cout << "0) Volver al Men\243 Principal" << endl << endl;
    gotoxy(8,14);
}

void nuevo_cliente(){
    cls();
    cliente reg;
    if (cargar_cliente(&reg)){
        if (guardar_cliente(reg)){
            cout << "Cliente cargado correctamente."<<endl;
            system("pause");
        }
        else{
            cout << "No se pudo guardar el cliente en el archivo."<<endl;
            system("pause");
        }
    }
    else{
        cout << "No se pudo cargar el cliente." <<endl;
        system("pause");
        return;
    }
};

bool cargar_cliente(cliente *p){

    p->ID = cantidad_clientes() + 1;

    cout << "Nombres: ";
    cin.ignore();
    cin.getline(p->nombres, 50);

    if (strlen(p->nombres) == 0){
        cout << "El nombre del cliente no puede estar vacio."<<endl;
        return false;
    }

    cout << "Apellidos: ";
    cin.getline(p->apellidos, 50);

    if (strlen(p->apellidos) == 0){
        cout << "El apellido del cliente no puede estar vacio."<<endl;
        return false;
    }

    cout << "Mail: ";
    cin >> p->mail;

    if (strlen(p->mail) == 0){
        cout << "El mail del cliente no puede estar vacio."<<endl;
        return false;
    }

        if(p->mail[0] == '@'){
            cout << "El mail de cliente no puede comenzar con @."<<endl;
            return false;
        }
        else if(p->mail[0] == '.'){
            cout << "El mail de cliente no puede comenzar con un punto."<<endl;
            return false;
        }


    cout << "Domicilio: ";
    cin.ignore();
    cin.getline(p->domicilio, 50);

    if (strlen(p->domicilio) == 0){
        cout << "El domicilio del cliente no puede estar vacio."<<endl;
        return false;
    }

    cout << "CP: ";
    cin  >> p->CP;

    if (p->CP < 1000 || p->CP > 9999){
        cout << "El CP del cliente debe ser un numero entre 1000 y 9999."<<endl;
        return false;
    }

    cout << "Fecha de nacimiento:";
    cout << "Dia: ";
    cin  >> p->fechanac.tm_mday;
    cout << "Mes: ";
    cin  >> p->fechanac.tm_mon;
    cout << "Anio: ";
    cin  >> p->fechanac.tm_year;

    bool fecha;
    fecha = validar_fecha(p);

    if (fecha == false){
        cout << "Fecha Invalida."<<endl;
        return false;
    }

    p->estado = true;

    return true;
}

bool validar_fecha(cliente *p){
    if (p->fechanac.tm_mday < 1 || p->fechanac.tm_mday > 31){
        return false;
    } else if (p->fechanac.tm_mon < 1 || p->fechanac.tm_mon > 12){
        return false;
    } else if (p->fechanac.tm_year < 1930 || p->fechanac.tm_year > 2010){
        return false;
    }
    if ((p->fechanac.tm_mon == 4 || p->fechanac.tm_mon == 6 || p->fechanac.tm_mon == 9 || p->fechanac.tm_mon == 11) && (p->fechanac.tm_mday == 31)){
        return false;
    } else if ((p->fechanac.tm_mon == 2) && (p->fechanac.tm_year % 4 == 0) && p->fechanac.tm_mday > 29){
        return false;
    } else if ((p->fechanac.tm_mon == 2) && (p->fechanac.tm_year % 4 != 0) && p->fechanac.tm_mday > 28){
        return false;
    }
    return true;
}

// Guardar cliente en archivo - Si no existe el archivo se crea
bool guardar_cliente(cliente reg){
    bool guardo;
    FILE *p;
    p = fopen(PATH_CLIENTE, "ab");
    if (p == NULL){
        return false;
    }
    guardo = fwrite(&reg, sizeof(cliente), 1, p);
    fclose(p);
    return guardo;
}

// Solicitar ID y modificar un lplato existente
bool editar_cliente(){

    system("cls");
    int id_buscado, pos;
    cout << "ID del cliente a modificar: ";
    cin >> id_buscado;
    pos = buscar_cliente(id_buscado);

    if (pos >= 0){

        cliente reg = leer_cliente(pos);
        cout << endl;
        listar_cliente(reg);
        cout << endl << "Nuevo Domicilio del Cliente: ";
        cin.ignore();
        cin.getline(reg.domicilio, 50);

        if (strlen(reg.domicilio) == 0){
            cout << "El domicilio del cliente no puede estar vacio."<<endl;
            return false;
        }

        if (sobrescribir_cliente(reg, pos)){
            cout << endl << "Cliente Modificado."<<endl;
            system("pause");
        }
        else {
            cout << "No se modific\242 el cliente."<<endl;
            system("pause");
            return false;
        }
    }
    else {
        cout << "No existe el cliente."<<endl;
        system("pause");
        return false;
    }
}

//Reemplazar registro
bool sobrescribir_cliente(cliente reg, int pos){
    bool escribio;
    FILE *p;
    p = fopen(PATH_CLIENTE, "rb+");
    if (p == NULL){
        return false;
    }
    fseek(p, pos * sizeof(cliente), SEEK_SET);
    escribio = fwrite(&reg, sizeof(cliente), 1, p);
    fclose(p);
    return escribio;
}

// Buscar cliente por ID
int buscar_cliente(int id_buscado){
    cliente reg;
    int i=0;
    FILE *p;
    p = fopen(PATH_CLIENTE, "rb");
    if (p == NULL){
        return -2;
    }
    while (fread(&reg, sizeof(cliente), 1, p)){
        if (reg.ID == id_buscado){
            fclose(p);
            return i;
        }
        i++;
    }
    fclose(p);
    return -1;
}

cliente leer_cliente(int pos){
    cliente reg;
    FILE *p;
    p = fopen(PATH_CLIENTE, "rb");
    if (p == NULL){
        reg.ID = -1;
        return reg;
    }
    fseek(p, pos * sizeof(cliente),SEEK_SET);
    fread(&reg, sizeof(cliente), 1, p);
    fclose(p);
    return reg;
}

// Layout de listado de platos
void listar_cliente_tabla(cliente reg){

    if (reg.estado == true){
        cout << left;
        cout << setw(4)  << reg.ID;
        cout << setw(30)  << reg.nombres;
        cout << setw(25) << reg.apellidos;
        cout << setw(25) << reg.mail;
        cout << setw(25) << reg.domicilio;
        cout << setw(6) << reg.CP;
        cout << setw(2) << reg.fechanac.tm_mday << "/" <<setw(2)<< reg.fechanac.tm_mon << "/" <<setw(4)<< reg.fechanac.tm_year << endl;
    }
}

// Layout de listado de platos
void listar_cliente(cliente reg){

    if (reg.estado == true){
        cout << "ID: " <<reg.ID <<endl;
        cout << "Nombres: "<<reg.nombres<<endl;
        cout << "Apellidos: "<<reg.apellidos<<endl;
        cout << "Mail: " <<reg.mail<<endl;
        cout << "Domicilio: " <<reg.domicilio<<endl;
        cout << "CP: "<<reg.CP <<endl;
        cout << "Fecha de Nacimiento: " <<reg.fechanac.tm_mday << "/" << reg.fechanac.tm_mon << "/" << reg.fechanac.tm_year << endl;
    }
}

void encabezado_clientes(){

    cout << left;
    cout << setw(4) << "ID";
    cout << setw(30) << "Nombres";
    cout << setw(25) << "Apellidos";
    cout << setw(25) << "Mail";
    cout << setw(25) << "Domicilio";
    cout << setw(6) <<  "CP";
    cout << setw(14) << "Fecha de Nacimiento" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------------------"<<endl;

};

void listar_cliente_id(){
system("cls");
    int id_buscado, pos;
    cout << "ID del cliente a buscar: ";
    cin >> id_buscado;
    pos = buscar_cliente(id_buscado);
    if (pos >= 0){
        cliente reg = leer_cliente(pos);

        if (reg.estado == true){
            system("cls");
            cout<<"--------- ID: "<<reg.ID<<" ---------"<<endl;
            listar_cliente(reg);
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

void listar_todos_clientes(){
    cls();
    HWND hwnd = GetConsoleWindow();
    if ( hwnd != NULL){ SetWindowPos(hwnd, 0, 0, 0, 1300, 800, SWP_SHOWWINDOW);}
    cliente reg;
    int cant = cantidad_clientes(), i;
    encabezado_clientes();
    for(i=0; i<cant; i++){
        reg = leer_cliente(i);
        if (reg.estado == true){
            listar_cliente_tabla(reg);
        }
    }
    system("pause");
};

//Obtener cantidad de registros
int cantidad_clientes(){
    int bytes, cr;
    FILE *p;
    p = fopen(PATH_CLIENTE, "rb");
    if (p == NULL){
        return 0;
    }
    fseek(p, 0, SEEK_END);
    bytes = ftell(p);
    cr = bytes / sizeof(cliente);
    fclose(p);
    return cr;
}

bool eliminar_clientes(){
    system("cls");
    int id_buscado, pos;
    char borrar;

    cout << "ID del cliente a eliminar: ";
    cin >> id_buscado;
    pos = buscar_cliente(id_buscado);
    if (pos >= 0){
        cliente reg = leer_cliente(pos);
        cout << endl;
        listar_cliente(reg);
        cout << endl << "Desea eliminar el cliente seleccionado? (S/N): ";
        cin >> borrar;

        if (borrar=='S' or borrar=='s'){
            FILE *p;
            p = fopen(PATH_CLIENTE, "rb+");
            if (p == NULL){
               // return false;
            }
            fread(&reg, sizeof(reg), 1, p);
            while(!feof(p)){
                if(reg.ID == id_buscado){
                    fseek(p, ftell(p) - sizeof(reg), SEEK_SET);
                    reg.estado = false;
                    fwrite(&reg, sizeof(reg), 1, p);
                    break;
                }
                fread(&reg, sizeof(reg), 1, p);
            }
            fclose(p);
        cout << endl;
        cout << "Cliente eliminado." << endl;
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

#endif // CLIENTES_H_INCLUDED
