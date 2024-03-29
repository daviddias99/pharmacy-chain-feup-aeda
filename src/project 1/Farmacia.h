#ifndef Farmacia_H
#define Farmacia_H

#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <queue>


#include "Empregado.h"
#include "Cliente.h"
#include "Produto.h"
#include "Medicamento.h"
#include "Excecoes.h"
#include "Fornecedor.h"
#include "Encomenda.h"

using namespace std;

/*!
 * \file Farmacia.h
 *
 * \author FEUP AEDA1819 MIEIC Turma5_G1
 * \author David Silva
 * \author Gaspar Pinheiro
 * \author Luis Cunha
 */

/** @defgroup Farmacia Farmacia
 * @{
 *
 * Farmacia 
 */


/**
 * @brief Classe que representa uma farmacia
 * 
 */

typedef priority_queue<Fornecedor*, vector<Fornecedor*>, fornecedor_heap_sort_func> HeapFornecedores;
typedef priority_queue<pair<Produto*, uint>> HeapStock;


class Farmacia {
public:
	/**
	* @brief Construtor da classe Farmacia que inicializa os atributos nome e morada
	* @param nome Nome da farmacia
	* @param morada Morada da farmacia
	*/
	Farmacia(string nome, Morada morada);
	/**
	* @brief Construtor da classe farmacia que inicializa os atributos atravez do conteudo lido de um ficheiro de texto
	* @param simp String com as informacoes sobre a farmacia no formato escrito pelo programa num ficheiro de texto
	*/
	Farmacia(string simp);
	/** 
	*  @brief Destrutor da classe Farmacia. Liberta da memoria o gerente, o vetor de empregados, os produtos e as vendas 
	*/
	virtual ~Farmacia();
	/**
	* @brief Adiciona um produto ao stock da farmacia. Se este ja existir, e lhe adicionada a quantidade indicada no segundo parametro
	* @param produto Apontador para o produto que vai ser adicionado ao stock ou que vai ter um aumento da quantidade
	* @param quantidade Quantidade que vai ser adicionada de produto ao stock
	*/
	void addProduto(Produto *produto, int quantidade);
	/**
	* @brief Adiciona o empregado indicado no argumento a lista de empregados da farmacia
	* @param empregado Apontador para empregado que vai ser adicionado a lista de empregados da farmacia 
	*/
	bool addEmpregado(Empregado* empregado);
	/**
	* @brief Remove o poduto com o codigo indicado no seu parametro completamente da lista de produtos em stock
	* @param codigo Codigo do produto a ser removido
	*/
	void remProduto(long unsigned int codigo);
	/**
	* @brief Remove o empregado com o ID indicado no seu parametro da lista de empregados da farmacia
	* @param ID ID do empregado a ser removido
	*/
	void remEmpregado(uint ID);
	/**
	* @brief Troca de gerente da farmacia. O antigo gerente passa a ter o cargo de empregado e o gerente passa a ser o empregado indicado no seu parametro.
	* @param novoGerente Apontador para o empregado que vai passar a ser o gerente da farmacia.
	* @param novoCargo	 novo cago a ser atribuido ao ex-gerente
	* @return true se a troca foi realizada com sucesso
	* false se ocorreu algum problema.
	*/
	bool setGerente(Empregado* novoGerente, string novoCargo);
	/**
	* @brief Remove a quantidade indicada no segundo parametro de produto com o codigo indicado no primeiro parametro do stock da farmacia. 
	* Lanca uma excecao se o produto nao existe em stock
	* @param codigo Codigo do produto no qual a quantidade em stock vai ser reduzida
	* @param quantidade Quantidade de produto a diminuir ao stock
	* @return True se a quantidade foi removida com sucesso
	* False se a quantidade indicada no parametro e maior do que a quantidade de produto em stock
	*/
	void removeQuantidade(long unsigned int codigo, uint quantidade);
	/**
	* @brief Adiciona a quantidade indicada no segundo parametro de produto com o codigo indicado no primeiro argumento ao stock da farmacia
	* @param codigo Codigo do produto no qual a quantidade em stock vai ser aumentada
	* @param quantidade Quantidade de produto a aumentar ao stock
	*/
	void addQuantidade(long unsigned int codigo, uint quantidade);
	/**
	* @brief Procura no stock da farmacia pelo produto com o codigo indicado no parametro
	* @param codigo Codigo do produto a ser procurado
	* @return True se o produto foi encontrado
	* False se o produto nao existe
	*/
	bool existeProduto(unsigned long int codigo);
	/**
	* @brief Devolve o nome da farmacia
	* @return Nome da farmacia
	*/
	string getNome() const;
	/**
	* @brief Devolve a morada da farmacia
	* @return Morada da farmacia
	*/
	Morada getMorada() const;
	/**
	* @brief Devolve o gerente da farmacia
	* @return Gerente da farmacia
	*/
	Empregado* getGerente() const;
	/**
	* @brief Procura na lista de empregados da farmacia aqueles com o nome indicado no parametro
	* @param nome Nome dos empregados que vai procurar na lista de empregados da farmacia
	* @return Vetor de apontadores para empregados com o nome indicado no parametro que trabalham na farmacia
	*/
	vector<Empregado*> getEmpregados(string nome) const;
	/**
	* @brief Devolve o numero de empregados que trabalham na farmacia
	* @return Numero de empregados da farmacia
	*/
	unsigned int getNumEmpregados() const;
	/**
	* @brief Procura no stock o produto com o codigo indicado no seu parametro
	* Lanca uma excecao nao for encontrado nenhum produto com esse codigo em stock
	* @param codigo Codigo do produto a ser procurado em stock
	* @return Apontador para o produto com o codigo indicado no parametro
	*/
	pair<Produto*, unsigned int> getProduto(int codigo) const;

