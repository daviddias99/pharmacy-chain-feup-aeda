#include "Farmacia.h"

Farmacia::Farmacia(string nome, Morada morada) :nome(nome), morada(morada) {}

Farmacia::Farmacia(string simp)
{
	string linha, nome_prod, desc_prod, produtoSimp;
	uint quant;

	float preco_prod, iva_prod, desc_receita;
	unsigned long int cod_produto;
	bool vend_sem_rec, pode_ser_rec;

	linha = simp;
	this->nome = linha.substr(0, linha.find_first_of('\\'));
	linha = linha.substr(linha.find_first_of('\\') + 1);
	this->morada = Morada(linha.substr(0, linha.find_first_of('\\')));
	linha = linha.substr(linha.find_first_of('\\') + 1);
	this->fornecedoresStringFicheiro = linha.substr(0, linha.find_first_of('\\'));
	linha = linha.substr(linha.find_first_of('\\'));

	if (linha != "\\") {
		while (linha != "!") {
			linha = linha.substr(1);
			produtoSimp = linha.substr(0, linha.find_first_of('#'));
			quant = stoul(linha.substr(linha.find_first_of('#') + 1, linha.find_first_of('!')));
			linha = linha.substr(linha.find_first_of('!'));

			bool isMed = false;
			if (count(produtoSimp.begin(), produtoSimp.end(), '&') > 4)
				isMed = true;

			cod_produto = stoul(produtoSimp.substr(0, produtoSimp.find_first_of('&')));
			produtoSimp = produtoSimp.substr(produtoSimp.find_first_of('&') + 1);
			nome_prod = produtoSimp.substr(0, produtoSimp.find_first_of('&'));
			produtoSimp = produtoSimp.substr(produtoSimp.find_first_of('&') + 1);
			desc_prod = produtoSimp.substr(0, produtoSimp.find_first_of('&'));
			produtoSimp = produtoSimp.substr(produtoSimp.find_first_of('&') + 1);
			preco_prod = stof(produtoSimp.substr(0, produtoSimp.find_first_of('&')));
			produtoSimp = produtoSimp.substr(produtoSimp.find_first_of('&') + 1);
			iva_prod = stof(produtoSimp.substr(0, produtoSimp.find_first_of('&')));


			if (!isMed) {
				stock.insert(pair<Produto *, uint>(new Produto(cod_produto, nome_prod, desc_prod, preco_prod, iva_prod), quant));
			}
			else {
				produtoSimp = produtoSimp.substr(produtoSimp.find_first_of('&') + 1);
				vend_sem_rec = stoi(produtoSimp.substr(0, produtoSimp.find_first_of('&')));
				produtoSimp = produtoSimp.substr(produtoSimp.find_first_of('&') + 1);
				pode_ser_rec = stoi(produtoSimp.substr(0, produtoSimp.find_first_of('&')));
				produtoSimp = produtoSimp.substr(produtoSimp.find_first_of('&') + 1);
				desc_receita = stof(produtoSimp.substr(0, produtoSimp.find_first_of('&')));

				stock.insert(pair<Produto *, uint>(new Medicamento(cod_produto, nome_prod, desc_prod, preco_prod, iva_prod, vend_sem_rec, pode_ser_rec, desc_receita), quant));
			}
		}
	}
}

Farmacia::~Farmacia()
{
	map< Produto *, uint>::const_iterator it;

	for (it = stock.begin(); it != stock.end(); it++)
		delete it->first;
	for (size_t i = 0; i < this->vendas.size(); i++)
		delete this->vendas.at(i);
}

void Farmacia::addProduto(Produto *produto, int quantidade)
{
	map<Produto *, unsigned int>::iterator it;
	for (it = stock.begin(); it != stock.end(); it++) {
		if (*(it->first) == *produto) {
			it->second += quantidade;
			this->constroiFilaReabastecimento();
			return;
		}
	}

	stock[produto] = quantidade;
	this->constroiFilaReabastecimento();
}

