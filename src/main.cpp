#include    <iostream>

#include    "inc/procura.h"
#include    "inc/erros.h"

int main(int argc, char** argv)
{
    int resp = 0;
    try
    {
        Procura* p = new Procura();
        resp = p->executar(argc,argv);
    }
    catch(std::exception e)
    {
        resp = -1;
    }

    return resp;
}

