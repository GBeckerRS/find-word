#include        "palavra.h"

/*
*   Construtor
*/
Palavra::Palavra(const std::string palavra)
{
    try
    {
        this->inicializa(palavra);
    }
    catch(std::bad_alloc& e)
    {
        std::string msg = "Nao foi possivel criar a palavra: " + palavra;
        throw PalavraNaoCriada(msg);
    }
}

/*
*   Construtor
*/
Palavra::Palavra(const char* palavra)
{
    try
    {
        this->inicializa(palavra);
    }
    catch(std::bad_alloc& e)
    {
        std::string p(palavra);
        std::string msg = "Nao foi possivel criar a palavra: " + p;
        throw PalavraNaoCriada(msg);
    }
}

/*
*   Construtor de copia
*/
Palavra::Palavra(const Palavra& palavra)
{
    try
    {
        this->inicializa(*palavra._palavra);
    }
    catch(std::bad_alloc& e)
    {
        std::string msg = "Nao foi possivel criar a palavra: " + *palavra._palavra;
        throw PalavraNaoCriada(msg);
    }
}

/*
*   Destrutor
*/
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

/*
*   getTamanho: Retorna o tamanho da palavra
*
*   Retorno:
*       Tamanho da palavra
*/
int Palavra::getTamanho()
{
    if(!this->_tamanho)
        throw PalavraNaoExiste("Palavra nao existe");

    return *this->_tamanho;
}

/*
*   getPalavra: Retorna a palavra
*
*   Retorno:
*       String contendo a palavra
*/
std::string Palavra::getPalavra()
{
    if(!this->_palavra)
        throw PalavraNaoExiste("Palavra nao existe");

    std::string tmp_pal(*this->_palavra);
    return tmp_pal;
}

/*
*   getPalavra_c: Retorna a palavra
*
*   Retorno:
*       String C contendo a palavra
*/
char* Palavra::getPalavra_c()
{
    if(!this->_palavra)
        throw PalavraNaoExiste("Palavra nao existe");

    std::string tmp(*this->_palavra);
    return (char*)tmp.c_str();
}

/*
*   caixaBaixa: Altera a palavra para caixa alta
*/
void Palavra::caixaBaixa()
{
    if(!this->_palavra)
        throw PalavraNaoExiste("Palavra nao existe");

    this->alteraCaixa(false);
}

/*
*   caixaAlta: Alatera a palavra para caixa alta
*/
void Palavra::caixaAlta()
{
    if(!this->_palavra)
        throw PalavraNaoExiste("Palavra nao existe");

    this->alteraCaixa(true);
}

// ****** Metodos Privados ****** //

/*
*   alteraCaixa: Altera a palavra para letras maiusculas ou minusculas
*
*   Parametros
*       modo = Tipo da alteracao (true = caixa alta, false = caixa baixa)
*/
void Palavra::alteraCaixa(bool modo)
{
    // Tratar excessao do operador new
    std::locale loc;
    int tam = this->_palavra->size();
    char* tmp = new char[tam+1];
    std::strcpy(tmp,this->_palavra->c_str());

    for(int i = 0; i < tam; i++)
        if(modo)
            tmp[i] = std::toupper(tmp[i],loc);
        else
            tmp[i] = std::tolower(tmp[i],loc);

    delete this->_palavra;
    this->_palavra = NULL;

    this->_palavra = new std::string(tmp);
}

void Palavra::inicializa(const std::string palavra)
{
        this->_palavra = new std::string(palavra);
        this->_tamanho = new int((int)(this->_palavra->size()));
}