bool Farmacia::addEmpregado(Empregado* empregado)
{	
	if (!empregados.insert(empregado).second) return false;

	if (empregado->getCargo() == "gerente") {
		if (gerente != NULL)
			cout << "O cargo do antigo gerente " << gerente->getNome() << " passou para empregado." << endl;
		setGerente(empregado, "empregado");
	}

	return true;
}

void Farmacia::removeQuantidade(long unsigned int codigo, uint quantidade)
{
	map<Produto*, unsigned int>::iterator it;
	for (it = stock.begin(); it != stock.end(); it++) {
		if (it->first->getCodigo() == codigo) {
			if (it->second <= quantidade) {
				throw ProdutosInsuficientes("Apenas existem " + to_string(it->second) + " unidades do referido produto.");
			}
			else {
				it->second -= quantidade;
				this->constroiFilaReabastecimento();
				return;
			}
		}
	}
	throw ProdutoNaoExiste("O produto com o codigo " + to_string(codigo) + " nao existe.");
}

void Farmacia::remProduto(long unsigned int codigo)
{
	map<Produto *, unsigned int>::iterator it;
	for (it = stock.begin(); it != stock.end(); it++) {
		if ((*it->first).getCodigo() == codigo) {
			Produto* prod = it->first;
			stock.erase(it);
			delete prod;
			this->constroiFilaReabastecimento();
			return;
		}
	}
	throw ProdutoNaoExiste("O produto com o codigo " + to_string(codigo) + " nao existe.");
}

void Farmacia::remEmpregado(uint ID)
{
	// TO DO

	/*
	int i = procura(this->empregados, ID);

	if (i != -1) {
		empregados.erase(empregados.begin() + i);
		sort(empregados.begin(), empregados.end(), Empregado_SortFunc_ID_Crescente);
	}
	else throw ClienteNaoExiste("O cliente com o ID " + to_string(ID) + " nao existe");*/

}

bool Farmacia::setGerente(Empregado * novoGerente, string novoCargo)
{
	if (this->gerente != NULL)
		this->gerente->setCargo(novoCargo);
	novoGerente->setCargo("gerente");
	this->gerente = novoGerente;

	return true;
}

void Farmacia::addQuantidade(long unsigned int codigo, uint quantidade)
{
	map<Produto*, unsigned int>::iterator it;
	for (it = stock.begin(); it != stock.end(); it++) {
		if (it->first->getCodigo() == codigo) {
			it->second += quantidade;
			this->constroiFilaReabastecimento();
			return;
		}
	}
	throw ProdutoNaoExiste("O produto com o codigo " + to_string(codigo) + " nao existe.");
}

bool Farmacia::existeProduto(unsigned long int codigo)
{
	for (map<Produto *, unsigned int>::const_iterator it = stock.begin(); it != stock.end(); it++) {
		if (it->first->getCodigo() == codigo)
			return true;
	}

	return false;
}

string Farmacia::getNome() const
{
	return nome;
}

Morada Farmacia::getMorada() const
{
	return morada;
}

Empregado* Farmacia::getGerente() const
{
	return gerente;
}

vector<Empregado*> Farmacia::getEmpregados(string nome) const
{
	vector<Empregado*> v1;
	vector<Empregado*>::const_iterator it;

	for (empregadoHashTable::const_iterator it = empregados.begin(); it != empregados.end(); it++) {
		if ((*it)->getNome() == nome) v1.push_back(*it);
	}

	return v1;
}

vector<Fornecedor*> Farmacia::getFornecedores() const
{
	return this->fornecedores;
}

Fornecedor * Farmacia::getFornecedor(string nome) const
{
	int fornecedorPos = procura(this->fornecedores, nome);

	if (fornecedorPos == -1)
		throw FornecedorNaoExiste("O fornecedor com o nome " + nome +" nao existe");
	else
		return fornecedores.at(fornecedorPos);

	return NULL;
}

