/*
    Hola bienvenido a este programa!
    En este podran ver un ejemplo de la estructura de datos llamada Hash Table.

    Este programa acepta un ID (su ID asignado por el INTEC) y ubique al estudiante en el índice
    correspondiente. La estructura para este caso debe ser:
    
    La tabla hash está limitada a MAX (pero en este caso, estará limitada al número de 
    estudiantes de su sección de Estructuras de Datos y Algoritmos), por
    lo que solo aceptará los ID distintos de su clase y asignará la posición correspondiente.

    Integrantes:
        1116783-Whisman Lorenzo
        1116842-Jose Reyes
        1105307-Jose Sol
        1114056-Jose Florentino
        1116176-Manuel Guzman
        1115997-Winston Pichardo
        1087257-Jorge Jimenez

        Fecha: 2/10/2023

*/

#include <iostream>
#include <string>
#include <limits>
#include <vector>

using namespace std;

struct Estudiante {
    int id;
    string nombre;
    string cod_carrera;
    float indice_acad;
};

struct NodoEstudiante {
    Estudiante estudiante;
    NodoEstudiante* siguiente;
};

vector<NodoEstudiante*> tablaHash;

int funcionHash(int id) {
    return id % tablaHash.size();
}

void insertarEstudiante(int id) {
    int indice = funcionHash(id);

    NodoEstudiante* nuevoEstudiante = new NodoEstudiante;
    nuevoEstudiante->estudiante.id = id;

    cout << "NOMBRE: ";
    cin.ignore();
    getline(cin, nuevoEstudiante->estudiante.nombre);
    cout << "CARRERA: ";
    cin >> nuevoEstudiante->estudiante.cod_carrera;
    cout << "INDICE ACADEMICO: ";
    cin >> nuevoEstudiante->estudiante.indice_acad;

    nuevoEstudiante->siguiente = nullptr;

    if (tablaHash[indice] == nullptr) {
        tablaHash[indice] = nuevoEstudiante;
    } else {
        NodoEstudiante* actual = tablaHash[indice];
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoEstudiante;
    }
}

bool hayRegistros() {
    for (size_t i = 0; i < tablaHash.size(); i++) {
        if (tablaHash[i] != nullptr) {
            return true;
        }
    }
    return false;
}

void mostrarRegistros() {
    if (!hayRegistros()) {
        cout << "No hay registros para mostrar." << endl;
        return;
    }

    for (size_t i = 0; i < tablaHash.size(); i++) {
        NodoEstudiante* actual = tablaHash[i];
        while (actual != nullptr) {
            cout << "ID: " << actual->estudiante.id << endl;
            cout << "NOMBRE: " << actual->estudiante.nombre << endl;
            cout << "CARRERA: " << actual->estudiante.cod_carrera << endl;
            cout << "INDICE ACADEMICO: " << actual->estudiante.indice_acad << endl;
            cout << "-------------------------" << endl;
            actual = actual->siguiente;
        }
    }
}

void mostrarRegistroPorID(int id) {
    int indice = funcionHash(id);
    NodoEstudiante* actual = tablaHash[indice];
    
    while (actual != nullptr) {
        if (actual->estudiante.id == id) {
            cout << "ID: " << actual->estudiante.id << endl;
            cout << "NOMBRE: " << actual->estudiante.nombre << endl;
            cout << "CARRERA: " << actual->estudiante.cod_carrera << endl;
            cout << "INDICE ACADEMICO: " << actual->estudiante.indice_acad << endl;
            return;
        }
        actual = actual->siguiente;
    }

    cout << "El ID no fue encontrado." << endl;
}

void eliminarRegistroPorID(int id) {
    int indice = funcionHash(id);
    NodoEstudiante* actual = tablaHash[indice];
    NodoEstudiante* anterior = nullptr;

    while (actual != nullptr) {
        if (actual->estudiante.id == id) {
            if (anterior == nullptr) {
                tablaHash[indice] = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }
            delete actual;
            cout << "El registro con ID " << id << " ha sido eliminado." << endl;
            return;
        }
        anterior = actual;
        actual = actual->siguiente;
    }

    cout << "El ID no fue encontrado." << endl;
}

void eliminarTodosLosRegistros() {
    for (size_t i = 0; i < tablaHash.size(); i++) {
        NodoEstudiante* actual = tablaHash[i];
        while (actual != nullptr) {
            NodoEstudiante* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
        tablaHash[i] = nullptr;
    }
    cout << "Todos los registros han sido eliminados." << endl;
}

bool continuar() {
    cout << "¿Desea continuar? (S/N)\n";
    string ans;
    cin >> ans;
    for (char& c : ans) {
        c = tolower(c);
    }
    if (ans != "s" && ans != "n") {
        do {
            cout << "Opción inválida.\n";
            cin >> ans;
        } while (ans != "s" && ans != "n");
    }
    return ans == "s";
}

int obtenerIntValido() {
    int number;
    while (!(cin >> number)) {
        cout << "\nEntrada inválida: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return number;
}

void cls() {
    if (continuar()) {
        cout << "Entendido" << endl;
        system("cls");
    }
    else {
        cin.ignore();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        exit(0);
    }
}

int main() {
    cout << "Ingrese la cantidad de estudiantes en su sección: ";
    int numEstudiantes = obtenerIntValido();
    tablaHash.resize(numEstudiantes, nullptr);

    int opcion;
    do {
        cout << "Menu:" << endl;
        cout << "1. Insertar estudiante" << endl;
        cout << "2. Mostrar todos los registros" << endl;
        cout << "3. Mostrar registro por ID" << endl;
        cout << "4. Desplegar registro por ID" << endl; // Nueva opción
        cout << "5. Desplegar todos los registros" << endl; // Nueva opción
        cout << "6. Salir" << endl;
        cout << "Ingrese su opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                cout << "ID: ";
                int id = obtenerIntValido();
                insertarEstudiante(id);
                cls();
                break;
            }
            case 2:
                mostrarRegistros();
                cls();
                break;
            case 3: {
                if (!hayRegistros()) {
                    cout << "No hay registros para buscar." << endl;
                    cls();
                    continue;
                }
                cout << "ID: ";
                int id = obtenerIntValido();
                mostrarRegistroPorID(id);
                cls();
                break;
            }
            case 4: {
                if (!hayRegistros()) {
                    cout << "No hay registros para eliminar." << endl;
                    cls();
                    continue;
                }
                cout << "ID a eliminar: ";
                int id = obtenerIntValido();
                eliminarRegistroPorID(id);
                cls();
                break;
            }
            case 5: {
                if (!hayRegistros()) {
                    cout << "No hay registros para eliminar." << endl;
                    cls();
                    continue;
                }
                eliminarTodosLosRegistros();
                cls();
                break;
            }
            case 6:
                cout << "Saliendo del programa." << endl;
                break;
            default:
                cout << "Opción inválida. Intente nuevamente." << endl;
                break;
        }
    } while (opcion != 6);

    return 0;
}
