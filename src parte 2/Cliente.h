#ifndef CLIENTE_H
#define CLIENTE_H

#include "Pessoa.h"


/*!
 * \file Cliente.h
 *
 * \author FEUP AEDA1819 MIEIC Turma5_G1
 * \author David Silva
 * \author Gaspar Pinheiro
 * \author Luis Cunha
 */


/** @defgroup Pessoa Pessoa
 * @{
 *
 * Classe pessoa e suas classes derivadas
 */


/**
 * Classe que representa uma pessoa
 */
class Cliente :public Pessoa {
public:
	/**
	* @brief Construtor da classe cliente
	* @param nome Nome do cliente
	* @param nif NIF do cliente. E zero se nao for indicado
	* @param dataNasc Data de nascimento do cliente
	* @param morada Morada atual do cliente
	* @param distrito Distrito de residencia do cliente
	*/
	Cliente(string nome = "NOME_DEFAULT", uint nif = 0, Data dataNasc = Data(), Morada morada = Morada(), string distrito = "");

	/**
	* @brief Adiciona a venda indicada no seu parametro a lista de compras do cliente
	* @param v Apontador para uma venda relizada pelo cliente
	* @return true se a venda foi adicionada com sucesso a lista de compras
	* false se ocorreu algum erro
	*/
	bool adicionaCompra(Venda* v);

	/**
	* @brief Mostra no ecra a lista de compras do cliente
	*/
	void mostrarCompras();

	/**
	* @brief Devolve o numero de compras efetuadas pelo cliente
	* @return Numero de compras efetuadas pelo cliente
	*/
	uint getNumCompras() const;

	/**
	* @brief Devolve o membro-dado distrito do cliente
	* @return Distrito de residencia do cliente
	*/
	string getDistrito() const;

	/**
	* @brief Altera o distrito atual do cliente
	* @param distrito Novo distrito de residencia do cliente
	*/
	void setDistrito(string distrito);

	/**
	 * @brief Imprime as informacoes do cliente num formato legivel
	 * 
	 * @param os Stream onde sao imprimidas as informacoes
	 * @return Stream onde foram imprimidas as informacoes
	 */
	ostream& print(ostream& os) const;

	/**
	 * @brief Imprime as informacoes do cliente num formato simplificado, utilizado para guardar informacoes das pessoas em ficheiro de texto
	 * 
	 * @param os Stream onde sao imprimidas as informacoes
	 * @return Stream onde foram imprimidas as informacoes
	 */
	ostream& printSimp(ostream& os) const;

	/**
	* @brief Overload do operador <, os clientes sao comparados por NIF
	*
	* @param c1 Cliente na esquerda do operador
	* @param c2 Cliente na direita do operador
	* @return True caso o NIF do cliente da esquerda seja menor que o NIF do da direita
	*/
	friend bool operator<(const  Cliente& c1, const Cliente & c2);

	/**
	 * @brief Overload do operador ==, os clientes sao comparados por NIF
	 *
	 * @param c1 Cliente na esquerda do operador
	 * @param c2 Cliente na direita do operador
	 * @return True caso o NIF do cliente da esquerda seja igual ao NIF do da direita
	 */
	friend bool operator==(const  Cliente& c1, const Cliente & c2);

private:
	/**
	 * @brief Vector de apontadores para vendas, que guarda o historico de compras do cliente
	 */
	vector<Venda*> historicoCompras;

	/**
	* @brief Distrito de residencia do cliente
	*/
	string distrito;
};

/**
* @brief Usada para ordenar a lista de clientes da cadeia. Compara dois clientes
* @return True se o cliente p1 tem distrito menor do que o cliente p2. Se os distritos sao iguais,
* retorna true se o nome de p1 e menor do que o nome de p2
*/
bool Cliente_SortFunc_Distrito_Crescente(Cliente* p1, Cliente* p2);

/**
* @brief Usada para ordenar a lista de clientes da cadeia. Compara dois clientes
* @return True se o cliente p1 tem distrito maior do que o cliente p2. Se os distritos sao iguais, 
* retorna true se o nome de p1 e menor do que o nome de p2
*/
bool Cliente_SortFunc_Distrito_Decrescente(Cliente* p1, Cliente* p2);

/**
* @brief Usada para ordenar a lista de clientes da cadeia. Compara dois clientes
* @return True se o cliente p1 fez menos compras do que o cliente p2. Se os numeros de compras sao iguais,
* retorna true se o nome de p1 e menor do que o nome de p2
*/
bool Cliente_SortFunc_numCompras_Crescente(Cliente* p1, Cliente* p2);

/**
* @brief Usada para ordenar a lista de clientes da cadeia. Compara dois clientes
* @return True se o cliente p1 fez mais compras do que o cliente p2. Se os numeros de compras sao iguais,
* retorna true se o nome de p1 e menor do que o nome de p2
*/
bool Cliente_SortFunc_numCompras_Decrescente(Cliente* p1, Cliente* p2);


/** @} */

#endif // !CLIENTE_H
