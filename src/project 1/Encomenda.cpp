#include "Encomenda.h"

bool Encomenda::adicionaProduto(Produto* novoProduto, uint quantidade)
{
	if (quantidade == 0)
		return false;
	ItemListaProdutos novoItem = { novoProduto,quantidade };

	ListaProdutos::iterator iterator = find(this->listaProdutos.begin(), this->listaProdutos.end(), novoItem);

	if (iterator == listaProdutos.end()) {
		listaProdutos.insert(listaProdutos.begin(), novoItem);
		this->valorEncomenda += quantidade * novoProduto->getPreco();
	}
	else {

		iterator->second += quantidade;
		this->valorEncomenda += iterator->first->getPreco() * iterator->second;
	}
		
	return true;
}

bool Encomenda::removeProduto(Produto* produto, uint quantidade, bool removeTudo) {

	if ( (quantidade == 0) && !removeTudo)
		return false;

	ItemListaProdutos novoItem = { produto,quantidade };

	ListaProdutos::iterator iterator = find(this->listaProdutos.begin(), this->listaProdutos.end(), novoItem);

	if (iterator == listaProdutos.end())
		return true;
	else {

		if (iterator->second - quantidade <= 0) {

			this->valorEncomenda -= iterator->first->getPreco() * iterator->second;
			iterator->second = 0;
		}
		else {
			this->valorEncomenda -= iterator->first->getPreco() * quantidade;
			iterator->second -= quantidade;
		}
	}
		

	if (removeTudo || (iterator->second == 0)) {

		this->listaProdutos.erase(iterator);
		return true;
	}

	return true;
}

bool Encomenda::terminaEncomenda()
{
	if (this->listaProdutos.size() == 0)
		return false;

	this->stamp = Timestamp();
	this->terminada = true;

	return true;
}

float Encomenda::getValor()
{

	return this->valorEncomenda;
}

string Encomenda::getNomeFarmacia()
{
	return this->farmaciaOrigem;
}

string Encomenda::getNomeFornecedor()
{
	return this->fornecedorOrigem;
}

uint Encomenda::getQuantidadeProdutos()
{

	ListaProdutos::iterator it = this->listaProdutos.begin();
	ListaProdutos::iterator ite = this->listaProdutos.end();
	uint resultado = 0;

	while (it != ite) {

		resultado += it->second;
		it++;
	}

	return resultado;
}

const ListaProdutos & Encomenda::getProdutos()
{
	return this->listaProdutos;
}

void Encomenda::mudaFornecedor(string novoFornecedor)
{
	this->fornecedorOrigem = novoFornecedor;
}

Encomenda::Encomenda(string nomeFarmacia, string nomeFornecedor) {

	this->terminada = false;
	this->farmaciaOrigem = nomeFarmacia;
	this->fornecedorOrigem = nomeFornecedor;
	this->valorEncomenda = 0;

}

bool operator==(const ItemListaProdutos& p1, const ItemListaProdutos& p2) {


	return p1.first->getCodigo() == p2.first->getCodigo();
}