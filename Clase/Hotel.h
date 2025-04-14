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

class Hotel
{
    std::vector <Client> clienti;
    std::vector <Angajat> angajati;
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

};

#endif //HOTEL_H