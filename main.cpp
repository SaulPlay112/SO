#include <iostream>
#include <vector>
#include <algorithm> // Para std::min
using namespace std;

// Estructura del nodo
struct nodo {
    int id;
    int t; // Tiempo restante
    int p; // Prioridad
    int t_llegada; // Tiempo de llegada para Round Robin
    nodo* siguiente;

    nodo(int proceso, int tiempo, int prioridad)
        : id(proceso), t(tiempo), p(prioridad), t_llegada(0), siguiente(nullptr) {}
};

// Declaración de funciones
void ejecutarYRemoverProceso(nodo*& cabeza, nodo* proceso);
nodo* seleccionarMayorPrioridad(nodo* cabeza);

// Función para agregar nodos a la lista
void agregarNodo(nodo*& cabeza, int id, int tiempo, int prioridad) {
    nodo* nuevoNodo = new nodo(id, tiempo, prioridad);

    if (cabeza == nullptr) {
        cabeza = nuevoNodo;
    } else {
        nodo* temp = cabeza;
        while (temp->siguiente != nullptr) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevoNodo;
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
        cout << "La lista está vacía." << endl;
        return;
    }

    nodo* temp = cabeza;
    while (temp != nullptr) {
        cout << "ID: " << temp->id << ", Tiempo: " << temp->t << ", Prioridad: " << temp->p << "\n";
        temp = temp->siguiente;
    }
    cout << endl;
}

// Función para pedir datos
void pedirDatos(vector<vector<int>>& datos) {
    int cantidadNodos;
    cout << "Ingrese la cantidad de nodos: ";
    cin >> cantidadNodos;

    for (int i = 0; i < cantidadNodos; ++i) {
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

// Función para transferir datos del vector a la lista enlazada
void transferirDatos(const vector<vector<int>>& datos, nodo*& cabeza) {
    for (const auto& a : datos) {
        agregarNodo(cabeza, a[0], a[1], a[2]);
    }
}

// Función para calcular el promedio de tiempos
double calcularPromedio(nodo* cabeza, int& sumaTiempos) {
    int contador = 0;
    sumaTiempos = 0;
    nodo* actual = cabeza;

    while (actual != nullptr) {
        sumaTiempos += actual->t;
        contador++;
        actual = actual->siguiente;
    }

    return (contador == 0) ? 0.0 : static_cast<double>(sumaTiempos) / contador;
}

// Implementación de FIFO
void fifo(nodo* cabeza) {
    nodo* actual = cabeza;
    int tiempoTotal = 0;
    int sumaTiempos = 0;
    double promedio = calcularPromedio(cabeza, sumaTiempos);

    while (actual != nullptr) {
        tiempoTotal += actual->t;
        cout << "Proceso ID: " << actual->id
             << " - Tiempo del proceso: " << actual->t
             << " - Tiempo acumulado: " << tiempoTotal << endl;
        actual = actual->siguiente;
    }

    cout << "Suma total de tiempos: " << sumaTiempos << endl;
    cout << "Promedio de tiempos: " << promedio << "\n" << endl;
}

// Implementación de SJF
nodo* seleccionarSJF(nodo* cabeza) {
    nodo* menorTiempo = cabeza;
    nodo* actual = cabeza->siguiente;

    while (actual != nullptr) {
        if (actual->t < menorTiempo->t) {
            menorTiempo = actual;
        }
        actual = actual->siguiente;
    }
    return menorTiempo;
}

void ejecutarSJF(nodo*& cabeza) {
    int sumaTiempos = 0;
    double promedio = calcularPromedio(cabeza, sumaTiempos);

    while (cabeza != nullptr) {
        nodo* proceso = seleccionarSJF(cabeza);
        ejecutarYRemoverProceso(cabeza, proceso);
    }

    cout << "Suma total de tiempos (SJF): " << sumaTiempos << endl;
    cout << "Promedio de tiempos (SJF): " << promedio << "\n" << endl;
}

// Implementación de Round Robin
void roundRobin(nodo*& cabeza) {
    const int quantum = 7;
    int tiempoTotal = 0;

    cout << "Quantum definido: " << quantum << endl;

    nodo* actual = cabeza;
    while (cabeza != nullptr) {
        actual = cabeza;
        while (actual != nullptr) {
            if (actual->t > 0) {
                int tiempoEjecutado = min(quantum, actual->t);
                actual->t -= tiempoEjecutado;
                tiempoTotal += tiempoEjecutado;

                if (actual->t == 0) {
                    cout << "Proceso ID: " << actual->id << " ha terminado. Tiempo total: " << tiempoTotal << endl;
                }
            }
            actual = actual->siguiente;
        }
    }

    liberarLista(cabeza);
}

// Implementación de prioridad
nodo* seleccionarMayorPrioridad(nodo* cabeza) {
    nodo* mayorPrioridad = cabeza;
    nodo* actual = cabeza->siguiente;

    while (actual != nullptr) {
        if (actual->p < mayorPrioridad->p) {
            mayorPrioridad = actual;
        }
        actual = actual->siguiente;
    }
    return mayorPrioridad;
}

void ejecutarPorPrioridad(nodo*& cabeza) {
    int sumaTiempos = 0;
    double promedio = calcularPromedio(cabeza, sumaTiempos);

    while (cabeza != nullptr) {
        nodo* proceso = seleccionarMayorPrioridad(cabeza);
        ejecutarYRemoverProceso(cabeza, proceso);
    }

    cout << "Suma total de tiempos (Prioridad): " << sumaTiempos << endl;
    cout << "Promedio de tiempos (Prioridad): " << promedio << "\n" << endl;
}

void ejecutarYRemoverProceso(nodo*& cabeza, nodo* proceso) {
    if (cabeza == proceso) {
        cabeza = cabeza->siguiente;
    } else {
        nodo* actual = cabeza;
        while (actual->siguiente != proceso) {
            actual = actual->siguiente;
        }
        actual->siguiente = proceso->siguiente;
    }

    cout << "Ejecutando proceso ID: " << proceso->id << endl;
    delete proceso;
}

// Main
int main() {
    nodo* cabeza = nullptr;
    vector<vector<int>> datos;
    int opcion;

    do {
        cout << "Ingrese una opción:\n";
        cout << "1. Ingresar valores\n";
        cout << "2. FIFO\n";
        cout << "3. SJF\n";
        cout << "4. Round Robin\n";
        cout << "5. Prioridad\n";
        cout << "0. Salir\n";
        cin >> opcion;

        switch (opcion) {
            case 1:
                pedirDatos(datos);
                break;
            case 2:
                transferirDatos(datos, cabeza);
                fifo(cabeza);
                liberarLista(cabeza);
                break;
            case 3:
                transferirDatos(datos, cabeza);
                ejecutarSJF(cabeza);
                liberarLista(cabeza);
                break;
            case 4:
                transferirDatos(datos, cabeza);
                roundRobin(cabeza);
                break;
            case 5:
                transferirDatos(datos, cabeza);
                ejecutarPorPrioridad(cabeza);
                liberarLista(cabeza);
                break;
            case 0:
                cout << "Saliendo del programa.\n";
                break;
            default:
                cout << "Opción no válida.\n";
        }
    } while (opcion != 0);

    return 0;
}
