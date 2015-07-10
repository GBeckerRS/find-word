#ifndef     FRASE_H
#define     FRASE_H

#include    <iostream>
#include    <sstream>
#include    <list>

#include    "palavra.h"

class Frase
{
public:
    Frase(const std::string frase);
    Frase(const char* frase);
    Frase(const Frase& frase);
    ~Frase();

    std::string imprimeFrase();
    bool procuraPalavra(const std::string palavra);
    bool procuraPalavra(const char* palavra);

private:
    std::list<Palavra>* _frase;

    void splitFrase(const std::string frase);
    bool procuraToken(std::string token);
};

#endif      //FRASE_H
