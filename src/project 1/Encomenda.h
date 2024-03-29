#ifndef ENCOMENDA_H
#define ENCOMENDA_H

#include "Produto.h"
#include "string"
#include "util.h"
#include <list>


typedef pair<Produto*, uint> ItemListaProdutos;
typedef list<ItemListaProdutos>ListaProdutos;

class Encomenda {

public:

	Encomenda(string nomeFarmacia, string nomeFornecedor);
	bool adicionaProduto(Produto* novoProduto, uint quantidade);
	bool removeProduto(Produto* produto, uint quantidade, bool removeTudo = false);
	bool terminaEncomenda();
	float getValor();
	string getNomeFarmacia();
	string getNomeFornecedor();
	uint getQuantidadeProdutos();
	const ListaProdutos& getProdutos();
	void mudaFornecedor(string novoFornecedor);


private:
	string farmaciaOrigem;
	string fornecedorOrigem;
	ListaProdutos listaProdutos;
	float valorEncomenda;
	Timestamp stamp;
	bool terminada;
};

bool operator==(const ItemListaProdutos& p1, const ItemListaProdutos& p2);

#endif
