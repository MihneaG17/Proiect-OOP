#ifndef PERSOANA_H
#define PERSOANA_H

#include <iostream>

class Persoana
{
    std::string nume;
    std::string email;
    int varsta;
public:
    Persoana(); //Constructor implicit
    Persoana(std::string nume, std::string email, int varsta); //Constructor parametrizat - initializeaza atributele cu cele primite ca argumente
    Persoana(const Persoana& p); // Copy constructor - takes a reference to an object of the same class as an argument - const so we don`t modify de object by mistake

    virtual ~Persoana();  //Destructor virtual - Pentru mostenire: in cazul alocarii dinamice, daca creez un obiect derivat cu un pointer la clasa de baza
    //atunci cand sterg obiectul, nu se va apela si destructorul clasei derivate, ceea ce ar putea duce la memory leak
    //de exemplu daca aloc dinamic un obiect (Persoana* p = new Angajat()), iar apoi eliberez memoria (delete p), fara destructor virtual nu s-ar elibera corect memoria

    //Suprascrierea operatorului de atribuire
    //Persoana& operator=(const Persoana& p);

    //Getteri pentru atribute
    std::string getNume() const;
    std::string getEmail() const;
    int getVarsta() const;

    //Setteri pentru atribute
    void setNume(std::string nume);
    void setEmail(std::string email);
    void setVarsta(int varsta);

    //Metode suplimentare
    virtual void afisareDetalii() const;
};


#endif //PERSOANA_H