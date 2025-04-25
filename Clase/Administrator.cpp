#include "Administrator.h"
#include <iostream>

Administrator::Administrator(std::string email, std::string parola): email(email), parola(parola) {}; //Constructor

bool Administrator::autentificare(std::string& e, std::string& p)
{
    return email==e && parola==p;
}