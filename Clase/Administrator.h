#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "Autentificabil.h"
#include <iostream>

namespace HotelManagement {

class Administrator: public Autentificabil 
{
    std::string m_email;
    std::string m_parola;
public:
    Administrator(std::string email, std::string parola); //Constructor
    bool Autentificare(std::string e, std::string p) override;
};

}
#endif //ADMINISTRATOR_H