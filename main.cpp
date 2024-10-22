#include <iostream>
#include <vector>
using namespace std;

// Estructura del nodo
struct nodo {
    int id;
    int t; // Tiempo restante
    int p; // Prioridad
    int t_llegada; // Para manejar el tiempo de llegada en Round Robin
    nodo* siguiente;

    nodo(int proceso, int tiempo, int prioridad) : id(proceso), t(tiempo), p(prioridad), t_llegada(0), siguiente(nullptr) {}
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
    int quantum = 7; // Definir un quantum fijo o calcularlo
    int tiempoTotal = 0;
    int tiemposRetorno[100] = {0};  // Para almacenar los tiempos de retorno de cada proceso
    int tiemposEspera[100] = {0};   // Para almacenar los tiempos de espera
    int procesos = 0;

    cout << "Quantum definido: " << quantum << endl;

    nodo* actual = cabeza;
    while (cabeza != nullptr) {
        actual = cabeza;
        while (actual != nullptr) {
            if (actual->t > 0) {
                int tiempoEjecutado = min(quantum, actual->t);
                tiemposEspera[actual->id] += tiempoTotal - actual->t_llegada; // Tiempo de espera

                actual->t -= tiempoEjecutado;
                tiempoTotal += tiempoEjecutado;
                actual->t_llegada = tiempoTotal;  // Actualizamos la llegada para la próxima ronda

                // Si el proceso ha terminado, calculamos el tiempo de retorno
                if (actual->t == 0) {
                    tiemposRetorno[actual->id] = tiempoTotal;
                    cout << "Proceso ID: " << actual->id << " ha terminado. Tiempo de retorno: " << tiemposRetorno[actual->id] << endl;
                    procesos++;
                }
            }
            actual = actual->siguiente;
        }
    }

    // Calcular el promedio de tiempos de retorno y espera
    int sumaTiemposEspera = 0;
    int sumaTiemposRetorno = 0;

    for (int i = 0; i < 100; i++) {
        if (tiemposRetorno[i] > 0) {
            sumaTiemposRetorno += tiemposRetorno[i];
            sumaTiemposEspera += tiemposEspera[i];
        }
    }

    cout << "Tiempo promedio de espera (Round Robin): " << (double)sumaTiemposEspera / procesos << endl;
    cout << "Tiempo promedio de retorno (Round Robin): " << (double)sumaTiemposRetorno / procesos << "\n" << endl;

    // Liberar la lista después de terminar el Round Robin
    liberarLista(cabeza);
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
                liberarLista(cabeza);  // Liberar después de FIFO
            break;
            case 3:
                tranferirDatos(datos, cabeza);
                ejecutarSJF(cabeza);
                liberarLista(cabeza);  // Liberar después de SJF
            break;
            case 4:
                tranferirDatos(datos, cabeza);
                roundRobin(cabeza);  // La función ya incluye la liberación de la lista
            break;
            case 5:
                tranferirDatos(datos, cabeza);
                ejecutarPorPrioridad(cabeza);
                liberarLista(cabeza);  // Liberar después de Prioridad
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
