#ifndef RECEPTIONER_H
#define RECEPTIONER_H

#include "Angajat.h"
#include <iostream>
#include <vector>

class Receptioner: public Angajat
{
    std::string schimb; //zi sau noapte
    std::vector <std::string> limbi_vorbite;
public:
    Receptioner(); //Constructor implicit
    Receptioner(std::string nume, std::string email, int varsta, int id_angajat, int salariu, std::string functie, std::string schimb, std::vector <std::string> limbi_vorbite); //Constructor parametrizat
    Receptioner(const Receptioner& obj); //Copy constructor

    ~Receptioner(); //Destructor

    //Getteri si setteri
    std::string getSchimb() const;
    std::vector <std::string> getLimbi() const;

    void setSchimb(std::string schimb);

    //Metode suplimentare
    void afisareDetalii() const override;
    void adaugaLimba(std::string limba);
    void eliminaLimba(std::string limba);

    //Operator overloading +
    Angajat* operator+(int suma) const override;
};


#endif //RECEPTIONER_H