unsigned int Farmacia::getNumEmpregados() const
{
	return empregados.size();
}

pair<Produto*, unsigned int> Farmacia::getProduto(int codigo) const
{
	map<Produto*, unsigned int>::const_iterator it;
	for (it = stock.begin(); it != stock.end(); it++) {
		if ((*it->first).getCodigo() == codigo)
			return *it;
	}
	throw ProdutoNaoExiste("O produto com o codigo " + to_string(codigo) + " nao existe.");
}

pair<Produto*, unsigned int> Farmacia::getProduto(string nome) const
{
	map<Produto*, unsigned int>::const_iterator it;
	for (it = stock.begin(); it != stock.end(); it++) {
		if ((*it->first).getNome() == nome)
			return *it;
	}
	throw ProdutoNaoExiste("O produto com o nome " + nome + " nao existe.");
}

const vector<Venda*>& Farmacia::getVendas() const
{
	return vendas;
}

unsigned int Farmacia::getTotalProdutos() const
{
	int soma = 0;
	map<Produto*, unsigned int>::const_iterator it;
	for (it = stock.begin(); it != stock.end(); it++) {
		soma += it->second;
	}
	return soma;
}

string Farmacia::getFornecedoresStr() const
{
	return this->fornecedoresStringFicheiro;
}

bool Farmacia::operator == (const Farmacia & ph1) const
{
	if (this->nome == ph1.getNome()) return true;
	else return false;
}

bool Farmacia::operator < (const Farmacia & ph1) const
{
	if (this->nome < ph1.getNome())
		return true;
	else if (this->nome == ph1.getNome())
	{
		if (this->tamanhoStock() < ph1.tamanhoStock())
			return true;
		else
			return false;
	}
	else
		return false;
}

void Farmacia::consultarQuantidades() const
{
	map<Produto*, unsigned int>::const_iterator it;
	for (it = stock.begin(); it != stock.end(); it++) {
		cout << "Nome: " << (*it->first).getNome() << "; Codigo: " << (*it->first).getCodigo() << "; Quantidade: " << it->second << endl;;
	}
}

void Farmacia::addVenda(Venda * venda)
{
	vendas.push_back(venda);
}


void Farmacia::constroiFilaReabastecimento()
{
	if (!this->prioridade_reabastecimento.empty())
		this->esvaziaFilaReabastecimento();


	map<Produto*, uint>::iterator it = this->stock.begin();
	map<Produto*, uint>::iterator ite = this->stock.end();

	while (it != ite) {

		pair<Produto*, uint> current = *it;

		this->prioridade_reabastecimento.push(current);

		it++;
	}

}

HeapStock Farmacia::getFilaReabastecimento()
{
	return this->prioridade_reabastecimento;
}

bool Farmacia::addFornecedor(Fornecedor * novo_fornecedor)
{
	if (procura(this->fornecedores, novo_fornecedor->getNome()) != -1)
		return false;

	if (novo_fornecedor->getTipo() == medicamentos) {
		this->fornecedores.insert(fornecedores.begin(), novo_fornecedor);
		this->fornecedores_medicamentos.push(novo_fornecedor);
	}
	else if (novo_fornecedor->getTipo() == produtos) {
		this->fornecedores.insert(fornecedores.begin(), novo_fornecedor);
		this->fornecedores_produtos.push(novo_fornecedor);
	}
	else {

		return false;
	}

	sort(this->fornecedores.begin(), this->fornecedores.end(), fornecedor_SortFunc_Nome_Crescente);

	return true;
}

