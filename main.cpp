#include <iostream>
#include <string>
using namespace std;

typedef struct snode {
    string mensaje;
    snode *id;
    snode *tiempo;
    snode *prioridad;
} dato;

void asigna(dato &n, dato *id, dato *tiempo, dato *prioridad) {
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
        break;
        case 2:
        break;
        case 3:
        break;
        case 4:
        break;
        // ruben puto
          //hola mundo que chingue su madre el america
          //hola putaaa arremangala arrempujala
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