	/**
	* @brief Procura no stock o produto com o nome indicado no seu parametro
	* Lanca uma excecao nao for encontrado nenhum produto com esse nome em stock
	* @param nome nome do produto a ser procurado em stock
	* @return	  Apontador para o produto com o codigo indicado no parametro
	*/

	pair<Produto*, unsigned int> getProduto(string nome) const;


	/**
	 * @brief Obtem o vetor de vendas da farmacia
	 *
	 * @return Vetor de apontadores para vendas realizadas pela farmacia
	 */
	const vector<Venda *>& getVendas() const;

	/** 
	* @brief Devolve o numero total de produtos em stock, incluindo os produtos repetidos
	* @return Numero total de produtos em stock
	*/
	unsigned int getTotalProdutos() const;
	/**
	* @brief Devolve o numero de produtos diferentes em stock
	* @return Numero de produtos diferentes em stock
	*/
	unsigned int tamanhoStock() const;
	/**
	* @brief Devolve o numero de empregados na farmacia, incluindo o gerente
	* @return Numero de empregados da farmacia
	*/
	unsigned int numEmpregados() const;
	/**
	* @brief Devolve o numero total de vendas que foram realizadas nesta farmacia
	* @return Numero total de vendas
	*/
	unsigned int numVendas() const;

	/**
	* @brief Compara a igualdade de duas farmacia. Duas farmacias sao iguais se possuem o mesmo nome
	* @param ph1 Farmacia a ser comparada com o proprio objeto
	* @return True se as duas farmacias sao iguais. False se nao o sao
	*/
	bool operator == (const Farmacia & ph1) const;
	/**
	* @brief Compara a prioridade de duas farmacias. Uma farmacia tem prioridade sobre outra se o seu nome tiver prioridade alfabetica. 
	* Se as duas farmacias tem nomes iguais, a que tem prioridade e aquela com menor tamanho de stock
	* @param ph1 Farmacia a ser comparada com o proprio objeto
	* @return True se o proprio objeto e menor que a farmacia no seu parametro
	*/
	bool operator < (const Farmacia & ph1) const;

	/**
	* @brief Ordena a lista de empregados de acordo com o modo indicado no seu parametro
	* @param modo Modo no qual a lista de empregados vai ser ordenada
	*/
	void sortEmpregados(ord_pessoas modo);

	/**
	* @brief Escreve num ficheiro as informacoes relativas a farmacia para preservar esta informacao e ser posteriormente carregada
	*/
	ostream& printSimp(ostream& os) const;

	/**
	* @brief Mostra o nome e a morada da farmacia no ecra
	*/
	ostream& print(ostream& os) const;

	/**
	* @brief Mostra alguns atributos de todos os empregados da farmacia no ecra
	*/
	void mostrarEmpregados() const;
	/**
	* @brief Mostra alguns atributos de todos os produtos em stock no ecra e ainda as suas quantidades
	*/
	void mostrarStock() const;
	/**
	 * @brief Mostra vendas da farmacia no ecra
	 */
	void mostrarVendas() const;
	/**
	* @brief Mostra no ecra as quantidades em stock de todos os produtos 
	*/
	void consultarQuantidades() const;
	/**
	 * @brief Adiciona uma venda ao vetor de vendas da farmacia
	 */
	void addVenda(Venda* venda);

