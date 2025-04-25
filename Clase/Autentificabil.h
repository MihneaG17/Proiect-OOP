#ifndef AUTENTIFICABIL_H
#define AUTENTIFICABIL_H

#include <iostream>

//Clasa pur abstracta - Interfata
class Autentificabil
{
public:
    virtual bool autentificare(std::string& email, std::string& parola) = 0;
    virtual ~Autentificabil() {}; //Destructor virtual
};

#endif //AUTENTIFICABIL_H
