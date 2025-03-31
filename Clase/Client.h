#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <vector>
#include "Persoana.h"

class Client: public Persoana
{
    int id_client;
    std::vector<int> istoricRezervari;
public:
    Client(); //Constructor implicit
    Client(std::string nume, std::string email, int varsta, int id_client, std::vector<int> istoricRezervari); //Constructor parametrizat
    Client(const Client& c); //Copy constructor

    ~Client(); //Destructor

    //Getteri si setteri
    int getIdC();
    std::vector<int> getIstoric();

    void setIdC(int id_client);

    //Metode suplimentare
    void adaugaRezervare(int rezervare);
    void afisareIstoricRezervari();
    virtual void afisareDetaliiClient() const;
};

#endif //CLIENT_H