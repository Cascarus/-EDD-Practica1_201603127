#include "Lista_Doble.h"
#include <iostream>

using namespace std;

Lista_Doble::Lista_Doble(bool a) {
	primero = NULL;
	ultimo = NULL;
}

bool Lista_Doble::isNull() {
	if (primero == NULL) {
		return true;
	}
	return false;
}


void Lista_Doble::agregar(int caja, int tiempo) {
	nodo_doble *nuevo = new nodo_doble();
	nuevo->no_caja = caja;
	nuevo->tiempo = tiempo;
	nuevo->Contador_Turnos = tiempo;
	nuevo->estado = true;
	nuevo->liberar = false;
	nuevo->estd = "Desocupado";

	if (isNull()) {
		primero = nuevo;
		ultimo = nuevo;
	}else {
		ultimo->siguiente = nuevo;
		nuevo->anterior = ultimo;
		ultimo = nuevo;
	}
}

bool Lista_Doble::existe(int caja) {
	nodo_doble *aux = new nodo_doble();
	aux = primero;

	if (!isNull()) {
		while (aux != NULL)
		{
			if (aux->no_caja == caja) {
				return true;
			}
			aux = aux->siguiente;
		}
		return false;
	}
	return false;
}

void Lista_Doble::LlegaCliente(int caja, int cliente, int carreta) {
	nodo_doble *actual = new nodo_doble();
	actual = primero;

	if (!isNull()) {

		while (actual != NULL)
		{
			if(actual->no_caja == caja){
				actual->cliente = cliente;
				actual->carreta = carreta;
				actual->Contador_Turnos = actual->tiempo;
				actual->estado = false;
				actual->estd = "Ocupado";
				break;
			}
			actual = actual->siguiente;
		}
	}
}

int Lista_Doble::ObtenerCarreta(int caja) {
	nodo_doble *actual = new nodo_doble();
	actual = primero;

	if (!isNull()) {

		while (actual != NULL)
		{
			if (actual->no_caja == caja) {
				return actual->carreta;
			}
			actual = actual->siguiente;
		}
	}
	return -1;
}

int Lista_Doble::ObtenerCliente(int caja) {
	nodo_doble *actual = new nodo_doble();
	actual = primero;

	if (!isNull()) {

		while (actual != NULL)
		{
			if (actual->no_caja == caja) {
				return actual->carreta;
			}
			actual = actual->siguiente;
		}
	}
	return -1;
}

void Lista_Doble::LiberarCaja(int caja) {
	nodo_doble *actual = new nodo_doble();
	actual = primero;

	if (!isNull()) {

		while (actual != NULL)
		{
			if (actual->no_caja == caja) {
				actual->cliente = NULL;
				actual->carreta = NULL;
				actual->Contador_Turnos = actual->tiempo;
				actual->estado = true;
				actual->estd = "Desocupado";
				actual->liberar = false;
				break;
			}
			actual = actual->siguiente;
		}
	}
}

void Lista_Doble::avanzarTurno() {
	nodo_doble *aux = new nodo_doble();
	aux = primero;

	if (!isNull()) {
		while (aux != NULL)
		{
			if (aux->estado == false) {
				aux->Contador_Turnos--;
				if (aux->Contador_Turnos == 0) {
					aux->liberar = true;
				}
				else {
					cout << "Cliente " << aux->cliente << " esta siendo atendido por la caja " << aux->no_caja << endl;
				}
			}
			aux = aux->siguiente;
		}
	}
}


void Lista_Doble::mostrar() {
	nodo_doble *aux = new nodo_doble();
	aux = primero;

	if (!isNull()) {
		int contador = 1;

		while (aux != NULL)
		{
			cout << contador << ". " << aux->no_caja << " con turnos " << aux->tiempo << endl;
			aux = aux->siguiente;
			contador++;
		}
	}
}

void Lista_Doble::graficar() {
	string grafica = "";
	ofstream archivo;
	archivo.open("Doble.dot");
	archivo << "digraph {\n rankdir=LR;\n";
	grafica = recorrer(primero);
	archivo << grafica;
	archivo << "}\n";
	archivo.close();

	system("dot -Tpng Doble.dot -o Doble.png -Gcharset=latin1");
	system("Doble.png");
}

string Lista_Doble::recorrer(nodo_doble *raiz) {
	string graf = "";
	if (raiz != NULL) {
		if (raiz->siguiente != NULL) {
			graf += "\tNodeCaja_" + cadena(raiz->no_caja) + "->" + "NodeCaja_" + cadena(raiz->siguiente->no_caja) + "; \n";
			graf += "\tNodeCaja_" + cadena(raiz->no_caja) + "->" + "NodeCaja_" + cadena(raiz->siguiente->no_caja) + "[dir=back]; \n";
		}
		graf += "\n \tNodeCaja_" + cadena(raiz->no_caja) + "[shape=box,style=filled,color=coral1  , label = \"-Caja " + cadena(raiz->no_caja) + "\n -" + cadena(raiz->Contador_Turnos) + " Turnos \n -" + raiz->estd +  "\"] \n";
		graf += recorrer(raiz->siguiente);
	}
	return graf;
}

string Lista_Doble::recorre() {
	string graf = "";
	graf += recorrer(primero);
	graf += "Nodo_Tcajas->NodeCaja_" + cadena(primero->no_caja) + "\n";
	graf += "Nodo_Tcajas[shape = box, label = \"CAJAS\"]\n";
	//graf += "}\n";
	return graf;
}

string Lista_Doble::cadena(int n) {
	stringstream flujo;
	flujo << n;
	return(flujo.str());
}