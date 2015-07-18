#ifndef     EXCESSAO_H
#define     EXCESSAO_H

#include    <iostream>
#include    <exception>

class Excessao : std::exception
{
public:
    Excessao(std::string motivo);
    ~Excessao() throw();

    const char* what();

private:
    std::string _motivo;
};

#endif      // EXCESSAO_H
