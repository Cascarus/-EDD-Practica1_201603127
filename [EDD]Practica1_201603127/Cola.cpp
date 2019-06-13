#include "Cola.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>

using namespace std;

Cola::Cola(bool a)
{
	primero = NULL;
	ultimo = NULL;
}

bool Cola::isNull() {
	if (primero == NULL) {
		return true;
	}
	else
	{
		return false;
	}
}

void Cola::agregarCliente(int dato) {
	nodo_cola *nuevo = new nodo_cola();
	nuevo->dato = dato;

	if (isNull()) {
		primero = nuevo;
		primero->siguiente = NULL;
		ultimo = nuevo;
	}
	else {
		ultimo->siguiente = nuevo;
		nuevo->siguiente = NULL;
		ultimo = nuevo;
	}
}

void Cola::agregarEspera(int dato, int carreta) {
	nodo_cola *nuevo = new nodo_cola();
	nuevo->dato = dato;
	nuevo->carreta = carreta;

	if (isNull()) {
		primero = nuevo;
		primero->siguiente = NULL;
		ultimo = nuevo;
	}
	else {
		ultimo->siguiente = nuevo;
		nuevo->siguiente = NULL;
		ultimo = nuevo;
	}

}

int Cola::sacarCliente() {
	int cliente;
	
	if (!isNull()) {
		cliente = primero->dato;
		primero = primero->siguiente;
		return cliente;
	}
	return -1;
}

int Cola::sacarEsperaCliente() {
	int cliente;

	if (!isNull()) {
		cliente = primero->dato;
		return cliente;
	}
	return -1;
}

int Cola::sacarCarreta() {
	int cliente;

	if (!isNull()) {
		cliente = primero->carreta;
		return cliente;
	}
	return -1;
}

void Cola::sacarPagar() {

	if (!isNull()) {
		primero = primero->siguiente;
	}
}

void Cola::mostrar() {
	nodo_cola *aux = new nodo_cola();
	aux = primero;

	if (primero != NULL) {
		int contador = 1;

		while (aux != NULL)
		{
			cout << contador << ". Cliente..." << aux->dato << " Carretilla..." << aux->carreta <<endl;
			aux = aux->siguiente;
			contador++;
		}
	}
}

void Cola::graficar1() {
	string grafica = "";
	ofstream archivo;
	archivo.open("Cola.dot");
	archivo << "digraph {\n rankdir=TB;\n";
	grafica = recorrer1(primero);
	archivo << grafica;
	archivo << "}\n";
	archivo.close();

	system("dot -Tpng Cola.dot -o Cola.png -Gcharset=latin1");
	system("Cola.png");
}

void Cola::graficar2() {
	string grafica = "";
	ofstream archivo;
	archivo.open("Cola_Pagar.dot");
	archivo << "digraph {\n rankdir=TB;\n";
	grafica = recorrer2(primero);
	archivo << grafica;
	archivo << "}\n";
	archivo.close();

	system("dot -Tpng Cola_Pagar.dot -o Cola_Pagar.png -Gcharset=latin1");
	system("Cola_Pagar.png");
}

string Cola::recorrer1(nodo_cola *raiz) {
	string graf = "";
	if (raiz != NULL) {
		if (raiz-> siguiente != NULL) {
			graf += "\tNodeCliente_" + cadena(raiz->dato) + "->" + "NodeCliente_" + cadena(raiz->siguiente->dato) + "; \n";
		}
		graf += "\n \tNodeCliente_" + cadena(raiz->dato) + "[shape=box,style=filled,color=slategray1  , label = \" Cliente " + cadena(raiz->dato)+ "\"] \n";
		graf += recorrer1(raiz->siguiente);
	}
	return graf;
}

string Cola::recorrer2(nodo_cola *raiz) {
	string graf = "";
	if (raiz != NULL) {
		if (raiz->siguiente != NULL) {
			graf += "\tNodePagar_" + cadena(raiz->dato) + "->" + "NodePagar_" + cadena(raiz->siguiente->dato) + "; \n";
		}
		graf += "\n \tNodePagar_" + cadena(raiz->dato) + "[shape=box,style=filled,color=lightslateblue  , label = \" Cliente " + cadena(raiz->dato) + "\"] \n";
		graf += recorrer2(raiz->siguiente);
	}
	return graf;
}

string Cola::recorre(int opcion) {
	string graf = "";
	
	switch (opcion){
	case 1:
		graf += recorrer1(primero);
		graf += "Nodo_Tcola1->NodeCliente_" + cadena(primero->dato) + "\n";
		graf += "Nodo_Tcola1[shape = box, label = \"Cola de espera\"]\n";
		break;
	case 2:
		graf += recorrer2(primero);
		graf += "Nodo_Tcola2->NodePagar_" + cadena(primero->dato) + "\n";
		graf += "Nodo_Tcola2[shape = box, label = \"Cola para pagar\"]\n";
		break;

	default:
		break;
	}
	
	//graf += "}\n";
	return graf;
}

string Cola::cadena(int n) {
	stringstream flujo;
	flujo << n;
	return(flujo.str());
}


