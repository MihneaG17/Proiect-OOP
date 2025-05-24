#ifndef RECEPTIONER_H
#define RECEPTIONER_H

#include "Angajat.h"
#include <iostream>
#include <vector>

namespace HotelManagement {
    
class Receptioner: public Angajat
{
    std::string m_schimb; //zi sau noapte
    std::vector <std::string> m_limbi_vorbite;
public:
    Receptioner(); //Constructor implicit
    Receptioner(std::string nume, std::string email, int varsta, int id_angajat, int salariu, std::string functie, std::string schimb, std::vector <std::string> limbi_vorbite); //Constructor parametrizat
    Receptioner(const Receptioner& obj); //Copy constructor

    ~Receptioner(); //Destructor

    //Getteri si setteri
    std::string GetSchimb() const;
    std::vector <std::string> GetLimbi() const;

    void SetSchimb(std::string schimb);

    //Metode suplimentare
    void AfisareDetalii() const override;
    void AdaugaLimba(std::string limba);
    void EliminaLimba(std::string limba);

    //Operator overloading +
    Angajat* operator+(int suma) const override;
};

}
#endif //RECEPTIONER_H