bool Farmacia::removeFornecedor(Fornecedor * fornecedor) {

	HeapFornecedores novoHeap;
	HeapFornecedores* heap_a_alterar;

	// guardar heap a alterar
	if (fornecedor->getTipo() == produtos)
		heap_a_alterar = &this->fornecedores_produtos;
	else if (fornecedor->getTipo() == medicamentos)
		heap_a_alterar = &this->fornecedores_medicamentos;
	else
		return false;

	// esvaziar heap, preenchendo o novo heap (nao adicionando o fornecedor a remover)
	while (!heap_a_alterar->empty()) {

		Fornecedor* atual = heap_a_alterar->top();
		heap_a_alterar->pop();

		if (atual->getNome() != fornecedor->getNome())
			novoHeap.push(atual);

	}

	for (unsigned int i = 0; i < this->fornecedores.size(); i++) {

		if (fornecedores.at(i) == fornecedor) {
			fornecedores.erase(fornecedores.begin() + i);
			break;
		}
	}

	// colocar heap novo;
	*heap_a_alterar = novoHeap;

	return true;

}

ostream & Farmacia::print_lista_fornecedores(ostream & os)
{
	for (size_t i = 0; i < this->fornecedores.size(); i++) {

		fornecedores.at(i)->print_resumo_lista(os);
	}
	cout << endl;

	return os;
}

bool Farmacia::temFornecedorMed()
{
	return !this->fornecedores_medicamentos.empty();
}

bool Farmacia::temFornecedorProd()
{
	return !this->fornecedores_produtos.empty();
}

void Farmacia::esvaziaFilaReabastecimento()
{
	while (!this->prioridade_reabastecimento.empty())
		this->prioridade_reabastecimento.pop();
}

pair<string,string> Farmacia::repoeStock(uint quantidade_limite, int quantidade_nova) {

	// criar resultado

	pair<string, string> resultado = { "NULL","NULL" };

	// obter o fornecedor de cada tipo
	Fornecedor* fornecedor_produtos = fornecedores_produtos.top();
	fornecedores_produtos.pop();
	Fornecedor* fornecedor_medicamentos = fornecedores_medicamentos.top();
	fornecedores_medicamentos.pop();

	// criar duas novas encomendas
	Encomenda encomendaProdutos(this->getNome(), fornecedor_produtos->getNome());
	Encomenda encomendaMedicamentos(this->getNome(), fornecedor_medicamentos->getNome());


	if (this->prioridade_reabastecimento.empty())
		return resultado;

	while ((!this->prioridade_reabastecimento.empty()) && (this->prioridade_reabastecimento.top().second < quantidade_limite)) {

		// produto atual
		pair<Produto*, uint> produtoTemp = prioridade_reabastecimento.top();
		prioridade_reabastecimento.pop();

		// verificar que tipo de produto se trata
		Medicamento* mediTemp = dynamic_cast<Medicamento*> (produtoTemp.first);

		if (mediTemp != NULL) {

			// criar entrada na encomenda com a quantidade necessaria
			if ((quantidade_nova == -1) || ((uint) quantidade_nova < quantidade_limite))
				encomendaMedicamentos.adicionaProduto(produtoTemp.first, quantidade_limite - produtoTemp.second);
			else
				encomendaMedicamentos.adicionaProduto(produtoTemp.first, quantidade_nova - produtoTemp.second);
		}
		else {

			// criar entrada na encomenda com a quantidade necessaria
			if ((quantidade_nova == -1) || ((uint) quantidade_nova < quantidade_limite))
				encomendaProdutos.adicionaProduto(produtoTemp.first, quantidade_limite - produtoTemp.second);
			else
				encomendaProdutos.adicionaProduto(produtoTemp.first, quantidade_nova - produtoTemp.second);

		}

	}

	// atualizar stock da farmacia
	ListaProdutos produtos = encomendaProdutos.getProdutos();
	ListaProdutos::iterator itp = produtos.begin();
	ListaProdutos::iterator itep = produtos.end();

	while (itp != itep) {

		Produto* current = itp->first;
		uint quantidade = itp->second;

		// atualiza tanto o vetor stock como a fila de prioridade
		this->addProduto(current, quantidade);
		//this->prioridade_reabastecimento.push(this->getProduto(current->getCodigo()));
		itp++;
	}

	ListaProdutos medicamentos = encomendaMedicamentos.getProdutos();
	ListaProdutos::iterator itm = medicamentos.begin();
	ListaProdutos::iterator item = medicamentos.end();

	while (itm != item) {

		Produto* current = itm->first;
		uint quantidade = itm->second;

		// atualiza tanto o vetor stock como a fila de prioridade
		this->addProduto(current, quantidade);
		//this->prioridade_reabastecimento.push(this->getProduto(current->getCodigo()));
		itm++;
	}

	// adicionar registo das encomendas ao fornecedor e � farmacia
	// terminar encomenda parar registar o timestamp

	if (!medicamentos.empty()) {

		encomendaMedicamentos.terminaEncomenda();
		fornecedor_medicamentos->satisfazEncomenda(encomendaMedicamentos);
		resultado.second = fornecedor_medicamentos->getNome();
		//this->encomendas.push_back(encomendaMedicamentos);
	}

	if (!produtos.empty()) {

		encomendaProdutos.terminaEncomenda();
		fornecedor_produtos->satisfazEncomenda(encomendaProdutos);
		resultado.first = fornecedor_produtos->getNome();
		//this->encomendas.push_back(encomendaProdutos);
	}

	// readicionar os fornecedores aos heaps
	fornecedores_produtos.push(fornecedor_produtos);
	fornecedores_medicamentos.push(fornecedor_medicamentos);
	return resultado;
}

