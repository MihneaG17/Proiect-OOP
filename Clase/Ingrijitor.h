#ifndef INGRIJITOR_H
#define INGRIJITOR_H

#include "Angajat.h"
#include <iostream>


class Ingrijitor: public Angajat
{
    int etaj_curatenie;
public:
    Ingrijitor(); //Constructor implicit
    Ingrijitor(std::string nume, std::string email, int varsta, int id_angajat, int salariu, std::string functie, int etaj_curatenie); //Constructor parametrizat
    Ingrijitor(const Ingrijitor& obj); //Copy Constructor

    ~Ingrijitor(); //Destructor

    //Getteri si setteri
    int getEtaj() const;

    void setEtaj(int etaj_curatenie);

    //Metode suplimentare
    void afisareDetalii() const override;

    //Metoda viitoare curataEtaj()
};

#endif //INGRIJITOR_H