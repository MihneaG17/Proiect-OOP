#include "Rezervare.h"
#include "Client.h"
#include "Camera.h"
#include "Review.h"
#include "utils.h"
#include <iostream>
#include <string>

Rezervare::Rezervare():id_rezervare(-1), data_check_in("N/A"), data_check_out("N/A"), pret_total(0.0), numar_nopti(0), discount(0.0), metoda_plata("N/A"), observatii("N/A") {}; //Constructor implicit

//Constructor parametrizat
Rezervare::Rezervare(int id_rezervare, std::string data_check_in, std::string data_check_out, double pret_total, 
    const Client& client, const Camera& camera, std::string metoda_plata, std::string observatii, double discount, int numar_nopti):
id_rezervare(id_rezervare), data_check_in(data_check_in), data_check_out(data_check_out), pret_total(pret_total), client(client), camera(camera),
metoda_plata(metoda_plata), observatii(observatii), discount(discount), numar_nopti(numar_nopti) {}; 

//Copy Constructor
Rezervare::Rezervare(const Rezervare& r): id_rezervare(r.id_rezervare), data_check_in(r.data_check_in), data_check_out(r.data_check_out), pret_total(r.pret_total),
client(r.client), camera(r.camera), discount(r.discount), numar_nopti(r.numar_nopti), observatii(r.observatii), metoda_plata(r.metoda_plata) {}; 

//Destructor
Rezervare::~Rezervare() {};

//Getteri si setteri
int Rezervare::getId() const { return id_rezervare; };
std::string Rezervare::getDataCheckIn() const { return data_check_in; };
std::string Rezervare::getDataCheckOut() const { return data_check_out; };
int Rezervare::getNumarNopti() const { return numar_nopti; };
double Rezervare::getPretTotal() const { return pret_total; };
double Rezervare::getDiscount() const { return discount; };
std::string Rezervare::getMetodaPlata() const { return metoda_plata; };
std::string Rezervare::getObservatii() const { return observatii; };
const Client& Rezervare::getClient() const { return client; };
const Camera& Rezervare::getCamera() const { return camera; };
const Review& Rezervare::getReview() const { return review; };

void Rezervare::setId(int id) { this->id_rezervare=id_rezervare; };
void Rezervare::setDataCheckIn(std::string getDataCheckIn) { this->data_check_in=data_check_in; };
void Rezervare::setDataCheckOut(std::string getDataCheckOut) { this->data_check_out=data_check_out; };
void Rezervare::setNumarNopti(int numar_nopti) { this->numar_nopti=numar_nopti; };
void Rezervare::setDiscount(double discount) { this->discount=discount;  };
void Rezervare::setMetodaPlata(std::string metoda_plata) { this->metoda_plata=metoda_plata; };
void Rezervare::setObservatii(std::string observatii) { this->observatii=observatii; };
void Rezervare::setReview(const Review& review) { this->review=review; };

//Metode suplimentare
void Rezervare::calcularePretDupaDiscount()
{
    pret_total-=(pret_total*discount/100);
};

void Rezervare::prelungireRezervare(int nopti)
{
    numar_nopti+=nopti;
    std::cout<<"Numarul total de nopti dupa actualizare este: "<<numar_nopti<<"\n";
}

void Rezervare::afisareDetalii()
{
    std::cout<<"ID rezervare: "<<id_rezervare<<"\n";
    std::cout<<"Data Check-in: "<<data_check_in<<"\n";
    std::cout<<"Data Check-out: "<<data_check_out<<"\n";
    std::cout<<"Pret total: "<<pret_total<<"\n";
    std::cout<<"Numar nopti: "<<numar_nopti<<"\n";
    std::cout<<"Discount aplicat: "<<discount<< "%\n";
    std::cout<<"Metoda de plata: "<<metoda_plata<< "\n";
    std::cout<<"Observatii: "<<observatii<< "\n";
    std::cout<<"\n";
    std::cout<<"Detaliile clientului: \n";
    client.afisareDetalii();
    std::cout<<"Detaliile camerei: \n";
    camera.afisareDetaliiCamera();
};

void Rezervare::calcularePretTotal() {
    int zile=calculeazaDiferentaZile(data_check_in,data_check_out);

    if(zile>0)
    {
        pret_total=zile*camera.getPret();
        numar_nopti=zile;
    }
    else
        std::cout<<"Datele introduse nu sunt valide.\n";
    };

bool Rezervare::areReview()
{
    return review.getNota()>0 || review.getComentariu()!="N/A";
}