string Farmacia::efetuaEncomenda(Produto * produto, uint quantidade)
{

	// verificar que tipo de produto se trata
	Medicamento* mediTemp = dynamic_cast<Medicamento*> (produto);
	Fornecedor*  fornecedor;

	if (mediTemp != NULL) {

		fornecedor = fornecedores_medicamentos.top();
		fornecedores_medicamentos.pop();
	}
	else {

		fornecedor = fornecedores_produtos.top();
		fornecedores_produtos.pop();
	}

	// criar uma nova encomenda
	Encomenda encomenda(this->getNome(), fornecedor->getNome());

	encomenda.adicionaProduto(produto, quantidade);


	this->addProduto(produto, quantidade);
	//this->prioridade_reabastecimento.push(this->getProduto(produto->getCodigo()));


	// adicionar registo das encomendas ao fornecedor e � farmacia
	// terminar encomenda parar registar o timestamp

	if (mediTemp != NULL) {

		encomenda.terminaEncomenda();
		fornecedor->satisfazEncomenda(encomenda);
		//this->encomendas.push_back(encomenda);
		fornecedores_medicamentos.push(fornecedor);
	}
	else {

		encomenda.terminaEncomenda();
		fornecedor->satisfazEncomenda(encomenda);
		//this->encomendas.push_back(encomenda);
		fornecedores_produtos.push(fornecedor);
	}

	return fornecedor->getNome();
}


unsigned int Farmacia::numEmpregados() const
{
	return empregados.size();
}

unsigned int Farmacia::tamanhoStock() const
{
	return stock.size();
}

unsigned int Farmacia::numVendas() const
{
	return vendas.size();
}

bool operator<(pair<Produto*, uint>& p1, pair<Produto*, uint>& p2)
{
	return p1.second > p2.second;
}

bool operator==(pair<Produto*, uint>& p1, pair<Produto*, uint>& p2)
{
	return p1.first->getCodigo() == p2.first->getCodigo();
}

bool farmacia_SortFunc_Nome_Crescente(Farmacia * f1, Farmacia * f2)
{
	if (f1->getNome() < f2->getNome())
		return true;
	else if (f1->getNome() == f2->getNome())
	{
		if (f1->tamanhoStock() < f2->tamanhoStock())
			return true;
		else
			return false;
	}
	else
		return false;
}

