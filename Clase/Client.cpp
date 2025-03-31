#include "Client.h"
#include <iostream>
#include <vector>

Client::Client():Persoana(), id_client(0), istoricRezervari(std::vector<int>()) {}; //Constructor implicit

Client::Client(std::string nume, std::string email, int varsta, int id_client, std::vector<int> istoricRezervari):
Persoana(nume, email, varsta), id_client(id_client), istoricRezervari(istoricRezervari) {}; //Constructor parametrizat

Client::Client(const Client& c): Persoana(c), id_client(c.id_client), istoricRezervari(c.istoricRezervari) {}; //Copy constructor

Client::~Client() {}; //Destructor

//Getteri si setteri
int Client::getIdC() { return id_client; };
std::vector<int> Client::getIstoric() { return istoricRezervari; };

void Client::setIdC(int id_client) { this->id_client=id_client; };

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

void Client::afisareDetaliiClient() const
{
    afisareDetalii();
    std::cout<<"ID Client: "<<id_client<<"\n";
    std::cout<<"Istoric de rezervari: ";
    for(auto i:istoricRezervari)
        std::cout<<i<<" ";
    std::cout<<"\n"; 
}