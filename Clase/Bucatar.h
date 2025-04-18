#ifndef BUCATAR_H
#define BUCATAR_H

#include "Angajat.h"
#include <iostream>
#include <vector>

class Bucatar: public Angajat
{
    std::string specializare; //tipul "dish-urilor" in care este specializat
    std::vector<std::string> certificari; //tipuri de meniuri pe care le poate prepara
public:
    Bucatar(); //Constructor implicit
    Bucatar(std::string nume, std::string email, int varsta, int id_angajat, int salariu, std::string functie, std::string specializare, std::vector<std::string> certificari); //Constructor parametrizat
    Bucatar(const Bucatar& obj); //Copy constructor

    ~Bucatar(); //Destructor

    //Getteri si setteri
    std::string getSpecializare() const;
    std::vector<std::string> getCertificari() const;

    void setSpecializare(std::string specializare);

    //Metode suplimentare
    void afisareDetalii() const override;
    void adaugaCertificare(std::string certificare);
    void eliminaCertificare(std::string certificare);
};

#endif //BUCATAR_H