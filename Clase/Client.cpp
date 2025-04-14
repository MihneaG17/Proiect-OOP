#include "Client.h"
#include <iostream>
#include <vector>

Client::Client():Persoana(), id_client(0), istoricRezervari(std::vector<int>()) {}; //Constructor implicit

Client::Client(std::string nume, std::string email, int varsta, int id_client, std::vector<int> istoricRezervari):
Persoana(nume, email, varsta), id_client(id_client), istoricRezervari(istoricRezervari) {}; //Constructor parametrizat

Client::Client(const Client& c): Persoana(c), id_client(c.id_client), istoricRezervari(c.istoricRezervari) {}; //Copy constructor

Client::~Client() {}; //Destructor

//Getteri si setteri
int Client::getIdC() const { return id_client; };
std::vector<int> Client::getIstoric() const { return istoricRezervari; };

void Client::setIdC(int id_client) { this->id_client=id_client; };


//Supraincarcarea operatorului += (adauga rezervare la istoric)
Client& Client::operator+=(int rezervare)
{
    istoricRezervari.push_back(rezervare);
    return *this;
};

//Metode suplimentare
void Client::adaugaRezervare(int rezervare)
{
    istoricRezervari.insert(istoricRezervari.begin()+istoricRezervari.size(),rezervare);
};

void Client::afisareIstoricRezervari()
{
    for(auto i:istoricRezervari)
        std::cout<<i<<" ";
};

void Client::afisareDetalii() const
{
    std::cout<<"Nume: "<<getNume()<<std::endl;
    std::cout<<"Email: "<<getEmail()<<std::endl;
    std::cout<<"Varsta: "<<getVarsta()<<std::endl;
    std::cout<<"ID Client: "<<id_client<<"\n";
    //std::cout<<"Istoric de rezervari: ";
    //for(auto i:istoricRezervari)
    //    std::cout<<i<<" ";
    std::cout<<"\n"; 
}