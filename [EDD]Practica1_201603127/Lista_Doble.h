#pragma once
#include <string>
#include <fstream>
#include <sstream>

struct nodo_doble
{
	int no_caja, tiempo, cliente, carreta, Contador_Turnos;
	bool estado,liberar;
	std::string estd;
	nodo_doble* siguiente;
	nodo_doble* anterior;
};

class Lista_Doble
{

private:
	std::string cadena(int n);
	std::string recorrer(nodo_doble * raiz);

public:
	nodo_doble *primero, *ultimo;
	Lista_Doble(bool a);
	bool isNull();
	void agregar(int caja, int tiempo);
	void mostrar();
	void graficar();
	void LlegaCliente(int caja, int cliente, int carreta);
	std::string recorre();
	bool existe(int caja);
	int ObtenerCarreta(int caja);
	int ObtenerCliente(int caja);
	void LiberarCaja(int caja);
	void avanzarTurno();
};

