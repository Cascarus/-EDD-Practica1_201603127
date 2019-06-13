#include "Pila.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;


Pila::Pila(bool a)
{
	primero = NULL;
}

bool Pila::isNull() {
	if (primero == NULL) {
		return true;
	}
	else
	{
		return false;
	}
}


void Pila::push(int dato) {
	nodo_pila *nuevo = new nodo_pila();
	nuevo->dato = dato;
	//nuevo->id = nuevo->id++;
	nuevo->siguiente = primero;
	primero = nuevo;
}

int Pila::pop() {
	if (primero != NULL) {
		nodo_pila *temp = primero;
		int carreta = temp->dato;
		temp = temp->siguiente;
		primero = temp;
		return carreta;
	}
	return -1;
}

void Pila::mostrar() {
	nodo_pila *aux = new nodo_pila();
	aux = primero;

	if (primero != NULL) {
		int contador = 1;

		while (aux != NULL)
		{
			cout << contador << ". " << aux->dato << endl;
			aux = aux->siguiente;
			contador++;
		}
	}
}

void Pila::graficar() {
	string grafica = "";
	ofstream archivo;
	archivo.open("Pila.dot");
	archivo << "digraph {\n graph [pad=\"0.1\", nodesep=\"0.15\", ranksep=\"1\"];\n node [shape=none]\n rankdir=LR;\n Mat1 [label=<\n <table border=\"0\" cellborder=\"1\" cellspacing=\"0\">\n";
	//archivo << "\tNode [style=filled,color=orangered2];\n";
	grafica = recorrer(primero);
	archivo << grafica;
	archivo << "</table>>];\n}";
	archivo.close();

	system("dot -Tpng Pila.dot -o Pila.png -Gcharset=latin1");
	system("Pila.png");
}

string Pila::recorrer(nodo_pila *raiz) {
	string graf = "";
	if (raiz != NULL) {
		graf += "<tr><td>" + cadena(raiz->dato) + "</td></tr>\n";
		graf += recorrer(raiz->siguiente);
	}
	return graf;
}

string Pila::recorre(int numero) {
	string graf = "";
	graf += "graph[pad=\"0.1\", nodesep=\"0.15\", ranksep=\"1\"];\n node [shape=none]\n rankdir=LR;\n car" + cadena(numero) + " [label=<\n <table border=\"0\" cellborder=\"1\" cellspacing=\"0\">\n";
	graf += recorrer(primero);
	graf += "</table>>];\n";
	graf += "Nodo_Tcarretas [shape=box, label = \"Carretas\"]\n";
	graf += "Nodo_Tcarretas -> car" + cadena(numero) + "\n";
	//graf += "}\n";
	return graf;
}

string Pila::cadena(int n) {
	stringstream flujo;
	flujo << n;
	return(flujo.str());
}
