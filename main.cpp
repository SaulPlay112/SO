#include <iostream>
#include <vector>
#include <algorithm>
#ifdef __MINGW32__
#include <windows.h>
#undef main
#endif

using namespace std;

// Estructura del nodo
struct nodo {
    int id;
    int t; // Tiempo restante
    int p; // Prioridad
    int t_llegada; // Tiempo de llegada
    nodo* siguiente;

    nodo(int proceso, int tiempo, int prioridad)
        : id(proceso), t(tiempo), p(prioridad), t_llegada(0), siguiente(nullptr) {}
};

// Declaración de funciones
void agregarNodo(nodo*& cabeza, int id, int tiempo, int prioridad);
void liberarLista(nodo*& cabeza);
void pedirDatos(vector<vector<int>>& datos);
void transferirDatos(const vector<vector<int>>& datos, nodo*& cabeza);
void fifo(nodo*& cabeza);
void seleccionarSJF(nodo*& cabeza);
void roundRobin(nodo*& cabeza, int quantum);
void ejecutarPorPrioridad(nodo*& cabeza);
double calcularPromedio(int sumaTiempos, int cantidadProcesos);
void menu();

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


void liberarLista(nodo*& cabeza) {
    nodo* temp;
    while (cabeza != nullptr) {
        temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

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

void transferirDatos(const vector<vector<int>>& datos, nodo*& cabeza) {
    for (const auto& a : datos) {
        agregarNodo(cabeza, a[0], a[1], a[2]);
    }
}

double calcularPromedio(int sumaTiempos, int cantidadProcesos) {
    return (cantidadProcesos == 0) ? 0.0 : static_cast<double>(sumaTiempos) / cantidadProcesos;
}

void fifo(nodo*& cabeza) {
    cout << "Estado inicial de los procesos (FIFO):\n";
    

    int tiempoAcumulado = 0;
    int sumaTiempos = 0;
    int nodos = 0;
    double promedio = 0.0;

    while (cabeza != nullptr) {
        tiempoAcumulado += cabeza->t;
        sumaTiempos += tiempoAcumulado;

        cout << "Ejecutando proceso ID: " << cabeza->id
             << " | Tiempo del proceso: " << cabeza->t
             << " | Tiempo acumulado: " << tiempoAcumulado << endl;

        nodo* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;

        nodos++;
    }

    if (nodos > 0) {
        promedio = calcularPromedio(sumaTiempos, nodos);
    }
    cout << "Suma total de tiempos (FIFO): " << sumaTiempos << endl;
    cout << "Promedio de tiempos (FIFO): " << promedio << "\n" << endl;
}

void seleccionarSJF(nodo*& cabeza) {
    cout << "Estado inicial de los procesos (SJF):\n";
    

    int tiempoAcumulado = 0;
    int sumaTiempos = 0;
    int nodos = 0;
    double promedio = 0.0;

    while (cabeza != nullptr) {
        nodo* menorTiempo = cabeza;
        nodo* actual = cabeza->siguiente;
        nodo* anteriorMenor = nullptr;
        nodo* anterior = cabeza;

        // Encontrar el proceso con el menor tiempo
        while (actual != nullptr) {
            if (actual->t < menorTiempo->t) {
                menorTiempo = actual;
                anteriorMenor = anterior;
            }
            anterior = actual;
            actual = actual->siguiente;
        }

        tiempoAcumulado += menorTiempo->t;
        sumaTiempos += tiempoAcumulado;

        cout << "Ejecutando proceso ID: " << menorTiempo->id
             << " | Tiempo del proceso: " << menorTiempo->t
             << " | Tiempo acumulado: " << tiempoAcumulado << endl;

        if (menorTiempo == cabeza) {
            cabeza = cabeza->siguiente;
        } else {
            anteriorMenor->siguiente = menorTiempo->siguiente;
        }
        delete menorTiempo;
        nodos++;
    }

    if (nodos > 0) {
        promedio = calcularPromedio(sumaTiempos, nodos);
    }
    cout << "Suma total de tiempos (SJF): " << sumaTiempos << endl;
    cout << "Promedio de tiempos (SJF): " << promedio << "\n" << endl;
}

void roundRobin(nodo*& cabeza, int quantum) {
    cout << "Estado inicial de los procesos (Round Robin):\n";
    

    int tiempoAcumulado = 0;
    int sumaTiempos = 0;
    int nodos = 0;
    double promedio = 0.0;

    while (cabeza != nullptr) {
        nodo* actual = cabeza;
        while (actual != nullptr) {
            if (actual->t > 0) {
                int tiempoProceso = min(actual->t, quantum);
                actual->t -= tiempoProceso;
                tiempoAcumulado += tiempoProceso;

                cout << "Proceso ID: " << actual->id
                     << " | Tiempo del proceso: " << tiempoProceso
                     << " | Tiempo acumulado: " << tiempoAcumulado
                     << " | Prioridad: " << actual->p << endl;

                if (actual->t == 0) {
                    sumaTiempos += tiempoAcumulado;
                    cout << "Proceso ID: " << actual->id << " completado.\n";
                    nodos++;
                }
            }
            actual = actual->siguiente;
        }

        // Eliminar procesos ya completados
        nodo* temp = cabeza;
        nodo* prev = nullptr;
        while (temp != nullptr) {
            if (temp->t == 0) {
                if (prev == nullptr) {
                    cabeza = temp->siguiente;
                } else {
                    prev->siguiente = temp->siguiente;
                }
                nodo* toDelete = temp;
                temp = temp->siguiente;
                delete toDelete;
            } else {
                prev = temp;
                temp = temp->siguiente;
            }
        }
    }

    if (nodos > 0) {
        promedio = calcularPromedio(sumaTiempos, nodos);
    }
    cout << "Suma total de tiempos (Round Robin): " << sumaTiempos << endl;
    cout << "Promedio de tiempos (Round Robin): " << promedio << "\n" << endl;
}


void ejecutarYRemoverProceso(nodo*& cabeza, nodo* proceso) {
    if (cabeza == nullptr) {
        // Si la lista está vacía, no hacemos nada
        return;
    }

    // Caso especial si el proceso a eliminar es el primero de la lista
    if (cabeza == proceso) {
        nodo* temp = cabeza;
        cabeza = cabeza->siguiente; // Avanzamos la cabeza de la lista
        delete temp; // Liberamos la memoria del nodo eliminado
        return;
    }

    // Buscamos el proceso en la lista
    nodo* actual = cabeza;
    while (actual != nullptr && actual->siguiente != proceso) {
        actual = actual->siguiente;
    }

    if (actual != nullptr) {
        // Si encontramos el proceso, lo eliminamos
        nodo* temp = actual->siguiente;
        actual->siguiente = actual->siguiente->siguiente; // Desconectamos el nodo
        delete temp; // Liberamos la memoria del nodo eliminado
    }
}



void ejecutarPorPrioridad(nodo*& cabeza) {
    int tiempoTotal = 0;
    int tiempoRetornoTotal = 0;
    int numProcesos = 0; // Para contar los procesos y calcular el promedio

    // Se guardará en un vector los tiempos de retorno de cada proceso para mostrarlos después
    vector<int> tiemposDeRetorno;

    while (cabeza != nullptr) {
        nodo** maxPrioridad = &cabeza;
        nodo* temp = cabeza;

        // Buscar el nodo con la mayor prioridad (el número de prioridad más grande)
        while (temp->siguiente != nullptr) {
            if (temp->siguiente->p > (*maxPrioridad)->p) {
                maxPrioridad = &(temp->siguiente);  // Actualizamos a la mayor prioridad
            }
            temp = temp->siguiente;
        }

        nodo* procesoMax = *maxPrioridad;
        *maxPrioridad = procesoMax->siguiente;  // Eliminamos el proceso de la lista

        // Ejecutar el proceso
        cout << "Ejecutando proceso ID: " << procesoMax->id
             << " | con prioridad: " << procesoMax->p
             << " | y Tiempo del proceso: " << procesoMax->t << endl;

        // Actualizar tiempos
        tiempoTotal += procesoMax->t;
        tiemposDeRetorno.push_back(tiempoTotal);  // Guardamos el tiempo de retorno de este proceso
        tiempoRetornoTotal += tiempoTotal;  // Acumulamos el tiempo de retorno total
        numProcesos++;

        // Mostrar el tiempo de retorno de este proceso
        cout << "Tiempo de retorno del proceso " << procesoMax->id << ": " << tiempoTotal << endl;

        delete procesoMax;  // Liberar la memoria del proceso ejecutado
    }

    // Calcular y mostrar el tiempo promedio de retorno si hubo procesos
    if (numProcesos > 0) {
        cout << "Tiempo total de ejecucion: " << tiempoTotal << endl;
        cout << "Tiempo de retorno promedio: " << static_cast<float>(tiempoRetornoTotal) / numProcesos << endl;
    }
}


void menu() {
    int opcion;
    nodo* cabeza = nullptr;
    vector<vector<int>> datos;

    pedirDatos(datos);
    transferirDatos(datos, cabeza);

    do {
        cout << "Seleccione el algoritmo de planificacion:\n";
        cout << "1. FIFO\n";
        cout << "2. SJF\n";
        cout << "3. Round Robin\n";
        cout << "4. Prioridad\n";
        cout << "5. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                fifo(cabeza);
                break;
            case 2:
                seleccionarSJF(cabeza);
                break;
            case 3:
                roundRobin(cabeza, 2);
                break;
            case 4:
                ejecutarPorPrioridad(cabeza);
                break;
            case 5:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción no válida. Intente nuevamente.\n";
        }

        cabeza = nullptr;  // Limpiar la lista para el siguiente algoritmo
        transferirDatos(datos, cabeza);

    } while (opcion != 5);

    liberarLista(cabeza);
}

int main() {
    menu();
    return 0;
}
