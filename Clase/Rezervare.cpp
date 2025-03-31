#include "Rezervare.h"
#include "Client.h"
#include "Camera.h"
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
int Rezervare::getId() { return id_rezervare; };
std::string Rezervare::getDataCheckIn() { return data_check_in; };
std::string Rezervare::getDataCheckOut() { return data_check_out; };
int Rezervare::getNumarNopti() { return numar_nopti; };
double Rezervare::getPretTotal() { return pret_total; };
double Rezervare::getDiscount() { return discount; };
std::string Rezervare::getMetodaPlata() { return metoda_plata; };
std::string Rezervare::getObservatii() { return observatii; };
const Client& Rezervare::getClient() const { return client; };
const Camera& Rezervare::getCamera() const { return camera; };

void Rezervare::setId(int id) { this->id_rezervare=id_rezervare; };
void Rezervare::setDataCheckIn(std::string getDataCheckIn) { this->data_check_in=data_check_in; };
void Rezervare::setDataCheckOut(std::string getDataCheckOut) { this->data_check_out=data_check_out; };
void Rezervare::setNumarNopti(int numar_nopti) { this->numar_nopti=numar_nopti; };
void Rezervare::setDiscount(double discount) { this->discount=discount;  };
void Rezervare::setMetodaPlata(std::string metoda_plata) { this->metoda_plata=metoda_plata; };
void Rezervare::setObservatii(std::string observatii) { this->observatii=observatii; };

//Metode suplimentare
void Rezervare::calcularePretDupaDiscount()
{
    pret_total-=(pret_total*discount/100);
    std::cout<<"Pretul total de dupa aplicarea discountului este:"<<pret_total<<"\n";
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
    std::cout<<"Detaliile clientului: \n";
    client.afisareDetaliiClient();
    std::cout<<"Detaliile camerei: \n";
    camera.afisareDetaliiCamera();
};
int numarZileInLuna(int luna, int an)
{
    switch(luna)
    {
        case 4: case 6: case 9: case 11: return 30;
        case 2: return (an % 4 == 0 && (an % 100 != 0 || an % 400 == 0)) ? 29 : 28;
        default: return 31;
    }
}
int calculeazaDiferentaZile(std::string check_in, std::string check_out)
{
    int zi1, luna1, an1;
    int zi2, luna2, an2;

    //Transform din string in int datele
    an1=std::stoi(check_in.substr(0,4));
    luna1=std::stoi(check_in.substr(5,2));
    zi1=std::stoi(check_in.substr(8,2));

    an2=std::stoi(check_out.substr(0,4));
    luna2=std::stoi(check_out.substr(5,2));
    zi2=std::stoi(check_out.substr(8,2));

    //Calculez numarul de zile dintre cele doua date
    int zile=0;

    while(an1<an2 || luna1<luna2 || zi1<zi2)
    {
        zi1++;
        zile++;
        if(zi1>numarZileInLuna(luna1,an1))
        {
            zi1=1;
            luna1++;
            if(luna1>12)
            {
                luna1=1;
                an1++;
            }
        }
    }
    return zile;
}
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