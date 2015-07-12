#include    "procura.h"

/*
*   Construtor
*/
Procura::Procura()
{
    this->_frases = new std::list<Frase>;
}

/*
*   Destrutor
*/
Procura::~Procura()
{
    if(this->_frases)
    {
        delete this->_frases;
        this->_frases = NULL;
    }
    if(this->_nomePrograma)
    {
        delete this->_nomePrograma;
        this->_nomePrograma = NULL;
    }
}

/*
*   executar: Realiza parser das opcoes recebidas pelo programa
*
*   Parametros:
*       qtParametros = Quantidade de parametros recebidos
*       parametros = Parametros recebidos pela linha de comando
*   Retorno:
*       Resultado da execucao do programa
*/
int Procura::executar(int qtParametros, char** parametros)
{
    this->_nomePrograma = new std::string(parametros[0]);

    int index = 1;
    int op = 0;
    while(index < qtParametros)
    {
        op = this->parserArgumentos(parametros[index]);
        switch(op)
        {
            case 0: // Argumento desconhecido
                std::cout << this->msgArgumentoDesconhecido(parametros[index]);
            break;
            case 1: // Frase
                this->_frases->push_back(parametros[index+1]);
            break;
            case 2:
                this->leArquivo(parametros[index+1]);
            break;
            case 3: // Palavra
                this->procuraPalavra(parametros[index+1]);
                std::cout << this->imprimeFrases();
            break;
            case 4: // Ajuda
                std::cout << this->msgAjuda();
            break;
        };
        index += 2;
    }
    return 0;
}

// ****** Metodos Privados ****** //
/*
*   parserArgumento: Retorna o numero do parametro recebido pelo programa
*
*   Parametro:
*       argumento = Argumento recebido
*   Retorno:
*       0 = Argumento desconhecido
*       1 = Frase (-f ou -p)
*       2 = Arquivo (-r ou -i)
*       3 = Palavra (-l ou -w)
*       4 = Ajuda (-a ou -h)
*/
int Procura::parserArgumentos(const char* argumento)
{
    if(std::strcmp(argumento,"-f") == 0 || std::strcmp(argumento,"-p") == 0)
        return 1;
    else if(std::strcmp(argumento,"-r") == 0 || std::strcmp(argumento,"-i") == 0)
        return 2;
    else if(std::strcmp(argumento,"-l") == 0 || std::strcmp(argumento,"-w") == 0)
        return 3;
    else if(std::strcmp(argumento,"-a") == 0 || std::strcmp(argumento,"-h") == 0)
        return 4;
    return 0;
}

/*
*   msgAjuda: Retorna mensegem de ajuda ao usuario
*
*   Retorno:
*       String contendo a mensagem para exibir
*/
std::string Procura::msgAjuda()
{
    std::stringstream ss;
    ss << "find-word: Implementacao minimalista do programa grep." << std::endl;
    ss << "find-word [opcao]... [argumento]..." << std::endl;
    ss << "\t" << "-f, -p" << std::endl;
    ss << "\t\t" << "Carrega uma frase" << std::endl;
    ss << "\t" << "-r, -i" << std::endl;
    ss << "\t\t" << "Carrega o conteudo de um arquivo" << std::endl;
    ss << "\t" << "-l, -w" << std::endl;
    ss << "\t\t" << "Palavra que deve ser procurada" << std::endl;
    return (ss.str()).c_str();
}

/*
*   msgArgumentoDesconhecido: Retorna mensagem indicando que o argumento recebido é inválido
*
*   Parametos:
*       argumento = Argumento recebido
*   Retorno = String contendo a mensagem para exibir
*/
std::string Procura::msgArgumentoDesconhecido(const char* argumento)
{
    std::stringstream ss;
    ss << "A opcao " << argumento << " e invalida!" << std::endl;
    ss << "Utilize " << *this->_nomePrograma << " -a para mais informacoes." << std::endl;
    return (ss.str()).c_str();
}

/*
*   procuraPalavra: Procura por uma palavra na lista de frases
*
*   Parametros:
*       palavra = Palavra que deve ser pesquisada
*/
void Procura::procuraPalavra(const char* palavra)
{
    std::list<Frase>::iterator it;
    for(it = this->_frases->begin(); it != this->_frases->end(); it++)
    {
        (*it).procuraPalavra(palavra);
    }
}

/*
*   imprimeFrases: imprime as frases recebidas pelo programa
*/
std::string Procura::imprimeFrases()
{
    std::stringstream ss;
    std::list<Frase>::iterator it;
    for(it = this->_frases->begin(); it != this->_frases->end(); it++)
    {
        Frase f(*it);
        ss << f.imprimeFrase() << std::endl;
    }
    return ss.str();
}

/*
*   leArquivo: Le o conteudo do arquivo e popula a lista de frases
*
*   Parametros
*       nome = Nome do arquivo que sera lido
*/
void Procura::leArquivo(const char* nome)
{
    std::ifstream in;
    in.open(nome);

    if(in.is_open())
    {
        char* tmp = new char[80];
        in.getline(tmp,80);
        while(in.good())
        {
            this->_frases->push_back(tmp);
            in.getline(tmp,80);
        }
    }
    else
        // Disparar uma excessao de erro
        return;
}

