#ifndef SRC_EXCECOES_H
#define SRC_EXCECOES_H

#include <String>
using namespace std;

class OpcaoInvalida {
private:
	string info;
public:
	OpcaoInvalida(string i);
	string getInfo();
};

#endif 