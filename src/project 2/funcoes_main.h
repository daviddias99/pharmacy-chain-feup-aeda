#ifndef FUNCOES_MAIN_H
#define FUNCOES_MAIN_H

#include "Cadeia.h"
#include "util.h"
using namespace std;

/*!
 * \file funcoes_main.h
 *
 * \author FEUP AEDA1819 MIEIC Turma5_G1
 * \author David Silva
 * \author Gaspar Pinheiro
 * \author Luis Cunha
 */

/** @defgroup funcoes_main funcoes_main
 * @{
 *
 * Funcoes usadas na interface do programa 
 */



/**
 * @brief Maximum stream size - used in istream::ignore()
 */
const long long MAX_STREAM_SIZE = numeric_limits<streamsize>::max();

/**
 * @brief Devolve uma morada lida do utilizador
 * 
 * @return Morada lida do utilizador
 */
Morada user_getMorada();
/**
 * @brief Le uma data do utilizador
 *
 * @param pergunta	Mensagem a apresentar ao utilizador quando pede para introduzir uma data
 * @param respErro	Mensagem a apresentar ao utilizador caso ele introduza uma data invalida
 * @param nasc		True caso a data seja de nascimento
 * @return Data lida do utilizador
 */
Data user_getData(string pergunta, string respErro, bool nasc);

/**
 * @brief Le um empregado do utilizador
 * 
 * @param cadeia        Cadeia para a qual se quer ler um empregado de modo a nao permitir que o utilizador indique um empregado com NIF  que ja existe
 * @param newFOverride  Se newFOverride for true significa que esta a ler um empregado para ser gerente de uma nova farmacia,
 * pelo que nao precisa de perguntar ao utilizador pelo cargo nem pela farmacia
 *
 * @return Apontador para o empregado lido do utilizador
 */
Empregado* user_getEmpregado(Cadeia& cadeia, pair<bool, string> newFOverride = { false, "nome_default" });
/**
 * @brief Le um cliente do utilizador
 * 
 * @return Apontador para o cliente lido do utilizador 
 */
Cliente* user_getCliente();

/**
 * @brief Le um fornecedor do utilizador
 *
 * @return Apontador para o fornecedor lido do utilizador
 */
Fornecedor* user_getFornecedor();


/**
 * @brief Le produto do utilizador
 * 
 * @param farmacia Farmacia para a qual se esta a ler um produto de modo a nao permitir que o utilizador nao indique um produto que ja exista
 * @return Apontador para o produto introduzido pelo utilizador
 */
Produto* user_getProduto(Farmacia& farmacia);
/**
 * @brief Le nome da receita do utilizador e se a encontrar adiciona a venda passada por argumento os produtos da receita, caso
 * a farmacia tenha capacidade para tal
 * 
 * @param farmacia Farmacia que deve fornecer os produtos para aviar a receita
 * @param venda Venda a qual se deve adicionar os produtos da receita
 */
void user_addReceita(Farmacia* farmacia, Venda* venda);
/**
 * @brief Pede ao utilizador para adicionar produtos a venda
 * 
 * @param farmacia Farmacia que deve fornecer os produtos para adicionar a venda
 * @param venda Venda a qual se deve adicionar produtos
 */
void user_getProdutos(Farmacia* farmacia, Venda* venda);
/**
 * @brief Le um numero do utilizador, verificando que o input e valido
 * 
 * @param limInf limite inferior da gama valida de inteiros introduzidos
 * @param limSup limite superior da gama valida de inteiros introduzidos
 * @param showLimSup Se for false, mostra apenas o limite inferior
 * @return Inteiro lido do utilizador
 */
int getInputNumber(int limInf, int limSup, bool showLimSup = true);
/**
 * @brief Le uma string do utilizador, verificando que o input e valido
 * 
 * @param msg Mensagem a apresentar ao utilizador para pedir que ele introduza a string
 * @param msgErr Mensagem a apresentar ao utilizador caso a string seja invalida
 * @return string lida do utilizador
 */
string getInputString(string msg, string msgErr);

/**
 * @brief Mostra menu inicial do programa de gestao de farmacias
 */
void showMenuInicial();
/**
 * @brief Mostra o menu principal do programa de gestao de farmacias
 */
void showMenuPrincipal();

/**
 * @brief Funcao utilizada para realizar vendas na cadeia passada como argumento
 * 
 * @param cadeia Cadeia onde a venda vai ser realizada
 */