	//--------------------------------------------------------------------
	void constroiFilaPrioridade(uint quantidade_limite);

	void repoeStock(uint quantidade_limite, int quantidade_nova = -1);

	void esvaziaFilaReabastecimento();

	HeapStock getFilaReabastecimento();

	bool addFornecedor(Fornecedor* novo_fornecedor);
	bool removeFornecedor(Fornecedor * fornecedor);


	//--------------------------------------------------------------------

private:
	/**
	 * @brief Nome da farmacia
	 * 
	 */
	string nome;
	/**
	 * @brief Morada da farmacia
	 */
	Morada morada;
	/**
	 * @brief Apontador para o gerente da farmacia
	 */
	Empregado* gerente;
	/**
	 * @brief Vetor de apontadores para os empregados da farmacia
	 */
	vector< Empregado* > empregados;
	/**
	 * @brief Map que representa o stock da farmacia (key = apontador para produto, value = quantidade)
	 * 
	 */
	map< Produto *, unsigned int> stock;
	/**
	 * @brief Vetor de apontadores para vendas
	 */
	vector <Venda *> vendas;

	//--------------------------------------------------------------------
	vector<Encomenda> encomendas;
	HeapFornecedores fornecedores_medicamentos;
	HeapFornecedores fornecedores_produtos;
	HeapStock prioridade_reabastecimento;
	//--------------------------------------------------------------------
};

bool operator>(pair<Produto*, uint>& p1, pair<Produto*, uint>& p2);

bool operator==(pair<Produto*, uint>& p1, pair<Produto*, uint>& p2);



/**
* @brief Usada para ordenar a lista de farmacias da cadeia. Compara duas farmacias.
* @return True se a farmacia f1 tem nome menor do que a farmacia f2. Se os nomes sao iguais,
* retorna true se a farmacia f1 tem menor tamanho de stock do que a farmacia f2.
*/
bool farmacia_SortFunc_Nome_Crescente(Farmacia * f1, Farmacia * f2);

/**
* @brief Usada para ordenar a lista de farmacias da cadeia. Compara duas farmacias.
* @return True se a farmacia f1 tem nome maior do que a farmacia f2. Se os nomes sao iguais,
* retorna true se a farmacia f1 tem menor tamanho de stock do que a farmacia f2.
*/
bool farmacia_SortFunc_Nome_Decrescente(Farmacia *f1, Farmacia *f2);

/**
* @brief Usada para ordenar a lista de farmacias da cadeia. Compara duas farmacias.
* @return True se a farmacia f1 tem tamanho de stock menor do que a farmacia f2. Se os tamanhos de stock sao iguais,
* retorna true se a farmacia f1 tem menor nome do que a farmacia f2.
*/
bool farmacia_SortFunc_TamanhoStock_Crescente(Farmacia *f1, Farmacia *f2);

/**
* @brief Usada para ordenar a lista de farmacias da cadeia. Compara duas farmacias.
* @return True se a farmacia f1 tem tamanho de stock maior do que a farmacia f2. Se os tamanhos de stock sao iguais,
* retorna true se a farmacia f1 tem menor nome do que a farmacia f2.
*/
bool farmacia_SortFunc_TamanhoStock_Decrescente(Farmacia *f1, Farmacia *f2);

/**
* @brief Usada para ordenar a lista de farmacias da cadeia. Compara duas farmacias.
* @return True se a farmacia f1 tem numero de vendas menor do que a farmacia f2. Se o numeros de venas sao iguais,
* retorna true se a farmacia f1 tem menor nome do que a farmacia f2.
*/
bool farmacia_SortFunc_NumVendas_Crescente(Farmacia *f1, Farmacia *f2);

/**
* @brief Usada para ordenar a lista de farmacias da cadeia. Compara duas farmacias.
* @return True se a farmacia f1 tem numero de vendas maior do que a farmacia f2. Se o numeros de venas sao iguais,
* retorna true se a farmacia f1 tem menor nome do que a farmacia f2.
*/
bool farmacia_SortFunc_NumVendas_Decrescente(Farmacia *f1, Farmacia *f2);

/** @} */

#endif
