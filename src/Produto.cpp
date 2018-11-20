#include "Produto.h"


Produto::Produto(long int cod, string n, string desc, float pr, float i) : codigo(cod), nome(n), descricao(desc) {
	preco = pr;
	iva = i;
}


long unsigned int Produto::getCodigo() const {
	return codigo;
}

string Produto::getNome() const {
	return nome;
}

string Produto::getDesc() const {
	return descricao;
}

float Produto::getPreco() const {
	return preco;
}

int Produto::alteraPreco(float novoPreco) {

	if (novoPreco > 0) {
		preco = novoPreco;
		return 0;
	}
	else
		return 1;
}

bool Produto::operator==(const Produto &prod) {
	return codigo == prod.codigo;
}

ostream & operator<<(ostream & os, const Produto & prod)
{
	os << "COUT DE UM PRODUTO- WIP" << endl;
	return os;
}

ostream & Produto::print(ostream & os) const
{
	os << "Codigo: " << codigo << "\t\tNome: " << nome << endl;
	os << "Descricao: " << descricao << endl << "Preco: " << preco << "e \t\tIva: " << iva * 100 << "%" << endl;

	return os;
}

ostream& Produto::printSimp(ostream& os) const {

	os << codigo << "&" << nome << "&" << descricao << "&" << preco << "&" << iva << endl;

	return os;
}