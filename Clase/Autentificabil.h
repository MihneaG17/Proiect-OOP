#ifndef AUTENTIFICABIL_H
#define AUTENTIFICABIL_H

#include <iostream>

//Clasa pur abstracta - Interfata
//Folosita pentru autentificarea Administratorului in sistem - NU SE POT INSTANTIA OBIECTE DE ACEST TIP!!
class Autentificabil
{
public:
    virtual bool Autentificare(std::string email, std::string parola) = 0;
    virtual ~Autentificabil() {}; //Destructor virtual
};

#endif //AUTENTIFICABIL_H
