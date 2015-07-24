#ifndef     PROCURA_H
#define     PROCURA_H

#include    <list>
#include    <cstring>
#include    <sstream>
#include    <fstream>

#include    "erros.h"
#include    "frase.h"
#include    "palavra.h"

struct flags
{
    bool frase;
    bool palavra;
    bool mAjuda;
    bool mArgDesconhecido;
};

class Procura
{
public:
    Procura();
    virtual ~Procura();

    int executar (int qtParametros, char** parametros);

private:
    std::list<Frase>* _frases;
    std::list<Palavra>* _palavras;
    std::string* _nomePrograma;
    std::string* _palavra;
    std::string* _argDesconhecido;
    int _imprimeMsg;
    flags flag;
    int _qtFrases;  // apenas para depuracao

    // Metodos privados
    int parserArgumentos (const char* argumento);
    void procuraPalavra (const char* palavra);
    void procuraPalavra ();
    void leArquivo (const char* nome);

    std::string msgAjuda ();
    std::string msgArgumentoDesconhecido ();
    std::string imprimeFrases ();
};

#endif      //PROCURA_H