bool farmacia_SortFunc_Nome_Decrescente(Farmacia * f1, Farmacia * f2)
{
	if (f1->getNome() > f2->getNome())
		return true;
	else if (f1->getNome() == f2->getNome())
	{
		if (f1->tamanhoStock() < f2->tamanhoStock())
			return true;
		else
			return false;
	}
	else
		return false;
}

bool farmacia_SortFunc_TamanhoStock_Crescente(Farmacia * f1, Farmacia * f2)
{
	if (f1->tamanhoStock() < f2->tamanhoStock())
		return true;
	else if (f1->tamanhoStock() == f2->tamanhoStock())
	{
		if (f1->getNome() < f2->getNome())
			return true;
		else
			return false;
	}
	else
		return false;
}

bool farmacia_SortFunc_TamanhoStock_Decrescente(Farmacia * f1, Farmacia * f2)
{
	if (f1->tamanhoStock() > f2->tamanhoStock())
		return true;
	else if (f1->tamanhoStock() == f2->tamanhoStock())
	{
		if (f1->getNome() < f2->getNome())
			return true;
		else
			return false;
	}
	else
		return false;
}

bool farmacia_SortFunc_NumVendas_Crescente(Farmacia *f1, Farmacia *f2)
{
	if (f1->numVendas() > f2->numVendas())
		return true;
	else if (f1->numVendas() == f2->numVendas())
	{
		if (f1->getNome() < f2->getNome())
			return true;
		else
			return false;
	}
	else
		return false;
}

bool farmacia_SortFunc_NumVendas_Decrescente(Farmacia *f1, Farmacia *f2)
{
	if (f1->numVendas() < f2->numVendas())
		return true;
	else if (f1->numVendas() == f2->numVendas())
	{
		if (f1->getNome() > f2->getNome())
			return true;
		else
			return false;
	}
	else
		return false;
}


ostream& Farmacia::printSimp(ostream& os) const {

	os << nome << "\\";
	morada.printSimp(os);
	os << "\\";

	for (size_t i = 0; i < this->fornecedores.size(); i++) {

		os << this->fornecedores.at(i)->getNome() << ",";
	}

	os << "\\";

	for (map<Produto *, unsigned int>::const_iterator it = stock.begin(); it != stock.end(); it++) {


		it->first->printSimp(os);
		os << "#" << it->second << "!";
	}

	return os;
}

ostream& Farmacia::print(ostream & os) const
{
	os << nome << endl << morada;

	if (this->getGerente() != NULL) {

		cout << endl << "gerente: " << this->getGerente()->getNome();
	}

	return os;
}

void Farmacia::mostrarEmpregados() const
{
	for (empregadoHashTable::const_iterator it = empregados.begin(); it != empregados.end(); it++) {
		(*it)->print(cout) << endl << endl;
	}
}

void Farmacia::mostrarStock() const
{
	for (map<Produto *, uint>::const_iterator it = stock.begin(); it != stock.end(); it++) {
		it->first->print(cout) << "#Quantidade: " << it->second << endl << endl;
	}
}

void Farmacia::mostrarPrioridadeEncomenda_listForm(uint quantidade_minima, bool mostraTodos) const
{
	HeapStock heapCopia = this->prioridade_reabastecimento;

	while (!heapCopia.empty()) {

		ItemListaProdutos atual = heapCopia.top();
		heapCopia.pop();
		if(mostraTodos == false){

			if (atual.second >= quantidade_minima)
				break;
		}
			
		atual.first->printListForm(cout) << " #Quantidade: " << atual.second << endl;
	}
}

void Farmacia::mostrarVendas() const
{
	for (size_t i = 0; i < vendas.size(); i++)
		vendas[i]->print(cout) << endl << endl;
}

void Farmacia::despedirEmpregado(Empregado* emp) {

	empregadoHashTable::const_iterator it = empregados.find(emp);

	if (it == empregados.end()) return;
	empregados.erase(emp);
}


