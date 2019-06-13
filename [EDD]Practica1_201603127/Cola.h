#pragma once
#include <string>
#include <fstream>
#include <sstream>

struct nodo_cola
{
	int dato, carreta;
	nodo_cola* siguiente;
};

class Cola
{
private:
	nodo_cola *primero, *ultimo;
	
	std::string cadena(int n);

public:
	Cola(bool a);
	bool isNull();
	void agregarCliente(int dato);
	void agregarEspera(int dato, int carreta);
	int sacarCliente();
	int sacarEsperaCliente();
	int sacarCarreta();
	void sacarPagar();
	void mostrar();
	void graficar1();
	void graficar2();
	std::string recorrer1(nodo_cola *raiz);
	std::string recorrer2(nodo_cola *raiz);
	std::string recorre(int opcion);
};

