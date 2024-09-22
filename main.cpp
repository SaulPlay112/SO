#include <iostream>
#include <string>
using namespace std;

struct dato {
    int id;
    int tiempo;
    int prioridad;
};

void datosGenerales(dato* n, int id, int tiempo, int prioridad) {
    n -> id = id;
    n -> tiempo = tiempo;
    n -> prioridad = prioridad;
}
int main() {
    cout<<"Ingresa una opcion: \n";
    cout<<"Ingresar valores-[1]\n";
    cout<<"FIFO-[2]\n";
    cout<<"SJF-[3]\n";
    cout<<"R.R-[4]\n";
    cout<<"Prioridad-[5]\n";
    cout<<"Salir-[0]\n";
    int opcion;
    cin>>opcion;
    switch (opcion) {
        case 1:
            void agregarDatos();
        break;
        case 2:
            void fifo();
        break;
        case 3:
            void sjf();
        break;
        case 4:
            void r_r();
        break;
        case 5:
            void prioridad();
        break;
    }
    return 0;

}
// funciones para los tiempos

void fifo() {
}

void sjf() {
}

void r_r() {
}

void prioridad() {
}
void agregarDatos() {
    cout<<"FIFO-[1]\n";
    cout<<"SJF-[2]\n";
    cout<<"R.R-[3]\n";
    cout<<"Prioridad-[4]\n";
    int opcion;
    cin>>opcion;
if(opcion==1 || opcion==2 || opcion==3) {
    int a;
    cout<<"Ingresa los procesos: \n";
    cin>>a;

    dato* node = new dato[a];
    for (int i = 0; i < a; i++) {
        int id, tiempo;
        cout<<"Ingresa el id del proceso: "<< i + 1<<": ";
        cin>>id;
        cout<<"Ingresa el tiempo del proceso: "<< i + 1<<": ";
        cin>>tiempo;
        datosGenerales(&node[i], id, tiempo,0);
    }
    cout << "\nProcesos ingresados: \n";
    for (int i = 0; i < a; i++) {
        cout << "ID: " << node[i].id << ", Tiempo: " << node[i].tiempo << endl;
    }
    delete[] node;
}else if (opcion == 4) {
    int a;
    cout<<"Ingresa los procesos: \n";
    cin>>a;

    dato* node = new dato[a];
    for (int i = 0; i < a; i++) {
        int id, tiempo, prioridad;
        cout<<"Ingresa el id del proceso: "<< i + 1<<": ";
        cin>>id;
        cout<<"Ingresa el tiempo del proceso: "<< i + 1<<": ";
        cin>>tiempo;
        cout<<"Ingresa la prioridad de: "<< i + 1<< ": ";
        cin>>prioridad;
        datosGenerales(&node[i], id, tiempo, prioridad);
    }
    cout << "\nProcesos ingresados: \n";
    for (int i = 0; i < a; i++) {
        cout << "ID: " << node[i].id << ", Tiempo: " << node[i].tiempo <<", Prioridad: "<< node[i].prioridad<<endl;
    }
    delete[] node;
}
}
