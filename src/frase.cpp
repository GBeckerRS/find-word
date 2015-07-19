#include    "frase.h"

/*
*   Construtor
*/
Frase::Frase(const std::string frase)
{
    try
    {
        this->_frase = new std::list<Palavra>();
        if(this->_frase)
            this->splitFrase(frase);
    }
    catch(std::bad_alloc& e)
    {
        throw FraseNaoCriada("Nao foi possivel criar a frase");
    }
}

/*
*   Construtor
*/
Frase::Frase(const char* frase)
{
    try
    {
        this->_frase = new std::list<Palavra>();
        if(this->_frase)
            this->splitFrase(frase);
    }
    catch(std::bad_alloc& e)
    {
        throw FraseNaoCriada("Nao foi possivel criar a frase");
    }
}

/*
*   Construtor de copia
*/
Frase::Frase(const Frase& frase)
{
    try
    {
        this->_frase = new std::list<Palavra>(*frase._frase);
    }
    catch(std::bad_alloc& e)
    {
        throw FraseNaoCriada("Nao foi possivel criar a frase");
    }
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
    if(!this->_frase)
        throw NaoImprimeFrase("Nao foi possivel imprimir a frase");

    std::stringstream ss;
    std::list<Palavra>::iterator it;

    try
    {
        for(it = this->_frase->begin(); it != this->_frase->end(); ++it)
        {
            Palavra p(*it);
            ss << p.getPalavra() << " ";
        }
    }
    catch(Excessao e)
    {
        // PalavraNaoExiste e PalavraNaoCriada
        throw NaoImprimeFrase("Nao foi possivel imprimir a frase");
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
    bool resp = false;
    try
    {
        resp = this->procuraToken(palavra);
    }
    catch(Excessao e)
    {
        // PalavraNaoExiste e PalavraNaoEncontrada
        resp = false;
    }

    return resp;
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
    bool resp = false;
    try
    {
        resp = this->procuraToken(palavra);
    }
    catch(Excessao e)
    {
        // PalavraNaoExiste e PalavraNaoEncontrada
        resp = false;
    }

    return resp;
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
    std::string msg = "Nao foi encontrada a palavra: " + token;
    throw PalavraNaoEncontrada(msg);
}

