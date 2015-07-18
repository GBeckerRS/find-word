#include    <iostream>

#include    "inc/procura.h"
#include    "inc/erros.h"

int main(int argc, char** argv)
{
    Procura* p = new Procura();

    return p->executar(argc,argv);
}

