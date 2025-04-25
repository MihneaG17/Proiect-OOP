#ifndef MANAGER_H
#define MANAGER_H

#include "Angajat.h"
#include <iostream>
#include <vector>

class Manager : public Angajat
{
    std::vector<std::string> departamenteCoordonate;
    int aniExperienta;

public:
    Manager(); // Constructor implicit
    Manager(std::string nume, std::string email, int varsta, int id_angajat, int salariu,
            std::string functie, std::vector<std::string> departamenteCoordonate, int aniExperienta); // Constructor parametrizat
    Manager(const Manager& obj); // Copy constructor

    ~Manager(); // Destructor

    // Getteri si setteri
    std::vector<std::string> getDepartamente() const;
    int getExperienta() const;

    void setDepartamente(std::vector<std::string> departamente);
    void setExperienta(int ani);

    // Metode suplimentare
    void afisareDetalii() const override;
    void adaugaDepartament(std::string dept);
    void eliminaDepartament(std::string dept);

    //Operator overloading +
    Angajat* operator+(int suma) const override;
};

#endif //MANAGER_H