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
vector <int> indices;
int funcionHash(int id) 
{
	int indice;
	bool repetido = false;
	indice = id % tablaHash.size();
		for (int i = 0; i < indices.size(); i++) {
			while (indices[i] == indice)
			{
				indice++;
				i = 0;
			}
			if (indice == tablaHash.size())
			{
				for (int e = 0; e < indices.size(); e++)
				{
					while (indices[e] == indice)
					{
						indice--;
						e = 0;
					}
				}

			}
	}
	indices.push_back(indice);
	return indice;
	
}

string verificar() {

	string entrada;
	bool valido = false;
	while (!valido)
	{
		cin >> entrada;
		for (char c : entrada) {
			if (!('a' <= c && c <= 'z') && !('A' <= c && c <= 'Z')) {
				cout << "\nEntrada inválida: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			else valido = true;
		}
	}

	return entrada;
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

void insertarEstudiante(int id) {
	int indice = funcionHash(id);
	NodoEstudiante* nuevoEstudiante = new NodoEstudiante;
	nuevoEstudiante->estudiante.id = id;
	cout << "Indice: " << indice;
	cout << "\nNOMBRE: ";
	cin.ignore();
	nuevoEstudiante->estudiante.nombre = verificar();
	cout << "CARRERA: ";
	nuevoEstudiante->estudiante.cod_carrera = verificar();
	while (true) {
		cout << "INDICE ACADEMICO: ";
		nuevoEstudiante->estudiante.indice_acad = obtenerIntValido();

		if (nuevoEstudiante->estudiante.indice_acad < 0 || nuevoEstudiante->estudiante.indice_acad > 4)
		{
			cout << "Entrada invalida, el indice debe ser entre 0-4\n";
		}
		else break;
	}
	nuevoEstudiante->siguiente = nullptr;

	if (tablaHash[indice-1] == nullptr) {
		tablaHash[indice-1] = nuevoEstudiante;
	}
	else {
		NodoEstudiante* actual = tablaHash[indice-1];
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
			cout << "Indice: " << indices[i] << endl;
			cout << "NOMBRE: " << actual->estudiante.nombre << endl;
			cout << "CARRERA: " << actual->estudiante.cod_carrera << endl;
			cout << "INDICE ACADEMICO: " << actual->estudiante.indice_acad << endl;
			cout << "-------------------------" << endl;
			actual = actual->siguiente;
		}
	}
}

void mostrarRegistroPorID(int id) {
	
	for (int i = 0; i < tablaHash.size(); i++)
	{
		NodoEstudiante* actual = tablaHash[i];
		while (actual != nullptr) {
			int indice = indices[i];
			if (actual->estudiante.id == id) {
				cout << "Indice: " << indice << endl;
				cout << "NOMBRE: " << actual->estudiante.nombre << endl;
				cout << "CARRERA: " << actual->estudiante.cod_carrera << endl;
				cout << "INDICE ACADEMICO: " << actual->estudiante.indice_acad << endl;
				return;
			}
			actual = actual->siguiente;
		}
	}


	cout << "El ID no fue encontrado." << endl;
}

void eliminarRegistroPorID(int id) {
	NodoEstudiante* anterior = nullptr;
	for (int i = 0; i < tablaHash.size(); i++)
	{
		NodoEstudiante* actual = tablaHash[i];
		while (actual != nullptr) {
			int indice = indices[i];
			if (actual->estudiante.id == id) {
				if (anterior == nullptr) {
					tablaHash[indice - 1] = actual->siguiente;
				}
				else {
					anterior->siguiente = actual->siguiente;
				}
				delete actual;
				cout << "El registro con ID " << id << " ha sido eliminado." << endl;
				return;
			}
			anterior = actual;
			actual = actual->siguiente;
			
		}
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

void cls() {
	if (continuar()) {
		cout << "Entendido" << endl;
		system("cls");
	}
	else {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		exit(0);
	}
}

int main() {
	cout << "Ingrese la cantidad de estudiantes en su sección: ";
	int numEstudiantes = obtenerIntValido();
	tablaHash.resize(numEstudiantes, nullptr);

	int opcion, id, contador = 0, indice;
	bool repetido = false;
	vector <int> Ids;
	do {
		cout << "Menu:" << endl;
		cout << "1. Insertar estudiante" << endl;
		cout << "2. Mostrar todos los registros" << endl;
		cout << "3. Mostrar registro por ID" << endl;
		cout << "4. Eliminar registro por ID" << endl; // Nueva opción
		cout << "5. Eliminar todos los registros" << endl; // Nueva opción
		cout << "6. Salir" << endl;
		cout << "Ingrese su opción: ";
		opcion = obtenerIntValido();

		switch (opcion) {
		case 1: {
			id = 0;
			if (contador >= numEstudiantes)
			{
				cout << "ya se a alcanzado el limite de estudiantes en la seccion\n";
				cls();
				break;
			}
			while (id <= 1000000 || id >= 9999999 || repetido == true) {
				cout << "\nID: ";
				id = obtenerIntValido();
				for (int i = 0; i < Ids.size(); i++)
				{
					if (Ids[i] == id)
					{
						cout << "Dos estudiantes no pueden tener el mismo id";
						repetido = true;
					}
					else repetido = false;
					
				}
				if (id <= 1000000 || id >= 9999999)
				{
					cout << "entrada invalida(ingresar numero de 7 digitos)";
				}
			}
			insertarEstudiante(id);
			Ids.push_back(id);
			contador++;
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
    } while (opcion != 6);

    return 0;
}
