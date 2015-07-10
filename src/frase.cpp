#include    "frase.h"

/*
*   Construtor
*/
Frase::Frase(const std::string frase)
{
    this->_frase = new std::list<Palavra>();
    if(this->_frase)
        this->splitFrase(frase);
}

/*
*   Construtor
*/
Frase::Frase(const char* frase)
{
    this->_frase = new std::list<Palavra>();
    if(this->_frase)
        this->splitFrase(frase);
}

/*
*   Construtor de copia
*/
Frase::Frase(const Frase& frase)
{
    //this->_frase = new Frase(*frase._frase);
    this->_frase = new std::list<Palavra>(*frase._frase);
}

/*
*   Destrutor
*/
Frase::~Frase()
{
    if(this->_frase)
    {
        delete this->_frase;
        this->_frase = NULL;
    }
}

/*
*   imprimeFrase: Imprime a frase
*
*   Retorno
*       String contentdo a frase
*/
std::string Frase::imprimeFrase()
{
    std::stringstream ss;
    std::list<Palavra>::iterator it;

    for(it = this->_frase->begin(); it != this->_frase->end(); ++it)
    {
        Palavra p(*it);
        ss << p.getPalavra() << " ";
    }

    return ss.str();
}

/*
*   procuraPalavra: Procura uma palavra na frase
*
*   Parametros
*       palavra = palavra que deve buscar na frase
*   Retorno
*       true = Se a palavra for encontrada
*/
bool Frase::procuraPalavra(const std::string palavra)
{
    return this->procuraToken(palavra);
}

/*
*   procuraPalavra: Procura uma palavra na frase
*
*   Parametros
*       palavra = palavra que deve buscar na frase
*   Retorno
*       true = Se a palavra for encontrada
*/
bool Frase::procuraPalavra(const char* palavra)
{
    return this->procuraToken(palavra);
}

// ****** Metodos Privados ****** //

/*
*   splitFrase: Popula a lista de frases recebidas
*
*   Parametros
*       frase = Conjunto de frases
*/
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

/*
*   procuraToken: Procura por uma palavra na lista de frases
*
*   Parametro
*       token = Palavra procurada
*   Retorno
*       true = Caso tenha encontrado a palavra
*/
bool Frase::procuraToken(std::string token)
{
    std::list<Palavra>::iterator it = this->_frase->begin();
    for(it = this->_frase->begin(); it != this->_frase->end(); ++it)
    {
        if(token == (*it).getPalavra())
        {
            (*it).caixaAlta();
            return true;
        }
    }
    return false;
}

