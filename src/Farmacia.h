#ifndef Farmacia_H
#define Farmacia_H

#include <string>
#include <vector>
#include <map>
#include "Cliente.h"
#include "Produto.h"
#include "Empregado.h"
#include "util.h"

using namespace std;

class Farmacia {
public:
	Farmacia(string nome, Morada Morada, Empregado gerente);
	virtual ~Farmacia();
	bool addProduto(Produto produto);
	Produto removeProduto(Product product, int quantity);
	string getNome() const;
	Morada getMorada() const;
	Empregado getGerente() const;
	bool operator == (const Farmacia & ph1);
private:
	string nome;
	Morada morada;
	Empregado gerente;
	vector< Empregado > empregados;
	map<Produto, int> stock;
};

#endif