#ifndef     ERROS_H
#define     ERROS_H

#include    "excessao.h"

class
PalavraNaoCriada : public Excessao
{
public:
    PalavraNaoCriada(std::string motivo) : Excessao(motivo) {}
};

#endif      // ERROS_H

