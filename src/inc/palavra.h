#ifndef     PALAVRA_H
#define     PALAVRA_H

#include    <iostream>
#include    <string>
#include    <algorithm> //std::transform

class Palavra
{
public:
    Palavra(const std::string palavra);
    Palavra(const char* palavra);
    virtual ~Palavra();

    int getTamanho();
    std::string getPalavra();
    char* getPalavra_c();
    void caixaAlta();
    void caixaBaixa();

private:
    std::string* _palavra;
    int* _tamanho;
};

#endif      //PALAVRA_H
