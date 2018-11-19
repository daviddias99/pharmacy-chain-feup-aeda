#include <string>
#include "util.h"
#include <ctime>


Morada::Morada()
{
	cidade = "SEM_CIDADE";
	endereco = "SEM_ENDERECO";
	codigoPostal = "0000-000";
}

Morada::Morada(string mor, string codigoPostal, string cidade) :endereco(mor), cidade(cidade) {


	if (codigoPostalValido(codigoPostal)) {
		this->codigoPostal = codigoPostal;
	}
	else {
		throw MoradaInvalida("codigo postal invalido");
	}

	

}

Morada::Morada(string simp) {
	endereco = simp.substr(0, simp.find_first_of('&'));
	simp = simp.substr(simp.find_first_of('&') + 1);
	codigoPostal = simp.substr(0, simp.find_first_of('&'));
	simp = simp.substr(simp.find_first_of('&') + 1);
	cidade = simp;
}

bool Morada::mudaMorada(Morada novaMorada)
{
	*this = novaMorada;

	return true;
}


ostream& Morada::printSimp(ostream& os) const {

	os << endereco << "&" << codigoPostal << "&" << cidade;

	return os;
}

Data::Data(uint dia, uint mes, uint  ano) : ano(ano), mes(mes), dia(dia) {

	if (mes > 12)
		throw DataInvalida();

	if (dia > (unsigned int)daysInMonth(mes, ano))
		throw DataInvalida();

}

Data::Data(string dataDMY)
{
	Data(stoi(dataDMY.substr(0, 2)), stoi(dataDMY.substr(3, 2)),stoi(dataDMY.substr(6, 4)));

}

string Data::getData(bool dmy)
{
	string result;

	if (dmy)
		result = this->getDia() + '/' + this->getMes() + '/' + this->getAno();
	else
		result = this->getAno() + '/' + this->getMes() + '/' + this->getDia();


	return result;
}


Data::Data() {

	time_t tempoAtual = time(NULL);

	tm* tempAtualStruct =  NULL;
	localtime_s(tempAtualStruct,&tempoAtual);

	this->ano = tempAtualStruct->tm_year;
	this->mes = tempAtualStruct->tm_mon;
	this->dia = tempAtualStruct->tm_mday;

}

uint Data::getAno() const
{
	return this->ano;
}

uint Data::getMes() const
{
	return this->mes;
}

uint Data::getDia() const
{
	return this->dia;
}

bool Data::operator<(Data & d2) const
{
	if (this->ano < d2.ano)
		return true;
	else if (this->ano == d2.ano) {

		if (this->mes < d2.mes)
			return true;
		else if (this->mes == d2.mes) {

			if (this->dia < d2.dia)
				return true;
			else return false;


		}
		else return false;
	}
	else return false;

}



Time::Time(uint hora, uint minuto, uint segundo) : hora(hora), minuto(minuto), segundo(segundo) {

	if (hora > 23)
		throw TimeInvalido();
	if (minuto > 59)
		throw TimeInvalido();
	if (segundo > 50)
		throw TimeInvalido();

}

string Time::getTime(bool mostraSegundos)
{
	string result;

	result = this->getHora() + ':' + this->getMin();

	if(mostraSegundos)
		result += ':' + this->getSeg();

	return result;
}

unsigned int Time::getHora() const
{
	return this->hora;
}

unsigned int Time::getMin() const
{
	return this->minuto;
}

unsigned int Time::getSeg() const
{
	return this->segundo;
}

Time::Time() {

	time_t tempoAtual = time(NULL);

	tm* tempAtualStruct = NULL;
	localtime_s(tempAtualStruct,&tempoAtual);

	this->hora = tempAtualStruct->tm_hour;
	this->minuto = tempAtualStruct->tm_min;
	this->segundo = tempAtualStruct->tm_sec;


}

Timestamp::Timestamp() : Data(), Time() {
}

Timestamp::Timestamp(Data data, Time time): Data(data), Time(time){
}

