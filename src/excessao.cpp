#include "inc/excessao.h"

/*
*   Construtor
*/
Excessao::Excessao(std::string motivo)
{
    this->_motivo = motivo;
}

/*
*   Destrutor
*/
Excessao::~Excessao() throw()
{
}

/*
*   what: Retorna mensagem descritivo do erro
*
*   Retorno
*       Retorna uma string C, com a descricao da excessao ocorrida
*/
const char* Excessao::what()
{
    return this->_motivo.c_str();
}

