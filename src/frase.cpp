#include    "frase.h"

/*
*   Construtor
*/
Frase::Frase(const std::string frase)
{
    //Tratar excessao do operador new
    this->_frase = new std::list<Palavra>();
    if(this->_frase)
        this->splitFrase(frase);
}

/*
*   Construtor
*/
Frase::Frase(const char* frase)
{
    //Tratar excessao do operador new
    this->_frase = new std::list<Palavra>();
    if(this->_frase)
        this->splitFrase(frase);
}

/*
*   Construtor de copia
*/
Frase::Frase(const Frase& frase)
{
    //Tratar excessao do operador new
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
    if(!this->_frases)
        //Nao exista frase carregada
        return "";
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
    // Tratar a excessao lancada pelo metodo procuraToken
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
    // Tratar a excessao lancada pelo metodo procuraToken
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
    // lancar excessao de palavra nao encontrada
    return false;
}

