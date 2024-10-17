#include <iostream>
#include <vector>
using namespace std;

// Estructura del nodo
struct nodo {
    int id;
    int t;
    int p;
    nodo* siguiente;

    nodo(int proceso, int tiempo , int prioridad) : id(proceso), t(tiempo), p(prioridad), siguiente(nullptr) {}
};

// Función para agregar nodos a la lista
void agregarnodo(nodo*& cabeza, int id, int tiempo, int prioridad) {
    nodo* nuevoNodo = new nodo(id, tiempo, prioridad);

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

// Función para liberar la lista
void liberarLista(nodo*& cabeza) {
    nodo* temp;
    while (cabeza != nullptr) {
        temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

// Función para imprimir la lista
void imprimirLista(nodo* cabeza) {
    if (cabeza == nullptr) {
        cout << "La lista está vacia." << endl;
        return;
    }

    nodo* temp = cabeza;
    while (temp != nullptr) {
        cout << "ID: " << temp->id << ", Tiempo: " << temp->t << ", Prioridad: " << temp->p << "\n "<<endl;
        temp = temp->siguiente;
    }
}

// Función para pedir datos
void pedirdatos(vector<vector<int>> & datos) {  // Se pasa cabeza por referencia
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
        datos.push_back({id, tiempo, prioridad});
    }
}

// funcion para pasar los datos del vector a una lista enlazada
void tranferirDatos(vector<vector<int>> & datos, nodo*& cabeza) {
    for (auto& a : datos) {
        agregarnodo(cabeza,a[0],a[1],a[2]);
    }
}

// Función FIFO
void fifo(nodo* cabeza) {
    nodo* actual = cabeza;  // Puntero para recorrer la lista
    int tiempoTotal = 0;  // Variable para almacenar el tiempo total
    int contador = 0;  // Contador de procesos

    if (actual == nullptr) {
        cout << "La lista esta vacia." << endl;
        return;
    }

    // Recorremos la lista enlazada sumando los tiempos
    while (actual != nullptr) {
        tiempoTotal += actual->t;  // Sumar el tiempo del proceso actual
        contador++;  // Contar cada proceso
        cout << "Proceso ID: " << actual->id
             << " - Tiempo del proceso: " << actual->t
             << " - Tiempo acumulado: " << tiempoTotal << endl;
        actual = actual->siguiente;  // Avanzar al siguiente nodo
    }

    // Calcular y mostrar el promedio
    if (contador > 0) {
        double promedio = static_cast<double>(tiempoTotal) / contador;
        cout << "Tiempo total de ejecucion: " << tiempoTotal << endl;
        cout << "Promedio del tiempo total de ejecucion: " << promedio <<"\n" <<endl;
    } else {
        cout << "No hay procesos en la lista." << endl;
    }
}


// Main
int main() {
    nodo* cabeza = nullptr;  // Inicializar la lista de procesos
    vector<vector<int>> datos;
    int opcion;
    do {
        cout << "Ingresa una opcion: \n";
        cout << "Ingresar valores-[1]\n";
        cout << "FIFO-[2]\n";
        cout << "SJF-[3]\n";
        cout << "R.R-[4]\n";
        cout << "Prioridad-[5]\n";
        cout << "Salir-[0]\n";
        cin >> opcion;

        switch (opcion) {
            case 1:
                pedirdatos(datos);  // Pasar la lista por referencia
                break;
            case 2:
                tranferirDatos(datos, cabeza);
                fifo(cabeza);  // Pasar la lista a la función FIFO
                break;
            case 3:
                // Implementar SJF
                break;
            case 4:
                // Implementar Round Robin
                break;
            case 5:
                // Implementar Prioridad
                break;
            case 0:
                cout << "Saliendo del programa." << endl;
                break;
            default:
                cout << "Opción no válida. Inténtelo de nuevo." << endl;
        }
    } while (opcion != 0);

    liberarLista(cabeza);  // Liberar la memoria al finalizar
    return 0;
}
