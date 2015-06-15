#include    "frase.h"

Frase::Frase(const std::string frase)
{
    this->_frase = new std::list<Palavra>();
    if(this->_frase)
        this->splitFrase(frase);
}

Frase::Frase(const char* frase)
{
    this->_frase = new std::list<Palavra>();
    if(this->_frase)
        this->splitFrase(frase);
}

Frase::~Frase()
{
    if(this->_frase)
    {
        delete this->_frase;
        this->_frase = NULL;
    }
}

std::string Frase::imprimeFrase()
{
    std::stringstream ss;
    std::list<Palavra>::iterator it;

    for(it = this->_frase->begin(); it != this->_frase->end(); ++it)
    {
        Palavra p = *it;
        ss << p.getPalavra() << " ";
    }

    return ss.str();
}

bool Frase::procuraPalavra(const std::string palavra)
{
    return this->procuraToken(palavra);
}

bool Frase::procuraPalavra(const char* palavra)
{
    return this->procuraToken(palavra);
}

// Métodos privados
void Frase::splitFrase(const std::string frase)
{
    std::istringstream input(frase);
    while(input)
    {
        std::string sub;
        input >> sub;
        if(sub != "")
            this->_frase->push_back(sub);
    }
}

bool Frase::procuraToken(std::string token)
{
    std::list<Palavra>::iterator it = this->_frase->begin();
    for(it = this->_frase->begin(); it != this->_frase->end(); ++it)
    {
        Palavra p = *it;
        if(token == p.getPalavra())
        {
            p.caixaAlta();
            return true;
        }
    }
    return false;
}

