#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

struct nodo_pila
{
	int dato;
	nodo_pila* siguiente;
};

class Pila
{
private:
	nodo_pila *primero;
	std::string cadena(int n);

public:
	Pila(bool a);
	bool isNull();
	void push(int a);
	int pop();
	void graficar();
	void mostrar();
	std::string recorrer(nodo_pila *raiz);
	std::string recorre(int a);
};
