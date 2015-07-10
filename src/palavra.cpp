#include        "palavra.h"

/*
*   Construtor
*/
Palavra::Palavra(const std::string palavra)
{
    this->_palavra = new std::string(palavra);
    this->_tamanho = new int((int)(this->_palavra->size()));
}

/*
*   Construtor
*/
Palavra::Palavra(const char* palavra)
{
    this->_palavra = new std::string(palavra);
    this->_tamanho = new int((int)(this->_palavra->size()));
}

/*
*   Construtor de copia
*/
Palavra::Palavra(const Palavra& palavra)
{
    this->_palavra = new std::string(*palavra._palavra);
    this->_tamanho = new int(*palavra._tamanho);
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
        return 0;
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

/*
*   getPalavra_c: Retorna a palavra
*
*   Retorno:
*       String contendo a palavra
*/char* Palavra::getPalavra_c()
{
    return (char*)(this->getPalavra()).c_str();
}

/*
*   caixaBaixa: Altera a palavra para caixa alta
*/
void Palavra::caixaBaixa()
{
    this->alteraCaixa(false);
}

/*
*   caixaAlta: Alatera a palavra para caixa alta
*/
void Palavra::caixaAlta()
{
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
    std::locale loc;
    int tam = this->_palavra->size();
    char* tmp = new char[tam+1];
    std::strcpy(tmp,this->_palavra->c_str());

    for(int i = 0; i < tam; i++)
        if(modo)
            tmp[i] = std::toupper(tmp[i],loc);
        else
            tmp[i] = std::tolower(tmp[i],loc);
    //*this->_palavra = (const char*)tmp;
    delete this->_palavra;
    this->_palavra = NULL;

    this->_palavra = new std::string(tmp);
}

