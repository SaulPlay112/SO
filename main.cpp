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
// Ruben - creo agregar nodos
void agregarnodo(nodo*& cabeza, int id, int tiempo, int prioridad) {
    nodo* nuevoNodo = new nodo(id, tiempo, prioridad);  // Crear nuevo nodo dinámico

    if (cabeza == nullptr) {
        cabeza = nuevoNodo;  // Si la lista está vacía, el nuevo nodo es la cabeza
    } else {
        nodo* temp = cabeza;
        while (temp->siguiente != nullptr) {  // Recorre hasta el último nodo
            temp = temp->siguiente;
        }
        temp->siguiente = nuevoNodo;  // Conecta el nuevo nodo al final de la lista
    }
}
// ruben - creo liberar lista
void liberarLista(nodo*& cabeza) {
    nodo* temp;
    while (cabeza != nullptr) {
        temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;  // Libera la memoria del nodo actual
    }
}
// Ruben - creo imprimir lista
void imprimirLista(nodo* cabeza) {
    if (cabeza == nullptr) {
        cout << "La lista está vacía." << endl;
        return;
    }

    nodo* temp = cabeza;
    while (temp != nullptr) {
        cout << "ID: " << temp->id << ", Tiempo: " << temp->t << ", Prioridad: " << temp->p << endl;
        temp = temp->siguiente;
    }
}
// Ruben - creo pedirdatos
void pedirdatos() {
    nodo* cabeza = nullptr;
    int cantidadNodos;

    cout << "Ingrese la cantidad de nodos: ";
    cin >> cantidadNodos;

    for (int i = 0; i < cantidadNodos; i++) {
        int id, tiempo, prioridad;

        cout << "Ingrese los datos para el nodo " << (i + 1) << ":\n";
        cout << "ID: ";
        cin >> id;
        cout << "Tiempo: ";
        cin >> tiempo;
        cout << "Prioridad: ";
        cin >> prioridad;

        agregarnodo(cabeza, id, tiempo, prioridad);


    }
    imprimirLista(cabeza);

    liberarLista(cabeza);
}

// Ruben - creo el main
int main() {
    int opcion;
    do{
        cout<<"Ingresa una opcion: \n";
        cout<<"Ingresar valores-[1]\n";
        cout<<"FIFO-[2]\n";
        cout<<"SJF-[3]\n";
        cout<<"R.R-[4]\n";
        cout<<"Prioridad-[5]\n";
        cout<<"Salir-[0]\n";
        cin>>opcion;
        switch (opcion) {
            case 1:
                pedirdatos();
            break;
            case 2:

                break;
            case 3:

                break;
            case 4:

                break;
            case 5:

                break;
        }
    }while (opcion != 0);

    return 0;
}

