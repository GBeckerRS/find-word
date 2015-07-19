#ifndef     ERROS_H
#define     ERROS_H

#include    "excessao.h"

/****** PALAVRA ******/ 
class
PalavraNaoCriada : public Excessao
{
public:
    PalavraNaoCriada(std::string motivo) : Excessao(motivo) {}
};

class
PalavraNaoExiste: public Excessao
{
public:
    PalavraNaoExiste(std::string motivo) : Excessao(motivo) {}
};

class
PalavraNaoCarregada: public Excessao
{
public:
    PalavraNaoCarregada(std::string motivo) : Excessao(motivo) {}
};

/****** FRASE ******/ 
class
FraseNaoCriada: public Excessao
{
public:
    FraseNaoCriada(std::string motivo) : Excessao(motivo) {}
};

class
PalavraNaoEncontrada: public Excessao
{
public:
    PalavraNaoEncontrada(std::string motivo) : Excessao(motivo) {}
};

class
NaoImprimeFrase: public Excessao
{
public:
    NaoImprimeFrase(std::string motivo) : Excessao(motivo) {}
};

/****** PROCURA ******/ 
class
ProcuraNaoCriado: public Excessao
{
public:
    ProcuraNaoCriado(std::string motivo) : Excessao(motivo) {}
};

class
ArgumentoDesconhecido: public Excessao
{
public:
    ArgumentoDesconhecido(std::string motivo) : Excessao(motivo) {}
};

class
FraseNaoCarregada: public Excessao
{
public:
    FraseNaoCarregada(std::string motivo) : Excessao(motivo) {}
};

class
NaoAbreArquivo: public Excessao
{
public:
    NaoAbreArquivo(std::string motivo) : Excessao(motivo) {}
};
#endif      // ERROS_H

