/*
*   Nombre del archivo:				main.cpp
*	Información de la versión:		Se creó en VisualStudio 2017
*	Fecha:							Sabado, 18 de agosto de 2018.
*	Autores:					    Hayser Dávila Abarca.
*/
#include <fstream>//Cargar archivos
#include <iostream>//Input and OutPut
#include <stdlib.h>//srand
#include <string>//Usar Strings
#include <time.h>//Random
#include <ctime>//Random
#include <vector>//STL vector
#include <sstream>//Encabezado que proporciona clases de secuencia de string
using namespace std;


//Declaración de metodos
void Gana();
void Pierde();
vector<string> agregarLineas(int);
string MostrarPalabrasEncontradas(vector<string>, int);
string muestraMuneco(int);

int main() {

	while (true) {

		cout << "\n\t\t\t    BIENVENIDO AL JUEGO DEl AHORCADO" << endl;
		cout << "\n\t\t\t***************************************";
		cout << "\n\t\t\t*         MENU PRINCIPAL              *";
		cout << "\n\t\t\t*                                     *";
		cout << "\n\t\t\t*         Opcion 1:JUGAR              *";
		cout << "\n\t\t\t*                                     *";
		cout << "\n\t\t\t*         Opcion 2:SALIR              *";
		cout << "\n\t\t\t*                                     *";
		cout << "\n\t\t\t***************************************";
		cout << "\n";
		cout << "\n\t\t\t\t Digite un Opcion: ";

		// validacion de que no se ingrese un valor mayor a 2 o una letra
		int opcion = 0;
		do {
			cin >> opcion;

		} while (opcion > 2);

		//Final del juego
		if (opcion == 2) {
			return 0;
		}
		system("cls");

		//Cargar el archivo e insertar las palabras en el vector  
		vector<string> palabras;
		int tamanoArchivo = 0;

		ifstream archivo;
		archivo.open("palabras.txt");//se carga el archivo
		if (archivo.is_open()) {
			while (archivo.good()) {//se verifica que sea correcto
				string letra;
				getline(archivo, letra); //se selecciona la palabra y se inserta en el vector 
				palabras.push_back(letra);
				tamanoArchivo++;
			}
		}
		srand(static_cast<unsigned int>(time(nullptr))); //Semilla que escoge una palabra del archivo txt
		const int semilla = rand() % tamanoArchivo;
		const string PalSeleccionada = palabras[semilla];

		// Lineas y tamaño de la palabra
		const  int intentos = 7;
		const  int PalSeleccionadaTamano = PalSeleccionada.length(); //esto se pude resumir
		vector<string> adivinar = agregarLineas(PalSeleccionadaTamano);
		vector<string> errores = agregarLineas(intentos);


		int cantErrores = 0;
		int cantCorrectos = 0;
		while (cantErrores < intentos) {
			cout << "\n\t\t <------AHORCADO------>" << endl;

			cout << endl;
			cout << endl;
			cout << "Le quedan " << 7 - cantErrores << " intentos" << endl;
			cout << endl;
			cout << "Letras Correctas: " << MostrarPalabrasEncontradas(adivinar, PalSeleccionadaTamano) << endl;
			cout << endl;
			cout << "Letras Erroneas: " << MostrarPalabrasEncontradas(errores, intentos) << endl;
			cout << endl;
			cout << "Ingresa una letra: ";
			cout << endl;
			cout << muestraMuneco(cantErrores);

			string letraIngresada;
			do {
				cin >> letraIngresada;
				cout << endl;
			} while (letraIngresada.length() > 1);

			// Se verifica si la letra pertenece a la palabra
			bool palabraValidacion = false;
			for (int i = 0; i <= PalSeleccionadaTamano; i++) {
				const string letraValida = PalSeleccionada.substr(i, 1);//manejar la cadenas de caracteres para no usar punteros.
				if (letraIngresada == letraValida) {
					adivinar[i] = letraIngresada;
					cantCorrectos++;
					palabraValidacion = true;
				}
			}

			// Si hay un error con la letra se agrega al vector de errores y se muestra en pantalla
			if (!palabraValidacion) {
				errores[cantErrores] = letraIngresada;
				cantErrores++;
			}

			//se compara la cantidad de aciertos  con la palabra
			if (cantCorrectos == PalSeleccionadaTamano) {
				Gana(); // Mensaje de gano
				cout << endl;
				cout << "La palabra era:" << PalSeleccionada << endl;
				cout << endl;
				cout << "Presione la letra s o S para salir" << endl;
				cin >> letraIngresada;
				cantErrores = intentos;//se restablece la cantidad de errores a cero para un nuevo juego
			}
			//se compara la cantidad de errores con los intentos
			else if (cantErrores == intentos) {
				Pierde();// Mensaje de perdio
				cout << endl;
				cout << "La palabra era:" << PalSeleccionada << endl;
				cout << endl;
				cout << "Presione la letra s o S para salir" << endl;
				cin >> letraIngresada;
				cantErrores = intentos;//se restablece la cantidad de errores a cero para un nuevo juego
			}
			system("cls");
		}
	}


}

//metodo que muestra un mensaje al usuario que de gano el juego
void Gana() {
	cout << "<-------FELICIDADES HAS GANADO------->" << endl;
}

//metodo que muestra un mensaje al usuario de que perdio el juego
void Pierde() {
	cout << "<------HAS PERDIDO, INTENTALO DE NUEVO------>" << endl;
}

//Muestro el numero de lineas que tiene la palabra
vector<string> agregarLineas(int tamano) { //pasar el iterador tipo int
	vector<string> Lineas;
	for (int i = 0; i < tamano; i++) {
		Lineas.push_back("-");
	}
	return Lineas;
}
//Muestra la letra en la poscion del vector STL
string MostrarPalabrasEncontradas(vector<string> letras, int limite) { //pasar el iterador tipo int
	string mostrar;
	for (int i = 0; i < limite; i++) {
		mostrar += letras[i] + " ";
	}
	return mostrar;
}

string muestraMuneco(int intentosFallidos) { //dibujo del Ahorcado
	stringstream s;
	s << " ______ \n";
	s << "|      |\n";
	s << "|      ";

	if (intentosFallidos >= 1) {
		s << '0';
	}
	s << '\n';
	s << "|    ";

	if (intentosFallidos >= 2) {
		s << "|";
	}
	if (intentosFallidos >= 3) {
		s << " | ";
	}
	if (intentosFallidos >= 4) {
		s << "|";
	}
	s << '\n';
	s << "|      ";
	if (intentosFallidos >= 5) {
		s << "|";
	}
	s << '\n';
	s << "|     ";
	if (intentosFallidos >= 6) {
		s << "|";
	}
	if (intentosFallidos == 7) {
		s << " |";
		s << endl;
		s << endl;
	}
	s << '\n';
	return s.str();
}

