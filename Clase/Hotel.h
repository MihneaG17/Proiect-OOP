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

};

#endif //HOTEL_H