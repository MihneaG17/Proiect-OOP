#ifndef BUCATAR_H
#define BUCATAR_H

#include "Angajat.h"
#include <iostream>
#include <vector>

class Bucatar: public Angajat
{
    std::string m_specializare; //tipul "dish-urilor" in care este specializat
    std::vector<std::string> m_certificari; //tipuri de meniuri pe care le poate prepara
public:
    Bucatar(); //Constructor implicit
    Bucatar(std::string nume, std::string email, int varsta, int id_angajat, int salariu, std::string functie, std::string specializare, std::vector<std::string> certificari); //Constructor parametrizat
    Bucatar(const Bucatar& obj); //Copy constructor

    ~Bucatar(); //Destructor

    //Getteri si setteri
    std::string GetSpecializare() const;
    std::vector<std::string> GetCertificari() const;

    void SetSpecializare(std::string specializare);

    //Metode suplimentare
    void AfisareDetalii() const override;
    void AdaugaCertificare(std::string certificare);
    void EliminaCertificare(std::string certificare);

    //Operator overloading +
    Angajat* operator+(int suma) const override;
};


#endif //BUCATAR_H