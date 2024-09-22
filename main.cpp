#include <iostream>
#include <string>
using namespace std;

typedef struct snode {
    snode *id;
    snode *tiempo;
    snode *prioridad;
} dato;

void asigna(dato&n,dato *id, dato *tiempo, dato *prioridad) {
    n.id = id;
    n.tiempo = tiempo;
    n.prioridad = prioridad;
}
int main() {
    cout<<"Ingresa una opcion: \n";
    cout<<"FIFO-[1]\n";
    cout<<"SJF-[2]\n";
    cout<<"R.R-[3]\n";
    cout<<"Prioridad-[4]\n";
    cout<<"Salir-[0]\n";
    int opcion;
    cin>>opcion;
    switch (opcion) {
        case 1:
            void fifo();
        break;
        case 2:
            void sjf();
        break;
        case 3:
            void r_r();
        break;
        case 4:
            void prioridad();
        break;
    }
    return 0;

}
// funciones para los tiempos

void fifo() {
    cout<< " Cuantos procesos quieres ingresar:"<< endl;
    cin>>*id;
    dato node[a];
    for (int i = 1; i < a; i++) {

cout << "Dime el tiempo del"<<i<<" :"<<endl;



    }
}
void sjf() {

}
void r_r() {

}
void prioridad() {

}
