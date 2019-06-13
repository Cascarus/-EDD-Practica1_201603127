#include <iostream>
#include<windows.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>

#include "Pila.h"
#include "Cola.h"
#include "Lista_Doble.h"
#include "Lista_D_Circular.h"

using namespace std;

Pila carreta1 = new Pila(true);
Pila carreta2 = new Pila(true);
Cola Cola_Espera = new Cola(true);
Cola Cola_Pago = new Cola(true);
Lista_Doble Cajas = new Lista_Doble(true);
Lista_D_Circular Compras = new Lista_D_Circular(true);\

int random, turnos = 0;
string bitacora = ""; 

void Graficar();
void insertar();
void Turno();
string cadena(int numero);

int main() {

	int opcion = 0;
	while (opcion != 4) {
		system("cls");
		cout << "1. INSETAR" << endl;
		cout << "2. AVANZAR TURNO" << endl;
		cout << "3. GRAFICAR" << endl;
		cout << "4. SALIR" << endl;
		cout << "ingrese la opcion que desee realizar: ";
		cin >> opcion;

		switch (opcion) {
		case 1:
			system("cls");
			insertar();
			system("pause");
			break;

		case 2:
			int tur;
			system("cls");
			cout << "ingrese el numero de turnos quiere avanzar...";
			cin >> tur;
			for (int a = 0;a < tur;a++) {
				Turno();
			}
			system("pause");
			break;

		case 3:
			system("cls");
			cout << "Graficando.";
			for (int a = 0; a < 10; a++) {
				Sleep(100);
				cout << ".";
			}
			Graficar();
			cout << endl;
			system("pause");
			break;

		case 4:
			cout << "Finalizando.";
			for (int a = 0; a < 10; a++) {
				Sleep(100);
				cout << ".";
			}
			break;

		default:
			cout << "Inserte una opcion valida!!"<<endl;
			system("pause");
			break;
		}
	}
	return 0;
}


void insertar() {
	int opcion = 0;
	int valor = 0;
	int cliente, carreta, caja;
	while (opcion != 7) {
		system("cls");
		cout << "1. INSETAR CLIENTES" << endl;
		cout << "2. INSERTAR CARRETILLAS" << endl;
		cout << "3. INSERTAR CAJAS" << endl;
		cout << "4. MOSTRAR CLIENTES" << endl;
		cout << "5. MOSTRAR CARRETILLAS" << endl;
		cout << "6. MOSTRAR CAJAS" << endl;
		cout << "7. REGRESAR" << endl;
		cout << "ingrese la opcion que desee realizar: ";
		cin >> opcion;

		switch (opcion) {
		case 1:
			system("cls");
			cout << "Cuantos clientes desea ingresar: ";
			cin >> valor;
			for (int a = 0; a < valor; a++) {
				cout << "Ingrese un cliente (No se puden repetir).....";
				cin >> cliente;
				Cola_Espera.agregarCliente(cliente);
				bitacora += "Llega cliente " + cadena(cliente) + " y se agrega a la cola de espera\n";
			}
			cout << "se ha ingresado " << valor << " clientes correctamente al sistema! "<< endl; //<< " en la pila " << car<< endl;
			system("pause");
			break;

		case 2:
			system("cls");
			cout << "Cuantas carretas desea ingresar: ";
			cin >> valor;
			for (int a = 0; a < valor; a++) {
				cout << "Ingrese una carretilla (No se puden repetir).....";
				cin >> carreta;
				random = rand() % 2 + 1;
				if (random == 1) {
					carreta1.push(carreta);
				}
				else {
					carreta2.push(carreta);
				}
			}
			cout << "se han ingresado " << valor << " carretilla correctamente al sistema! " << endl; //<< " en la pila " << car<< endl;
			system("pause");
			break;

		case 3:
			system("cls");
			cout << "Cuantas cajas desea ingresar: ";
			cin >> valor;
			for (int a = 0; a < valor; a++) {
				cout << "Ingrese una caja (No se puden repetir).....";
				cin >> caja;
				random = rand() % 10 + 1;
				Cajas.agregar(caja,random);
			}
			cout << "se han ingresado " << valor << " cajas correctamente al sistema! " << endl; //<< " en la pila " << car<< endl;
			system("pause");
			break;

		case 4:
			system("cls");
			cout << "Clientes en cola de espera de carretas "<<endl;
			Cola_Espera.mostrar();
			system("pause");
			break;

		case 5:
			system("cls");
			cout << "Carretillas en Pila #1 "<< endl;
			carreta1.mostrar();
			cout << "\n\n Carretillas en Pila #2 " << endl;
			carreta2.mostrar();
			system("pause");
			break;

		case 6:
			system("cls");
			cout << "Cajas en el sistema " << endl;
			Cajas.mostrar();
			system("pause");
			break;

		case 7:
			break;

		default:
			cout << "Inserte una opcion valida!!"<<endl;
			system("pause");
			break;
		}
	}
}

