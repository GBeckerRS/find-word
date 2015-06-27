#include    <iostream>

#include    "frase.h"

int main(int argc, char** argv)
{
    std::cout << "Numero Parametros: " << argc << std::endl;
    for(int index=0; index<argc; index++)
        std::cout << "Valor de argv[" << index << "]: "\
        << argv[index] << std::endl;

    Frase f("Uma frasé completa");
    std::cout << f.imprimeFrase() << std::endl;
    f.procuraPalavra("frasé");
    std::cout << "Nova frase alterada: " << f.imprimeFrase() << std::endl;

    return 0;
}

