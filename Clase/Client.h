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
    int getIdC() const;
    std::vector<int> getIstoric() const;

    void setIdC(int id_client);

    //Supraincarcarea operatorului =+ (adauga rezervare la istoric)
    Client& operator+=(int rezervare);

    //Metode suplimentare
    void adaugaRezervare(int rezervare);
    void afisareIstoricRezervari();
    void afisareDetalii() const override;
};

#endif //CLIENT_H