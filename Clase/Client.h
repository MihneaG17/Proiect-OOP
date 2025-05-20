#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <vector>
#include "Persoana.h"

class Client: public Persoana
{
    int m_id_client;
    
public:
    Client(); //Constructor implicit
    Client(std::string nume, std::string email, int varsta, int id_client); //Constructor parametrizat
    Client(const Client& c); //Copy constructor

    ~Client(); //Destructor

    //Getteri si setteri
    int GetIdC() const;

    void SetIdC(int id_client);

    //Metode suplimentare
    void AdaugaRezervare(int rezervare);
    void AfisareDetalii() const override;
};

#endif //CLIENT_H