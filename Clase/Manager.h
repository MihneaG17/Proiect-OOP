#ifndef MANAGER_H
#define MANAGER_H

#include "Angajat.h"
#include <iostream>
#include <vector>

class Manager : public Angajat
{
    std::vector<std::string> m_departamente_coordonate;
    int m_ani_experienta;

public:
    Manager(); // Constructor implicit
    Manager(std::string nume, std::string email, int varsta, int id_angajat, int salariu,
            std::string functie, std::vector<std::string> departamente_coordonate, int ani_experienta); // Constructor parametrizat
    Manager(const Manager& obj); // Copy constructor

    ~Manager(); // Destructor

    // Getteri si setteri
    std::vector<std::string> GetDepartamente() const;
    int GetExperienta() const;

    void SetDepartamente(std::vector<std::string> departamente);
    void SetExperienta(int ani);

    // Metode suplimentare
    void AfisareDetalii() const override;
    void AdaugaDepartament(std::string dept);
    void EliminaDepartament(std::string dept);

    //Operator overloading +
    Angajat* operator+(int suma) const override;
};

#endif //MANAGER_H