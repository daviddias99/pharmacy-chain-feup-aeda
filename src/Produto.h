#ifndef PRODUTO_H
#define PRODUTO_H

#include <string>
#include <iostream>
using namespace std;


class Produto {
public:
	Produto(long int code, string n, string desc, float pr, float i);
	long unsigned int getCodigo() const;
	string getNome() const;
	string getDesc() const;
	float getPreco() const;
	int alteraPreco(float novoPreco);
	bool operator==(const Produto &prod);
	
	virtual ostream& print(ostream& os) const;
	virtual ostream& printSimp(ostream& os) const;
protected:
	const long unsigned int codigo;
	const string nome;
	const string descricao;
	float preco;
	float iva;
};


#endif /* PRODUTO_H */
