#ifndef PERSOANA_H
#define PERSOANA_H

#include <iostream>

class Persoana
{
    std::string m_nume;
    std::string m_email;
    int m_varsta;
public:
    Persoana(); //Constructor implicit
    Persoana(std::string nume, std::string email, int varsta); //Constructor parametrizat - initializeaza atributele cu cele primite ca argumente
    Persoana(const Persoana& p); // Copy constructor - takes a reference to an object of the same class as an argument - const so we don`t modify de object by mistake

    virtual ~Persoana();  //Destructor virtual - Pentru mostenire: in cazul alocarii dinamice, daca creez un obiect derivat cu un pointer la clasa de baza
    //atunci cand sterg obiectul, nu se va apela si destructorul clasei derivate, ceea ce ar putea duce la memory leak
    //de exemplu daca aloc dinamic un obiect (Persoana* p = new Angajat()), iar apoi eliberez memoria (delete p), fara destructor virtual nu s-ar elibera corect memoria

    //Getteri pentru atribute
    std::string GetNume() const;
    std::string GetEmail() const;
    int GetVarsta() const;

    //Setteri pentru atribute
    void SetNume(std::string nume);
    void SetEmail(std::string email);
    void SetVarsta(int varsta);

    //Metode suplimentare
    virtual void AfisareDetalii() const = 0; //metoda pur virtuala
};


#endif //PERSOANA_H