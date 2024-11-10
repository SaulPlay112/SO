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
void mostrarLista(nodo* cabeza);
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

void mostrarLista(nodo* cabeza) {
    nodo* temp = cabeza;
    while (temp != nullptr) {
        cout << temp->id << " | " << temp->t;
        if (temp->siguiente != nullptr) {
            cout << "  <-  ";
        }
        temp = temp->siguiente;
    }
    cout << endl;
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
    mostrarLista(cabeza);

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
    mostrarLista(cabeza);

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
    mostrarLista(cabeza);

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
nodo* seleccionarMayorPrioridad(nodo* cabeza) {
    nodo* mayorPrioridad = cabeza; // Inicialmente, seleccionamos el primer nodo
    nodo* actual = cabeza->siguiente; // Empezamos a recorrer la lista desde el siguiente nodo

    while (actual != nullptr) {
        // Comparamos las prioridades (menor valor de prioridad es mayor urgencia)
        if (actual->p < mayorPrioridad->p) {
            mayorPrioridad = actual;
        }
        actual = actual->siguiente; // Avanzamos al siguiente nodo
    }

    return mayorPrioridad;
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
    int tiempoTotal = 0;       // Variable para el tiempo total acumulado
    int sumaTiempos = 0;       // Variable para la suma total de los tiempos
    int nodos = 0;             // Variable para contar el número de procesos
    double promedio = 0.0;     // Promedio de tiempos

    // Guardamos los tiempos de retorno de cada proceso
    vector<int> tiemposRetorno;

    // Iteramos mientras haya procesos
    while (cabeza != nullptr) {
        nodo* mayorPrioridad = seleccionarMayorPrioridad(cabeza); // Seleccionar el proceso con la mayor prioridad (menor valor de `p`)

        // Guardamos el tiempo de ejecución de este proceso
        int tiempoProceso = mayorPrioridad->t;

        // Acumulamos el tiempo total hasta el final de este proceso
        tiempoTotal += tiempoProceso;

        // Guardamos el tiempo de retorno para el proceso
        tiemposRetorno.push_back(tiempoTotal);

        // Mostrar estado actual del proceso en ejecución
        cout << "Ejecutando proceso ID: " << mayorPrioridad->id
             << " | Tiempo de proceso: " << mayorPrioridad->t
             << " | Tiempo acumulado: " << tiempoTotal
             << " | Prioridad: " << mayorPrioridad->p << endl;

        // Eliminar el proceso de la lista después de ejecutarlo
        ejecutarYRemoverProceso(cabeza, mayorPrioridad);
        nodos++; // Incrementar el contador de procesos
    }

    // Sumar los tiempos de retorno para calcular el promedio
    for (int tiempo : tiemposRetorno) {
        sumaTiempos += tiempo;
    }

    if (nodos > 0) {
        promedio = calcularPromedio(sumaTiempos, nodos); // Calcular el promedio de tiempos
    }

    // Imprimir resultados finales
    cout << "Tiempos de retorno: ";
    for (int tiempo : tiemposRetorno) {
        cout << tiempo << " ";
    }
    cout << endl;

    cout << "Suma total de tiempos (Prioridad): " << sumaTiempos << endl;
    cout << "Promedio de tiempos (Prioridad): " << promedio << "\n" << endl;
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