void Turno() {
	int cliente, carreta;
	turnos++;

	cout << "---------------------Turno " << turnos << "---------------------" << endl;
	cout << bitacora;
	bitacora = "";

	//CIENTE AGARRA CARRETA
	if (!Cola_Espera.isNull()) {
		if (!carreta1.isNull() || !carreta2.isNull()) {
			cliente = Cola_Espera.sacarCliente();

			if (!carreta1.isNull() && !carreta2.isNull()) {
				random = rand() % 2 + 1;
				if (random == 1) {
					carreta = carreta1.pop();
				}
				else {
					carreta = carreta2.pop();
				}
			}
			else if (carreta2.isNull()) {
				carreta = carreta1.pop();
			}
			else {
				carreta = carreta2.pop();
			}
			Compras.agregar(cliente, carreta);
			cout << "Cliente " << cliente << " toma la carreta " << carreta << " y se incorpora a la lista de compras" << endl;
		}
	}
	
	//GENERAR NUMERO ALEATORIO Y SACARLO SI SE PUEDE
	if (!Compras.isNull()) {
		random = rand() % 20;
		cout << "El random es..." << random<<endl;
		if (Compras.VerificarTamanio(random+1)) {
			cliente = Compras.sacarCliente(random + 1);
			carreta = Compras.sacarCarreta(random+1);
			Compras.sacar(random + 1);
			Cola_Pago.agregarEspera(cliente, carreta);
			cout << "Cliente " << cliente << " entra a la cola de pagos"<<endl; //componer el cliente 
		}
	}

	//AVANZAR TURNOS EN CAJA
	Cajas.avanzarTurno();

	//PASAR CLIENTES DE COLA DE PAGOS A CAJA DISPONIBLE 
	nodo_doble *actual = new nodo_doble();
	actual = Cajas.primero;
	if (!Cajas.isNull()) {
		while (actual != NULL){
			int no_caja = actual->no_caja;

			//INGRESA CLIENTE A CAJA
			if (actual->estado == true) {
				if (!Cola_Pago.isNull()) {
					cliente = Cola_Pago.sacarEsperaCliente();
					carreta = Cola_Pago.sacarCarreta();
					Cola_Pago.sacarPagar();
					Cajas.LlegaCliente(no_caja, cliente, carreta);
					cout << "El cliente " << cliente << " pasa a la caja " << no_caja << endl;
				}
			}

			//LIBERAR CAJA
			if (actual->liberar == true) {
				cliente = Cajas.ObtenerCliente(no_caja);
				carreta = Cajas.ObtenerCarreta(no_caja);
				Cajas.LiberarCaja(no_caja);
				cout << "Cliente " << cliente << " sale de la caja. Libera carreta " << carreta << " y caja " << no_caja<<endl;
				random = rand() % 2 + 1;
				if (random == 1) {
					carreta1.push(carreta);
				}
				else {
					carreta2.push(carreta);
				}
			}
		
			actual = actual->siguiente;
		}
	}



}

void Graficar() {
	string grafica = "";
	ofstream archivo;
	archivo.open("Practica_1.dot");
	archivo << "digraph {\n";
	if (!Cola_Espera.isNull()) {
		archivo << "subgraph Cola_Espera{\n";
		archivo << Cola_Espera.recorre(1);
		archivo << "}\n";
	}
	archivo << "subgraph Pilas_Carretas{\n";
	if (!carreta1.isNull()) {
		archivo << carreta1.recorre(1);
	}
	if (!carreta2.isNull()){
		archivo << carreta2.recorre(2);
	}
	archivo << "}\n";

	if (!Compras.isNull()) {
		archivo << "subgraph Compras{\n";
		archivo << Compras.recorre();
		archivo << "}\n";
	}

	if (!Cola_Pago.isNull()) {
		archivo << "subgraph Pago{\n";
		archivo << Cola_Pago.recorre(2);
		archivo << "}\n";
	}

	if (!Cajas.isNull()) {
		archivo << "subgraph Cajas{\n";
		archivo << Cajas.recorre();
		archivo << "}\n";
	}

	archivo << "}";
	archivo.close();

	system("dot -Tpng Practica_1.dot -o Practica_1.png -Gcharset=latin1");
	system("Practica_1.png");
}

string cadena(int n) {
	stringstream flujo;
	flujo << n;
	return(flujo.str());
}