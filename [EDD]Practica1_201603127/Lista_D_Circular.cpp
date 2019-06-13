#include "Lista_D_Circular.h"
#include <iostream>

using namespace std;

Lista_D_Circular::Lista_D_Circular(bool a)
{
	primero = NULL;
	ultimo = NULL;
}

bool Lista_D_Circular::isNull() {
	if (primero == NULL) {
		return true;
	}
	return false;
}

bool Lista_D_Circular::VerificarTamanio(int pos) {
	if (pos <= contador) {
		return true;
	}
	return false;
}

void Lista_D_Circular::agregar(int cliente, int carreta) {
	nodo_circular *nuevo = new nodo_circular();
	nuevo->compra = compra++;
	nuevo->cliente = cliente;
	nuevo->carreta = carreta;

	if (isNull()) {
		primero = nuevo;
		ultimo = nuevo;
		primero->anterior = ultimo;
		ultimo->siguiente = primero;
	}
	else {
		ultimo->siguiente = nuevo;
		nuevo->anterior = ultimo;
		nuevo->siguiente = primero;
		ultimo = nuevo;
		primero->anterior = ultimo;
	}
	contador++;
	//cout << "el dato se ha agregado exitosamente!" << endl;
}



void Lista_D_Circular::mostrar() {
	nodo_circular *aux = new nodo_circular();
	aux = primero;

	if (!isNull()) {
		do {
			int contador = 1;
			cout << contador << ". Cliente..." << aux->cliente << " Carreta..."<< aux->carreta << endl;
			aux = aux->siguiente;
			contador++;
		} while (aux != primero);
		
	}
}

int Lista_D_Circular::sacarCliente(int posicion) {
	int iteraciones = 1;
	nodo_circular *actual = primero;

	if (!isNull()) {
		while (iteraciones < posicion)
		{
			iteraciones++;
			actual = actual->siguiente;
		}
		return actual->cliente;
	}
	return -1;
}

int Lista_D_Circular::sacarCarreta(int posicion) {
	int iteraciones = 1;
	nodo_circular *actual = primero;

	if (!isNull()) {
		while (iteraciones < posicion)
		{
			iteraciones++;
			actual = actual->siguiente;
		}
		return actual->carreta;
	}
	return -1;
}

void Lista_D_Circular::sacar(int pos)
{
	int iteraciones = 1;
	nodo_circular *actual = primero;
	nodo_circular *anterior = new nodo_circular();
	anterior = NULL;

	if (!isNull()) {
		if (pos == 1) {
			primero->anterior->siguiente = primero->siguiente;
			primero->siguiente->anterior = primero->anterior;
			primero = primero->siguiente;
		}else if (pos == contador) {
			ultimo->anterior->siguiente = ultimo->siguiente;
			ultimo->siguiente->anterior = ultimo->anterior;
			ultimo = ultimo->anterior;
		}else {
			while (iteraciones < pos)
			{
				iteraciones++;
				anterior = actual;
				actual = actual->siguiente;
			}
			anterior->siguiente = actual->siguiente;
			actual->siguiente->anterior = anterior;
		}
		contador--;
	}
}

void Lista_D_Circular::graficar() {
	string grafica = "";
	ofstream archivo;
	archivo.open("DobleCircular.dot");
	archivo << "digraph {\n rankdir=TB;\n";
	grafica = recorrer(primero);
	archivo << grafica;
	archivo << "}\n";
	archivo.close();

	system("dot -Tpng DobleCircular.dot -o DobleCircular.png -Gcharset=latin1");
	system("DobleCircular.png");
}

string Lista_D_Circular::recorrer(nodo_circular *raiz) {
	string graf = "";
	nodo_circular *actual = raiz;
	if (raiz != NULL) {
		do{
			graf += "\tNodeCompra_" + cadena(actual->compra) + "->" + "NodeCompra_" + cadena(actual->siguiente->compra) + "[constraint=false]; \n";
			graf += "\tNodeCompra_" + cadena(actual->compra) + "->" + "NodeCompra_" + cadena(actual->siguiente->compra) + "[dir=back, constraint=false]; \n";
			graf += "\n \tNodeCompra_" + cadena(actual->compra) + "[shape=box,style=filled,color=chartreuse1  , label = \"-Cliente " + cadena(actual->cliente) + "\n -Carreta " + cadena(actual->carreta) + " \"] \n";
			actual = actual->siguiente;
		} while (actual != raiz);
	}
	return graf;
}

string Lista_D_Circular::recorre() {
	string graf = "";
	graf += recorrer(primero);
	return graf;
}

string Lista_D_Circular::cadena(int n) {
	stringstream flujo;
	flujo << n;
	return(flujo.str());
}