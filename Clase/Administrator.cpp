#include "Administrator.h"
#include <iostream>

Administrator::Administrator(std::string email, std::string parola): m_email(email), m_parola(parola) {}; //Constructor

bool Administrator::Autentificare(std::string e, std::string p)
{
    return m_email==e && m_parola==p; //Returneaza true daca datele introduse corespund cu cele setate
}