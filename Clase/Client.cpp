#include "Client.h"
#include <iostream>
#include <vector>

namespace HotelManagement {

Client::Client():Persoana(), m_id_client(0) {}; //Constructor implicit

Client::Client(std::string nume, std::string email, int varsta, int id_client):
Persoana(nume, email, varsta), m_id_client(id_client) {}; //Constructor parametrizat

Client::Client(const Client& c): Persoana(c), m_id_client(c.m_id_client) {}; //Copy constructor

Client::~Client() {}; //Destructor

//Getteri si setteri
int Client::GetIdC() const { return m_id_client; };

void Client::SetIdC(int id_client) { m_id_client=id_client; };


//Metode suplimentare

void Client::AfisareDetalii() const //Metoda suprascrisa din clasa de baza Persoana
{
    std::cout<<"Nume: "<<GetNume()<<std::endl;
    std::cout<<"Email: "<<GetEmail()<<std::endl;
    std::cout<<"Varsta: "<<GetVarsta()<<std::endl;
    std::cout<<"ID Client: "<<GetIdC()<<"\n";
}
}