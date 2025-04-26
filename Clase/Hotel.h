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
#include "Autentificabil.h"
#include "Administrator.h"

class Hotel
{
    std::vector <Client> m_clienti;
    std::vector <Angajat*> m_angajati;
    std::vector <Camera> m_camere;
    std::vector <Rezervare> m_rezervari;
public:
    Hotel();
    ~Hotel();
    void Ruleaza();

    //Meniuri
    void MeniuClient();
    void MeniuAdministrator();
    
    //Actiuni client
    void EfectueazaRezervare();
    void VeziCamereDisponibile();
    void AdaugaRezervare(Camera& camera, std::string& data_check_in, std::string& data_check_out);
    void VizualizareRezervari();
    void AnuleazaRezervare();
    void OferaReview();

    //Metode pentru lucru cu fisiere (salvare date/citire date)
    void SalvareRezervareFisier(const Rezervare& r);
    void ScrieCameraInFisier(const Camera& camera);
    void IncarcaCamereDinFisier();
    void ActualizeazaCamereDupaRezervare();
    void IncarcaAngajatiDinFisier();
    void IncarcaRezervariDinFisier();
    void ActualizareRezervariDupaAnulare(); 
    void SalveazaAngajatiInFisier(); //folosita la mariri/micsorari salariale sau la concediere
    void AdaugaAngajatInFisier(Angajat* angajat); //folosita cu modul append doar pentru a adauga la finalul fisierului un angajat

    void IncarcaIngrijitor(std::string nume, std::string email, int varsta, int id, int salariu, std::string functie, std::string atribut1);
    void IncarcaReceptioner(std::string nume, std::string email, int varsta, int id, int salariu, std::string functie, std::string atribut1, std::string atribut2);
    void IncarcaBucatar(std::string nume, std::string email, int varsta, int id, int salariu, std::string functie, std::string atribut1, std::string atribut2);
    void IncarcaManager(std::string nume, std::string email, int varsta, int id, int salariu, std::string functie, std::string atribut1, std::string atribut2);

    //Actiuni administrator
    void LogareAdmin(bool &ok);
    void AdaugaCamere();
    void GestionareAngajati();
    void VizualizareClienti();
    void VizualizareToateRezervarile();

    //Din gestionareAngajati()
    void VizualizareAngajati();
    void MaresteSalariuAdmin(); //mareste salariul angajatului prin actiunea din consola a adminului
    void MicsoreazaSalariuAdmin(); //micsoreaza salariul angajatului prin actiunea din consola a adminului
    void ConcediereAngajat();
    void Angajare();
    void AfiseazaStatisticiAngajati();

    //Functiile din optiunea(metoda) angajare()
    void AdaugaIngrijitor(std::string nume, std::string email,int varsta,int id,int salariu,std::string functie);
    void AdaugaReceptioner(std::string nume, std::string email,int varsta,int id,int salariu,std::string functie);
    void AdaugaBucatar(std::string nume, std::string email,int varsta,int id,int salariu,std::string functie);
    void AdaugaManager(std::string nume, std::string email,int varsta,int id,int salariu,std::string functie);

};

#endif //HOTEL_H