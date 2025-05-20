#include "Angajat.h"
#include <iostream>
#include <vector>

//Metodele si variabilele din struct StatisticiAngajati
int StatisticiAngajat::total_angajati=0;
int StatisticiAngajat::salariu_total=0;
int StatisticiAngajat::salariu_minim=INT_MAX;
int StatisticiAngajat::salariu_maxim=INT_MIN;

void StatisticiAngajat::AdaugaSalariu(int salariu) {
    salariu_total+=salariu;
    total_angajati++;
    if(salariu<salariu_minim) 
        salariu_minim=salariu;
    if(salariu>salariu_maxim)
        salariu_maxim=salariu;
}

void StatisticiAngajat::EliminaSalariu(int salariu, const std::vector<Angajat*>& angajati)
{
    salariu_total-=salariu;
    total_angajati--;
    
    //recalculare minim si maxim in cazul in care salariul angajatului concediat reprezenta una dintre aceste valori
    if(total_angajati==0)
    {
        salariu_minim=INT_MAX;
        salariu_maxim=INT_MIN;
        return;
    }

    salariu_minim=INT_MAX;
    salariu_maxim=INT_MIN;

    for(const auto& angajat : angajati)
    {
        if(angajat)
        {
            int sal=angajat->GetSalariu();
            if(sal<salariu_minim)
                salariu_minim=sal;
            else if(sal>salariu_maxim)
                salariu_maxim=sal;
        }
    }
}

double StatisticiAngajat::SalariuMediu()
{
    return total_angajati==0 ? 0 : static_cast<double>(salariu_total)/total_angajati; //conversie int in double
}

//Clasa Angajat

//Constructori
Angajat::Angajat():Persoana(), m_id_angajat(0), m_salariu(0), m_functie("Nedefinit") {}; //Constructor implicit - Fiind o clasa derivata din clasa de baza Persoana,
//Pentru atributele mostenite se apeleaza constructorul clasei de baza

Angajat::Angajat(std::string nume, std::string email, int varsta, int id_angajat, int salariu, std::string functie):Persoana(nume, email, varsta),
m_id_angajat(id_angajat), m_salariu(salariu), m_functie(functie) 
{
    StatisticiAngajat::AdaugaSalariu(salariu); //Cand se creeaza un nou obiect de tip angajat cu datele completate, se apeleaza functia AdaugaSalariu() ce modifica salariul si nr de angajati
}; 
//Constructor parametrizat - Fiind o clasa derivata din clasa de baza Persoana,
//Pentru atributele mostenite se apeleaza constructorul clasei de baza

Angajat::Angajat(const Angajat& a):Persoana(a), m_id_angajat(a.m_id_angajat), m_salariu(a.m_salariu), m_functie(a.m_functie){}; //Copy constructor

Angajat::~Angajat() {} //Destructor

//Getteri si setteri specifici pentru clasa Angajat (cei din clasa de baza Persoana fiind mosteniti)
int Angajat::GetId() const { return m_id_angajat; };
int Angajat::GetSalariu() const { return m_salariu; };
std::string Angajat::GetFunctie() const { return m_functie; };

void Angajat::SetId(int id_angajat) { m_id_angajat=id_angajat; };
void Angajat::SetSalariu(int salariu)
{
    if(salariu<0)
        std::cout<<"Salariul trebuie sa fie un numar pozitiv";
    else
        m_salariu=salariu;
};
void Angajat::SetFunctie(std::string functie) { m_functie=functie; };

//Metode suplimentare

// void Angajat::MarireSalariala(int procent)
// {
//     salariu=salariu+(procent*salariu)/100;
// };

void Angajat::MinorareSalariala(int procent)
{
    m_salariu=m_salariu-(procent*m_salariu)/100;
};

void Angajat::AfisareDetalii() const //Metoda suprascrisa (cea din clasa de baza Persoana)
{
    std::cout<<"Nume: "<<GetNume()<<"\n";
    std::cout<<"Email: "<<GetEmail()<<"\n";
    std::cout<<"Varsta: "<<GetVarsta()<<"\n";
    std::cout<<"ID Angajat: "<<GetId()<<"\n";
    std::cout<<"Salariu: "<<GetSalariu()<<"\n";
    std::cout<<"Functie: "<<GetFunctie()<<"\n";
};

//Operator overloading +
Angajat* Angajat::operator+(int suma) const
{
    Angajat* copie = new Angajat(*this); //copie dupa obiectul original - se apeleaza copy constructorul
    copie->m_salariu += suma; 
    return copie; //se intoarce copia obiectului, cu salariu modificat
}