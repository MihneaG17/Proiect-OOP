#include "Client.h"
#include <iostream>
#include <vector>

Client::Client():Persoana(), m_id_client(0), m_istoric_rezervari(std::vector<int>()) {}; //Constructor implicit

Client::Client(std::string nume, std::string email, int varsta, int id_client, std::vector<int> istoric_rezervari):
Persoana(nume, email, varsta), m_id_client(id_client), m_istoric_rezervari(istoric_rezervari) {}; //Constructor parametrizat

Client::Client(const Client& c): Persoana(c), m_id_client(c.m_id_client), m_istoric_rezervari(c.m_istoric_rezervari) {}; //Copy constructor

Client::~Client() {}; //Destructor

//Getteri si setteri
int Client::GetIdC() const { return m_id_client; };
std::vector<int> Client::GetIstoric() const { return m_istoric_rezervari; };

void Client::SetIdC(int id_client) { m_id_client=id_client; };


//Supraincarcarea operatorului += (adauga rezervare la istoric)
Client& Client::operator+=(int rezervare)
{
    m_istoric_rezervari.push_back(rezervare);
    return *this;
};

//Metode suplimentare
void Client::AdaugaRezervare(int rezervare)
{
    m_istoric_rezervari.insert(m_istoric_rezervari.begin()+m_istoric_rezervari.size(),rezervare);
};

void Client::AfisareIstoricRezervari()
{
    for(auto& rezervare : m_istoric_rezervari)
        std::cout<<rezervare<<" ";
};

void Client::AfisareDetalii() const
{
    std::cout<<"Nume: "<<GetNume()<<std::endl;
    std::cout<<"Email: "<<GetEmail()<<std::endl;
    std::cout<<"Varsta: "<<GetVarsta()<<std::endl;
    std::cout<<"ID Client: "<<m_id_client<<"\n";
    //std::cout<<"Istoric de rezervari: ";
    //for(auto i:istoricRezervari)
    //    std::cout<<i<<" ";
    std::cout<<"\n"; 
}