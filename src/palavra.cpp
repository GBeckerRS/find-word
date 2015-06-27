#include        "palavra.h"

Palavra::Palavra(const std::string palavra)
{
    this->_palavra = new std::string(palavra);
    this->_tamanho = new int((int)(this->_palavra->size()));
}

Palavra::Palavra(const char* palavra)
{
    this->_palavra = new std::string(palavra);
    this->_tamanho = new int((int)(this->_palavra->size()));
}

Palavra::~Palavra()
{
    if(!this->_palavra || !this->_tamanho)
    {
        delete this->_palavra;
        this->_palavra = NULL;
        delete this->_tamanho;
        this->_tamanho = NULL;
    }
}

int Palavra::getTamanho()
{
    if(!this->_tamanho)
        return 0;
    return *this->_tamanho;
}

std::string Palavra::getPalavra()
{
    if(this->_palavra)
    {
        std::string tmp_pal(*this->_palavra);
        return tmp_pal;
    }
    else
    {
        return "";
    }
}

char* Palavra::getPalavra_c()
{
    return (char*)(this->getPalavra()).c_str();
}

void Palavra::caixaBaixa()
{
    this->alteraCaixa(false);
}

void Palavra::caixaAlta()
{
    this->alteraCaixa(true);
}

// Metodos Privados

void Palavra::alteraCaixa(bool modo)
{
    std::locale loc;
    int tam = this->_palavra->size();
    char* tmp = new char[tam+1];
    std::strcpy(tmp,this->_palavra->c_str());

    for(int index = 0; index < tam; index++)
        if(modo)
            tmp[index] = std::toupper(tmp[index],loc);
        else
            tmp[index] = std::tolower(tmp[index],loc);
    *this->_palavra = (const char*)tmp;
}