void realizarVenda(Cadeia& cadeia);

/**
 * @brief Menu que mostra ao utilizador as diferentes acoes que ele pode fazer sobre os clientes
 * 
 * @param cadeia Cadeia cujos clientes vao ser utilizados
 */
void menuClientes(Cadeia& cadeia);
/**
 * @brief Mostra no ecra um resumo dos clientes que fazem parte da cadeia passada como argumento
 * 
 * @param cadeia Cadeia cujos clientes sao consultados
 */
void resumoClientes(Cadeia& cadeia);
/**
 * @brief Mostra no ecra as compras efetuadas pelo cliente
 * 
 * @param c Cliente cujas compras sao consultadas
 */
void cliente_consultarCompras(Cliente* c);
/**
 * @brief Funcao que mostra ao utilizador as acoes que pode fazer sobre um cliente especifico da cadeia
 * 
 * @param cadeia Cadeia cujo cliente sera consultado
 */
void gerirCliente(Cadeia& cadeia);

/**
 * @brief Menu que permite ao utilizador escolher entre as acoes disponiveis sobre os empregados da cadeia
 * 
 * @param cadeia Cadeia que contem os empregados com os quais vamos trabalhar
 */
void menuEmpregados(Cadeia& cadeia);
/**
 * @brief Mostra no ecra um resumo das informacoes dos empregados da cadeia
 * 
 * @param cadeia Cadeia que contem os empregados que serao mostrados
 */
void resumoEmpregados(Cadeia& cadeia);
/**
 * @brief Adicionar um empregado a cadeia passada como argumento
 * 
 * @param cadeia Cadeia a qual se quer adicionar um empregado
 */
void adicionarEmpregado(Cadeia& cadeia);
/**
* @brief Recontratar um empregado com ligacao anterior a cadeia de farmacias
*
* @param	cadeia	Cadeia na qual se pretende recontratar um empregado
*/
void recontratarEmpregado(Cadeia& cadeia);
/**
 * @brief Despedir um empregado da cadeia passada como argumento
 * 
 * @param cadeia Cadeia da qual se quer remover um empregado
 */
void despedirEmpregado(Cadeia& cadeia);
/**
* @brief Consultar os empregados sem contrato da cadeia de farmacias
*
* @param cadeia Cadeia da qual se prentende consultar os empregados sem contrato
*/
void consultarEmpregadosSemContrato(Cadeia & cadeia);
/**
 * @brief Funcao que permite gerir atributos de um empregado e consultar as suas vendas
 * 
 * @param cadeia Cadeia cujos empregados se pretende gerir
 */
void gerirEmpregado(Cadeia& cadeia);

/**
 * @brief Menu que apresenta e permiter ao utilizador realizar as acoes disponiveis sobre os fornecedores de uma cadeia
 *
 * @param cadeia Cadeia cujaos fornecedores se pretende gerir
 */
void menuFornecedores(Cadeia& cadeia);

/**
 * @brief Mostra no ecra um resumo das informacoes dos fornecedores de uma cadeia
 *
 * @param cadeia        Cadeia que contem os fornecedores cujas informacoes se pretende consultar
 */
void resumoFornecedores(Cadeia& cadeia);

/**
 * @brief Funcao que permite ao utilizador adicionar um fornecedor a cadeia
 *
 * @param cadeia        Cadeia onde se pretende adicionar o fornecedor
 */
void adicionarFornecedor(Cadeia& cadeia);


/**
 * @brief Funcao que permite ao utilizador adicionar um fornecedor a cadeia
 *
 * @param cadeia        Cadeia onde se pretende adicionar o fornecedor
 */
void consultarFornecedor(Cadeia& cadeia);

/**
 * @brief Menu que apresenta e permiter ao utilizador realizar as acoes disponiveis sobre as farmacias de uma cadeia
 * 
 * @param cadeia Cadeia cujas farmacias se pretende gerir
 */
void menuFarmacias(Cadeia& cadeia);
/**
 * @brief Mostra no ecra um resumo das informacoes das farmacias de uma cadeia
 * 
 * @param cadeia        Cadeia que contem as farmacias cujas informacoes se pretende consultar
 */
void resumoFarmacias(Cadeia& cadeia);
/**
 * @brief Funcao que permite ao utilizador adicionar uma farmacia a cadeia, tendo para isso que criar um novo gerente
 * 
 * @param cadeia        Cadeia onde se pretende adicionar a farmacia
 */
