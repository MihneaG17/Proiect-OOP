#ifndef AUTENTIFICABIL_H
#define AUTENTIFICABIL_H

#include <iostream>

//Clasa pur abstracta - Interfata
//In viitor va fi folosita si pentru autentificarea clientilor, nu doar pentru administrator
class Autentificabil
{
public:
    virtual bool Autentificare(std::string email, std::string parola) = 0;
    virtual ~Autentificabil() {}; //Destructor virtual
};

#endif //AUTENTIFICABIL_H
