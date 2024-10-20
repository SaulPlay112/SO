#include <iostream>
#include <vector>
using namespace std;

// Estructura del nodo
struct nodo {
    int id;
    int t;
    int p;
    nodo* siguiente;

    nodo(int proceso, int tiempo, int prioridad) : id(proceso), t(tiempo), p(prioridad), siguiente(nullptr) {}
};

void ejecutarYRemoverProceso(nodo*& cabeza, nodo* proceso);
nodo* seleccionarMayorPrioridad(nodo* cabeza);

// Función para agregar nodos a la lista
void agregarnodo(nodo*& cabeza, int id, int tiempo, int prioridad) {
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
        cout << "ID: " << temp->id << ", Tiempo: " << temp->t << ", Prioridad: " << temp->p << "\n" << endl;
        temp = temp->siguiente;
    }
}

// Función para pedir datos
void pedirdatos(vector<vector<int>>& datos) {
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

// Función para transferir datos del vector a la lista enlazada
void tranferirDatos(vector<vector<int>>& datos, nodo*& cabeza) {
    for (auto& a : datos) {
        agregarnodo(cabeza, a[0], a[1], a[2]);
    }
}

// Función para calcular el promedio de los tiempos
double calcularPromedio(nodo* cabeza, int& sumaTiempos) {
    int contador = 0;
    sumaTiempos = 0;
    nodo* actual = cabeza;

    while (actual != nullptr) {
        sumaTiempos += actual->t;
        contador++;
        actual = actual->siguiente;
    }

    if (contador == 0) return 0.0;
    return static_cast<double>(sumaTiempos) / contador;
}

// Función FIFO
void fifo(nodo* cabeza) {
    nodo* actual = cabeza;
    int tiempoTotal = 0;
    int sumaTiempos = 0;
    double promedio = calcularPromedio(cabeza, sumaTiempos);

    if (actual == nullptr) {
        cout << "La lista está vacía." << endl;
        return;
    }

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

// Función SJF (Shortest Job First)
nodo* seleccionarSJF(nodo* cabeza) {
    if (cabeza == nullptr) return nullptr;

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

// Función Round Robin
void roundRobin(nodo*& cabeza) {
    int sumaTiempos = 0;
    double promedio = calcularPromedio(cabeza, sumaTiempos);
    int quantum = static_cast<int>(promedio);  // El quantum es el promedio de los tiempos

    cout << "Quantum calculado: " << quantum << endl;

    while (cabeza != nullptr) {
        nodo* actual = cabeza;
        while (actual != nullptr) {
            if (actual->t > quantum) {
                cout << "Ejecutando proceso ID: " << actual->id << " con quantum de " << quantum << endl;
                actual->t -= quantum;
            } else {
                cout << "Ejecutando proceso ID: " << actual->id << " - Tiempo restante: " << actual->t << endl;
                nodo* siguiente = actual->siguiente;
                ejecutarYRemoverProceso(cabeza, actual);
                actual = siguiente;
                continue;
            }
            actual = actual->siguiente;
        }
    }

    cout << "Suma total de tiempos (Round Robin): " << sumaTiempos << endl;
    cout << "Promedio de tiempos (Round Robin): " << promedio << "\n" << endl;
}

// Función de prioridad
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

// Funciones ya existentes para ejecutar y remover
nodo* seleccionarMayorPrioridad(nodo* cabeza) {
    if (cabeza == nullptr) return nullptr;

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

void ejecutarYRemoverProceso(nodo*& cabeza, nodo* proceso) {
    if (cabeza == nullptr || proceso == nullptr) return;

    if (cabeza == proceso) {
        cabeza = cabeza->siguiente;
    } else {
        nodo* actual = cabeza;
        while (actual->siguiente != proceso) {
            actual = actual->siguiente;
        }
        actual->siguiente = proceso->siguiente;
    }

    cout << "Ejecutando proceso ID: " << proceso->id << " con prioridad " << proceso->p << endl;
    delete proceso;
}

// Main
int main() {
    nodo* cabeza = nullptr;
    vector<vector<int>> datos;
    int opcion;

    do {
        cout << "Ingresa una opcion: \n";
        cout << "Ingresar valores-[1]\n";
        cout << "FIFO-[2]\n";
        cout << "SJF-[3]\n";
        cout << "Round Robin-[4]\n";
        cout << "Prioridad-[5]\n";
        cout << "Salir-[0]\n";
        cin >> opcion;

        switch (opcion) {
            case 1:
                pedirdatos(datos);
            break;
            case 2:
                tranferirDatos(datos, cabeza);
            fifo(cabeza);
            break;
            case 3:
                tranferirDatos(datos, cabeza);
            ejecutarSJF(cabeza);
            break;
            case 4:
                tranferirDatos(datos, cabeza);
            roundRobin(cabeza);
            break;
            case 5:
                tranferirDatos(datos, cabeza);
            ejecutarPorPrioridad(cabeza);
            break;
            case 0:
                cout << "Saliendo del programa." << endl;
            break;
            default:
                cout << "Opción no válida. Inténtalo de nuevo." << endl;
            break;
        }
    } while (opcion != 0);
}