string Timestamp::getTstamp()
{
	string result;

	result = this->getData() + " | " + this->getTime();

	return result;
}

ostream & operator<<(ostream & os, const Morada & mor)
{
	os << mor.endereco << endl << mor.codigoPostal << " " << mor.cidade;

	return os;

}

ostream & operator<<(ostream & os, const Data & d)
{
	os  << setfill('0') << setw(2) << d.dia << "-" << setfill('0') << setw(2) << d.mes << "-" << setw(4) << d.ano ;

	return os;
}

//This function returns true if the given year is a Leap Year and false otherwise
bool isLeap(int year)
{
	bool result = false;

	if (year % 400 == 0)
	{
		result = true;
	}
	else if ((year % 4 == 0) && (year % 10 != 0))
	{
		result = true;
	}

	return result;
}

//This functions returns an integer representing the number of days in a given month of a given year
int daysInMonth(int month, int year)
{
	int numDays;

	if ((month == 2) && isLeap(year))
		numDays = 29;
	else if ((month == 2) && !isLeap(year))
		numDays = 28;
	else if ((month == 1) || (month == 3) || (month == 5) || (month == 7) || (month == 8) || (month == 10) || (month == 12))
		numDays = 31;
	else if ((month == 4) || (month == 6) || (month == 9) || (month == 11))
		numDays = 30;
	else
		numDays = 0;

	return numDays;
}

bool codigoPostalValido(string codigoPostal)
{
	if (codigoPostal.length() != 8) {

		return false;
	}

	if (codigoPostal.at(3) != '-') {

		return false;
	}

	try {

		stoi(codigoPostal.substr(4, 3));

	}
	catch (const std::invalid_argument& ia) {

		return false;
	}

	try {

		stoi(codigoPostal.substr(0, 4));

	}
	catch (const std::invalid_argument& ia) {

		return false;
	}

	return true;
}



/*
template< class T>
int procura(const vector<T> &v, T x)
{
	int left = 0, right = v.size() - 1;
	while (left <= right)
	{
		int middle = (left + right) / 2;
		if (v[middle] < x)
			left = middle + 1;
		else if (x < v[middle])
			right = middle - 1;
		else return middle;

	}
	return -1;
}

template< class T>
int procura(const vector<T*> &v, T x)
{
	int left = 0, right = v.size() - 1;
	while (left <= right)
	{
		int middle = (left + right) / 2;
		if (*v[middle] < x)
			left = middle + 1;
		else if (x < *v[middle])
			right = middle - 1;
		else return middle;

	}
	return -1;
}


template< class T>
int procura(const vector<T*> &v, T* x)
{
	int left = 0, right = v.size() - 1;
	while (left <= right)
	{
		int middle = (left + right) / 2;
		if (*v[middle] < *x)
			left = middle + 1;
		else if (*x < *v[middle])
			right = middle - 1;
		else return middle;

	}
	return -1;
}

template< class T>
int procura(const vector <T> &v, string nome)
{
	int left = 0, right = v.size() - 1;
	while (left <= right)
	{
		int middle = (left + right) / 2;
		if (v[middle].getNome() < nome)
			left = middle + 1;
		else if (nome < v[middle].getNome())
			right = middle - 1;
		else return middle;

	}
	return -1;
}

template < class T>
int procura(const vector <T> &v, int nif)
{
	int left = 0, right = v.size() - 1;
	while (left <= right)
	{
		int middle = (left + right) / 2;
		if (v[middle].getNIF() < nif)
			left = middle + 1;
		else if (nif < v[middle].getNIF())
			right = middle - 1;
		else return middle;

	}
	return -1;
}

template < class T>
int procura(const vector <T*> &v, int nif)
{
	int left = 0, right = v.size() - 1;
	while (left <= right)
	{
		int middle = (left + right) / 2;
		if (v[middle]->getNIF() < nif)
			left = middle + 1;
		else if (nif < v[middle]->getNIF())
			right = middle - 1;
		else return middle;

	}
	return -1;
}
*/


