#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <vector>
#include "Persoana.h"

class Client: public Persoana
{
    int m_id_client;
    std::vector<int> m_istoric_rezervari;
public:
    Client(); //Constructor implicit
    Client(std::string nume, std::string email, int varsta, int id_client, std::vector<int> istoric_rezervari); //Constructor parametrizat
    Client(const Client& c); //Copy constructor

    ~Client(); //Destructor

    //Getteri si setteri
    int GetIdC() const;
    std::vector<int> GetIstoric() const;

    void SetIdC(int id_client);

    //Supraincarcarea operatorului =+ (adauga rezervare la istoric)
    Client& operator+=(int rezervare);

    //Metode suplimentare
    void AdaugaRezervare(int rezervare);
    void AfisareIstoricRezervari();
    void AfisareDetalii() const override;
};

#endif //CLIENT_H