void adicionarFarmacia(Cadeia& cadeia);
/**
* @brief Ordena um vetor de empregados pelo modo especificado
*
* @param	empregados		vetor de empregados a ordenar
* @param	modo			modo de ordenacao
*/
void sortEmpregados(vector<Empregado*>& empregados, ord_empregados modo);

/**
 * @brief Funcao que permite consultar todas as informaçoes acerca de uma farmacia(a escolher pelo user). Sendo elas, os empregados, os protdutos e as vendas
 * 
 * @param cadeia        cadeia que contem a farmacia se pretende consultar
 */
void consultarFarmacia(Cadeia& cadeia);

/**
 * @brief Função que permite gerir o Stock de uma farmacia da cadeia a escolher pelo user. E possivel adicionar produtos, remover 
 * produtos, ou simplesmente consultar informaçao acerca dos produtos existentes
 * 
 * @param cadeia       cadeia que contem a farmacia cujo stock se pretende gerir 
 */
void gerirStock(Cadeia& cadeia);

/**
 * @brief Alterar o gerente de uma farmacia a escolher pelo user para outro empregado dessa mesma farmacia. A função atribui
 * um cargo escolhido pelo user para o gerente antigo
 * 
 * @param cadeia    cadeia que contem a farmacia cujo gerente se pretende mudar
 */
void farmacia_alterarGerente(Cadeia& cadeia);
/**
 * @brief Consultar vendas realizadas nume determinada farmacia
 * 
 * @param farmacia Farmacia cujas vendas se pretende consultar
 */
void farmacia_consultarVendas(Farmacia& farmacia);
/**
 * @brief Consultar empregados de uma determina farmacia
 * 
 * @param farmacia Farmacia cujos empregados se pretende consultar
 */
void farmacia_consultarEmpregados(Farmacia& farmacia);
/**
 * @brief Consultar produtos de uma determinada farmacia
 * 
 * @param farmacia Farmacia cujos produtos se pretende consultar
 */
void farmacia_consultarProdutos(Farmacia& farmacia);
/**
 * @brief Adicionar produtos a uma determinada farmacia
 * 
 * @param farmacia Farmacia a qual pretendemos adicionar produtos
 */
void farmacia_adicionarProduto(Farmacia& farmacia);
/**
 * @brief Remover produtos de uma determinada farmacia
 * 
 * @param farmacia Farmacia da qual pretendemos remover produtos
 */
void farmacia_removerProduto(Farmacia& farmacia);

/**
 * @brief Funcao usada para executar o utilitario de adicionar um fornecedor a uma farmacia.
 * 
 * @param cadeia        cadeia que contem a  farmacia a alterar
 */
void farmacia_adicionarFornecedor(Cadeia& cadeia);

/**
 * @brief Funcao usada para executar o utilitario de remover um fornecedor a uma farmacia.
 * 
 * @param cadeia           cadeia que contem a  farmacia a alterar
 */
void farmacia_removerFornecedor(Cadeia& cadeia);

/**
 * @brief Funcao usada para executar o utilitario de consultar os fornecedores de uma farmacia.
 * 
 * @param farmacia          farmacia a consultar
 */
void farmacia_consultaFornecedores(Farmacia& farmacia);

/**
 * @brief Funcao usada para executar o utilitario de repor o stock de uma farmacia.
 * 
 * @param farmacia          farmacia onde o stock sera reposto
 */
void farmacia_reposicaoStock(Farmacia& farmacia);

/**
 * @brief Executa a operação de consultar encomendas de um fornecedor. As encomendas sao encontradas atraves da data da sua realizacao.
 * 
 * @param fornecedor        fornecedor a consultar
 */
void fornecedor_consultarEncomendaData(Fornecedor& fornecedor);


/**
 * @brief Executa a operação de consultar encomendas de um fornecedor. As encomendas sao encontradas atraves da farmacia de onde originaram.
 *
 * @param fornecedor        fornecedor a consultar
 */
void fornecedor_consultarEncomendaFarmacia(Fornecedor& fornecedor);

/**
 * @brief Consultar os produtos da farmacia, em forma de lista, ordenados pela prioridade com que devem ser encomendados
 *
 * @param farmacia Farmacia cujas vendas se pretende consultar
 */
void farmacia_verPrioridadeEncomendas(Farmacia& farmacia);

/** @} */

#endif
