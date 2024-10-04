#include <iostream>
using namespace std;

// SAUL- Cree la estructura de la lista enlazada con lo que vamos a ocupar...  id (proceso), tiempo(tiempo del proceso), prioridad(prioridad del proceso)
struct nodo {
    int id;
    int t;
    int p;
    nodo* siguiente;

    // SAUL- cree el constructor para utilizar la lista enlazada para los procesos
    nodo(int proceso, int tiempo , int prioridad) : id(proceso), t(tiempo), p(prioridad), siguiente(nullptr) {}
};


