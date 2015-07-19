#include    "procura.h"

/*
*   Construtor
*/
Procura::Procura()
{
    try
    {
        this->_frases = new std::list<Frase>;
        this->_palavra = NULL;
        this->_argumentoDesconhecido = NULL;
        this->_imprimeMsg = 0;
        this->_qtFrases = 0;
    }
    catch(std::bad_alloc& e)
    {
        throw ProcuraNaoCriado("Nao foi possivel iniciar a busca");
    }
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
    Frase* f = NULL;

    try
    {
        int index = 1;
        int op = 0;
        while(index < qtParametros)
        {
            op = this->parserArgumentos(parametros[index]);
            switch(op)
            {
                case 1: // Popula a lista de frases
                    f = new Frase(parametros[index+1]); //parametros[index+1]
                    this->_frases->push_back(*f);
                break;
                case 2: // Le de um arquivo
                    this->leArquivo(parametros[index+1]);
                break;
                case 3: // Armazena a palavra
                    this->_palavra = new std::string(parametros[index+1]);
                break;
                case 4: // Imprime a mensagem de ajuda
                    this->_imprimeMsg = 1;
                break;
                default:// Imprime a mensagem de argumento desconhecido
                    this->_imprimeMsg = 2;
                    this->_argumentoDesconhecido = new std::string(parametros[index]);
                break;
            };
            index += 2;
        }

        if(this->_imprimeMsg == 1)
        {
            std::cout << this->msgAjuda();
            return 0;
        }
        else
        {
            if(this->_imprimeMsg == 2)
            {
                std::cout << this->msgArgumentoDesconhecido(this->_argumentoDesconhecido->c_str());
                return 0;
            }
            else
            {
                if(!this->_palavra)
                {
                    throw PalavraNaoCarregada("Palavra nao foi recebida");
                }
            }
        }

        // Procura a palavra solicitada
        procuraPalavra(this->_palavra->c_str());
        // Imprime as frases carregadas
        std::cout << this->imprimeFrases();
    }
    catch(Excessao& e)
    {
        return -1;
    }
    catch(std::exception& e)
    {
        return -1;
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
    bool resp = false;
    for(it = this->_frases->begin(); it != this->_frases->end(); it++)
    {
        if((*it).procuraPalavra(palavra))
        {
            resp = true;
        }
    }

    if(!resp)
        throw PalavraNaoEncontrada("A palavra nao foi encontrada");
}

/*
*   imprimeFrases: imprime as frases recebidas pelo programa
*/
std::string Procura::imprimeFrases()
{
    std::stringstream ss;
    std::list<Frase>::iterator it;

    try
    {
        for(it = this->_frases->begin(); it != this->_frases->end(); it++)
        {
            ss << (*it).imprimeFrase() << std::endl;
        }
    }
    catch(NaoImprimeFrase e)
    {
        throw ArgumentoDesconhecido("Uma frase nao foi carregada");
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
            this->_qtFrases++;
        }
    }
    else
    {
        throw NaoAbreArquivo("Nao foi possivel abrir o arquivo");
    }
}

