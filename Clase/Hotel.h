#ifndef HOTEL_H
#define HOTEL_H

#include <iostream>
#include <vector>

#include "Persoana.h"
#include "Angajat.h"
#include "Client.h"
#include "Camera.h"
#include "Rezervare.h"
#include "Review.h"
#include "Ingrijitor.h"
#include "Receptioner.h"
#include "Bucatar.h"
#include "Manager.h"

class Hotel
{
    std::vector <Client> clienti;
    std::vector <Angajat*> angajati;
    std::vector <Camera> camere;
    std::vector <Rezervare> rezervari;
public:
    Hotel();
    ~Hotel();
    void ruleaza();

    //Meniuri
    void meniuClient();
    void meniuAdministrator();
    
    //Actiuni client
    void efectueazaRezervare();
    void veziCamereDisponibile();
    void adaugaRezervare(Camera& camera, std::string& data_check_in, std::string& data_check_out);
    void vizualizareRezervari();
    void anuleazaRezervare();
    void oferaReview();

    //Metode pentru lucru cu fisiere (salvare date/citire date)
    void salvareRezervareFisier(const Rezervare& r);
    void scrieCameraInFisier(const Camera& camera);
    void incarcaCamereDinFisier();
    void actualizeazaCamereDupaRezervare();
    void incarcaAngajatiDinFisier();
    void incarcaRezervariDinFisier();
    void actualizareRezervariDupaAnulare(); 
    void salveazaAngajatiInFisier(); //folosita la mariri/micsorari salariale sau la concediere
    void adaugaAngajatInFisier(Angajat* angajat); //folosita cu modul append doar pentru a adauga la finalul fisierului un angajat

    void incarcaIngrijitor(std::string nume, std::string email, int varsta, int id, int salariu, std::string functie, std::string atribut1);
    void incarcaReceptioner(std::string nume, std::string email, int varsta, int id, int salariu, std::string functie, std::string atribut1, std::string atribut2);
    void incarcaBucatar(std::string nume, std::string email, int varsta, int id, int salariu, std::string functie, std::string atribut1, std::string atribut2);
    void incarcaManager(std::string nume, std::string email, int varsta, int id, int salariu, std::string functie, std::string atribut1, std::string atribut2);

    //Actiuni administrator
    void logareAdmin(bool &ok);
    void adaugaCamere();
    void gestionareAngajati();
    void vizualizareClienti();
    void vizualizareToateRezervarile();

    //Din gestionareAngajati()
    void vizualizareAngajati();
    void maresteSalariuAdmin(); //mareste salariul angajatului prin actiunea din consola a adminului
    void micsoreazaSalariuAdmin(); //micsoreaza salariul angajatului prin actiunea din consola a adminului
    void concediereAngajat();
    void angajare();

    //Functiile din optiunea(metoda) angajare()
    void adaugaIngrijitor(std::string nume, std::string email,int varsta,int id,int salariu,std::string functie);
    void adaugaReceptioner(std::string nume, std::string email,int varsta,int id,int salariu,std::string functie);
    void adaugaBucatar(std::string nume, std::string email,int varsta,int id,int salariu,std::string functie);
    void adaugaManager(std::string nume, std::string email,int varsta,int id,int salariu,std::string functie);

};

#endif //HOTEL_H