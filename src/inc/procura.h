#ifndef     PROCURA_H
#define     PROCURA_H

#include    <list>
#include    <cstring>
#include    <sstream>
#include    <fstream>

#include    "erros.h"
#include    "frase.h"

class Procura
{
public:
    Procura();
    virtual ~Procura();

    int executar(int qtParametros, char** parametros);

private:
    std::list<Frase>* _frases;
    std::string* _nomePrograma;
    std::string* _palavra;
    std::string* _argumentoDesconhecido;
    int _imprimeMsg;
    int _qtFrases;  // apenas para depuracao

    // Metodos privados
    int parserArgumentos(const char* argumento);
    void procuraPalavra(const char* palavra);
    void leArquivo(const char* nome);

    std::string msgAjuda();
    std::string msgArgumentoDesconhecido(const char* argumento);
    std::string imprimeFrases();
};

#endif      //PROCURA_H

