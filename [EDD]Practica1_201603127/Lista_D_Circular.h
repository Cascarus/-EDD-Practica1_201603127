#pragma once
#include <string>
#include <fstream>
#include <sstream>

struct nodo_circular
{
	int compra, cliente, carreta;
	nodo_circular* siguiente;
	nodo_circular* anterior;
};

class Lista_D_Circular
{

private:
	nodo_circular *primero, *ultimo;
	int contador =0, compra = 0;
	std::string cadena(int n);
	std::string recorrer(nodo_circular* raiz);

public:
	Lista_D_Circular(bool a);
	bool isNull();
	bool VerificarTamanio(int pos);
	void agregar(int cliente, int carreta);
	void mostrar();
	void graficar();
	int sacarCliente(int pos);
	int sacarCarreta(int pos);
	void sacar(int pos);
	std::string recorre();
	//bool existe(int caja);

};