#ifndef     PALAVRA_H
#define     PALAVRA_H

#include    <string>
#include    <locale>    // std::locale, std::toupper
#include    <cstring>   // std::strcoy

#include    "erros.h"

class Palavra
{
public:
    Palavra(const std::string palavra);
    Palavra(const char* palavra);
    Palavra(const Palavra& palavra);
    virtual ~Palavra();

    int getTamanho();
    std::string getPalavra();
    char* getPalavra_c();
    void caixaAlta();
    void caixaBaixa();

private:
    std::string* _palavra;
    int* _tamanho;

    // Metodos privados
    void alteraCaixa(bool modo);
    void inicializa(const std::string palavra);
};

#endif      //PALAVRA_H
