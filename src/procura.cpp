#include    "procura.h"

/*
*   Construtor
*/
Procura::Procura ()
{
    try
    {
        this->_frases = new std::list<Frase>;
        this->_palavras = new std::list<Palavra>;
        this->_palavra = NULL;
        this->_argDesconhecido = NULL;
        this->_imprimeMsg = 0;
        this->_qtFrases = 0;
        this->flag.frase = false;
        this->flag.palavra = false;
        this->flag.mAjuda = false;
        this->flag.mArgDesconhecido = false;
    }
    catch (std::bad_alloc& e)
    {
        throw ProcuraNaoCriado ("Nao foi possivel iniciar a busca");
    }
}

/*
*   Destrutor
*/
Procura::~Procura ()
{
    if (this->_frases)
    {
        delete this->_frases;
        this->_frases = NULL;
    }
    if (this->_nomePrograma)
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
int Procura::executar (int qtParametros, char** parametros)
{
    try
    {
        this->_nomePrograma = new std::string (parametros[0]);
        int index = 1;
        do
        {
            switch (this->parserArgumentos (parametros[index]))
            {
                case 1: // Popula a lista de frases
                    this->_frases->push_back (*(new Frase (parametros[index+1])));
                    this->flag.frase = true;
                break;
                case 2: // Le de um arquivo e popula lista de frases
                    this->leArquivo (parametros[index+1]);
                break;
                case 3: // Popula a llista de palavras
                    this->_palavras->push_back (*(new Palavra (parametros[index+1])));
                    this->flag.palavra = true;
                break;
                case 4: // Imprime a mensagem de ajuda
                    this->flag.mAjuda = true;
                break;
                default:// Imprime a mensagem de argumento desconhecido
                    this->_argDesconhecido = new std::string (parametros[index]);
                    this->flag.mArgDesconhecido = true;
                break;
            };
            index += 2;
        }
        while (index <= (qtParametros-1));

        if (this->flag.mAjuda)
        {
            std::cout << this->msgAjuda ();
            return 0;
        }
        else
        {
            if (this->flag.mArgDesconhecido)
            {
                std::cout << this->msgArgumentoDesconhecido ();
                return 0;
            }
        }

        if (!this->flag.palavra || !this->flag.frase)
        {
            return -1;
        }

        if (this->flag.palavra)
        {
            // realiza a busca
            this->procuraPalavra ();
            // Imprime as frases carregadas
            std::cout << this->imprimeFrases ();
        }

    }
    catch (Excessao& e)
    {
        return -1;
    }
    catch (std::exception)
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
std::string Procura::msgArgumentoDesconhecido ()
{
    std::stringstream ss;
    ss << "A parametro " << *this->_argDesconhecido << " e invalido!" << std::endl;
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
*   procuraPalavra: Procura por uma palavra na lista de frases
*
*   Parametros:
*       palavra = Palavra que deve ser pesquisada
*/
void Procura::procuraPalavra ()
{
    std::list<Frase>::iterator itFrase;
    std::list<Palavra>::iterator itPalavra;

    bool resp = false;
    for (itFrase = this->_frases->begin (); itFrase != this->_frases->end (); itFrase++)
    {
        for (itPalavra = this->_palavras->begin (); itPalavra != this->_palavras->end (); itPalavra++)
        {
            if ((*itFrase).procuraPalavra ((*itPalavra).getPalavra ()))
            {
                resp = true;
            }
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

